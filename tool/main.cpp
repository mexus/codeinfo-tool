#include <iostream>

#include <boost/filesystem.hpp>

#include "compilation_db.h"
#include "cursor.h"
#include "diagnostic.h"
#include "file.h"
#include "index.h"
#include "options.h"
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
    Options opts;
    bool res;
    std::tie(opts, res) = ParseCmdLine(argc, argv);
    if (!res) {
        return 1;
    }

    opts.path_to_compile_commands = NormalizePath(opts.path_to_compile_commands);
    opts.source_name = NormalizePath(opts.source_name);
    if (opts.file_name.empty()) {
        opts.file_name = opts.source_name;
    }
    opts.file_name = NormalizePath(opts.file_name);

    if (!CheckCompileCommands(opts.path_to_compile_commands)) {
        return 1;
    }
    ChangeCurrentPath(opts.path_to_compile_commands);

    cx::Index index(opts.exclude_declarations_from_pch, opts.display_diagnostic);
    cx::CompilationDatabase comp_db(opts.path_to_compile_commands);
    cx::TranslationUnit unit(index, opts.source_name, comp_db);

    auto diagnostics = unit.GetDiagnostics();
    for (auto& diag : diagnostics) {
        auto severity = diag.getDiagnosticSeverity();
        std::cerr << SeverityToString(severity) << ": " << diag.formatDiagnostic() << "\n";
        if (severity >= CXDiagnostic_Error) {
            return 1;
        }
    }
    std::cout << "File parsed OK\n";

    cx::File file(unit, opts.file_name);
    cx::SourceLocation location(unit, file, opts.line, opts.column);
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
