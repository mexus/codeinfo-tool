#pragma once

#include <clang-c/CXCompilationDatabase.h>
#include <clang-c/Index.h>
#include <string>
#include <vector>

namespace cx {

class CompileCommand {
public:
    CompileCommand(const CompileCommand&) = delete;
    CompileCommand(CompileCommand&&);

    std::string getDirectory();
    // std::string getFilename(); // Not in all versions of Clang
    unsigned getNumArgs();
    std::string getArg(unsigned i);
    std::vector<std::string> GetArguments(int skip = 0);

private:
    CXCompileCommand command_;

    CompileCommand(CXCompileCommand command);

    friend class CompileCommands;
};

class CompileCommands {
public:
    ~CompileCommands();

    unsigned getSize();
    CompileCommand getCommand(unsigned i);

private:
    CXCompileCommands commands_;

    CompileCommands(CXCompileCommands commands);

    friend class CompilationDatabase;

};

class CompilationDatabase {
public:
    CompilationDatabase(const std::string& path);
    ~CompilationDatabase();

    CompileCommands getCompileCommands(const std::string& file_name);
    CompileCommands getAllCompileCommands();


    void SetClangHeadersLocation(const std::string& path);
    std::string GetClangHeadersLocation() const;

private:
    CXCompilationDatabase db_;
    std::string clang_headers_path_ = "/usr/lib/clang/3.7.1/include/";
};

}
