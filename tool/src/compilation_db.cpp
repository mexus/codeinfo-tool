#include <compilation_db.h>
#include <iostream>

namespace cx {

CompileCommand::CompileCommand(CXCompileCommand command) : command_(command) {}

CompileCommand::CompileCommand(CompileCommand&& other) : command_(other.command_) {
    other.command_ = nullptr;
}

std::string CompileCommand::getDirectory() {
    CXString dir = clang_CompileCommand_getDirectory(command_);
    std::string result(clang_getCString(dir));
    clang_disposeString(dir);
    return result;
}

// std::string CompileCommand::getFilename() {
//     CXString path = clang_CompileCommand_getFilename(command_);
//     std::string result(clang_getCString(path));
//     clang_disposeString(path);
//     return result;
// }

unsigned CompileCommand::getNumArgs() {
    return clang_CompileCommand_getNumArgs(command_);
}

std::string CompileCommand::getArg(unsigned i) {
    CXString data = clang_CompileCommand_getArg(command_, i);
    std::string result(clang_getCString(data));
    clang_disposeString(data);
    return result;
}

std::vector<std::string> CompileCommand::GetArguments(int skip) {
    int n = getNumArgs();
    std::vector<std::string> result;
    for (int i = skip; i < n; ++i) {
        result.push_back(getArg(i));
    }
    return result;
}

CompileCommands::CompileCommands(CXCompileCommands commands) : commands_(commands) {}

CompileCommands::~CompileCommands() {
    clang_CompileCommands_dispose(commands_);
}

unsigned CompileCommands::getSize() {
    return clang_CompileCommands_getSize(commands_);
}

CompileCommand CompileCommands::getCommand(unsigned i) {
    return CompileCommand(clang_CompileCommands_getCommand(commands_, i));
}

CompilationDatabase::CompilationDatabase(const std::string& path) {
    CXCompilationDatabase_Error error;
    db_ = clang_CompilationDatabase_fromDirectory(path.c_str(), &error);
    if (error != CXCompilationDatabase_NoError) {
        std::cout << db_ << "\n";
        throw std::runtime_error("Can't load compilation database from path `" + path + "`");
    }
}

CompilationDatabase::~CompilationDatabase() {
    clang_CompilationDatabase_dispose(db_);
}

CompileCommands CompilationDatabase::getCompileCommands(const std::string& file_name) {
    CXCompileCommands commands = clang_CompilationDatabase_getCompileCommands(db_, file_name.c_str());
    return CompileCommands(commands);
}

void CompilationDatabase::SetClangHeadersLocation(const std::string& path) {
    clang_headers_path_ = path;
}

std::string CompilationDatabase::GetClangHeadersLocation() const {
    return clang_headers_path_;
}
}
