#include <iostream>
#include <boost/filesystem.hpp>
#include "compilation_db.h"
#include "cursor.h"
#include "diagnostic.h"
#include "file.h"
#include "index.h"
#include "source_location.h"
#include "translation-unit.h"

namespace {

std::string SeverityToString(CXDiagnosticSeverity severity) {
    switch (severity) {
        case CXDiagnostic_Ignored:
            return "Ignored";
        case CXDiagnostic_Note:
            return "Note";
        case CXDiagnostic_Warning:
            return "Warning";
        case CXDiagnostic_Error:
            return "Error";
        case CXDiagnostic_Fatal:
            return "Fatal";
        default:;
    }
    return "Unknown";
}
}

std::string NormalizePath(const std::string& file) {
    using namespace boost::filesystem;
    return canonical(absolute(file)).string();
}

bool CheckCompileCommands(const std::string& path_to_compile_commands) {
    using namespace boost::filesystem;
    path cc_path(path_to_compile_commands);
    if (!exists(cc_path)) {
        std::cerr << "Path to `compile_commands.json` doesn't exist\n";
        return false;
    }
    if (!exists(cc_path / "compile_commands.json")) {
        std::cerr << "`compile_commands.json` doesn't exist in `" << cc_path << "`\n";
        return false;
    }
    return true;
}

void ChangeCurrentPath(const std::string& new_path) {
    boost::filesystem::current_path(new_path);
}

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cerr << argv[0] << " <compile_commands.json dir> <file to parse> <line> <column>\n";
        return 1;
    }

    const bool display_diagnostic = true;
    const int exclude_declarations_from_pch = 0;
    const std::string path_to_compile_commands = NormalizePath(argv[1]);
    const std::string file_name = NormalizePath(argv[2]);
    const unsigned line = std::stoul(argv[3]);
    const unsigned number = std::stoul(argv[4]);

    if (!CheckCompileCommands(path_to_compile_commands)) {
        return 1;
    }
    ChangeCurrentPath(path_to_compile_commands);

    cx::Index index(exclude_declarations_from_pch, display_diagnostic);
    cx::CompilationDatabase comp_db(path_to_compile_commands);
    cx::TranslationUnit unit(index, file_name, comp_db);

    auto diagnostics = unit.GetDiagnostics();
    for (auto& diag : diagnostics) {
        auto severity = diag.getDiagnosticSeverity();
        std::cerr << SeverityToString(severity) << ": " << diag.formatDiagnostic() << "\n";
        if (severity >= CXDiagnostic_Error) {
            return 1;
        }
    }
    std::cout << "File parsed OK\n";

    cx::File file(unit, file_name);
    cx::SourceLocation location(unit, file, line, number);
    cx::Cursor cursor(unit, location);

    if (cursor.isNull()) {
        std::cerr << "Cursor is null\n";
        return 1;
    }

    unsigned effective_line, effective_column, effective_offset;
    location.getFileLocation(&file, &effective_line, &effective_column, &effective_offset);
    std::cout << "Location: ";
    if (file) {
        std::cout << file.getFileName();
    } else {
        std::cout << "[no file]";
    }
    std::cout << ", line " << effective_line << ", "
              << "column " << effective_column << ", offset " << effective_offset << "\n";

    std::cout << "Location is from main file? " << std::boolalpha << location.isFromMainFile() << "\n";
    std::cout << "Cursor kind: " << cursor.getCursorKind() << "\n";

    return 0;
}
