#include <iostream>
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

int main(int /*argc*/, char** /*argv*/) {
    bool display_diagnostic = true;
    int exclude_declarations_from_pch = 0;
    cx::Index index(exclude_declarations_from_pch, display_diagnostic);
    cx::CompilationDatabase comp_db("/home/mexus/c++11-projects/codeinfo-tool/build/");
    const std::string file_name = "/home/mexus/c++11-projects/codeinfo-tool/tool/src/temp_file.cpp";
    cx::TranslationUnit unit(index, file_name, comp_db);

    for (unsigned i = 0, n = unit.getNumDiagnostics(); i != n; ++i) {
        cx::Diagnostic diag(unit, i);
        auto severity = diag.getDiagnosticSeverity();
        std::cerr << SeverityToString(severity) << ": " << diag.formatDiagnostic() << "\n";
        if (severity >= CXDiagnostic_Error) {
            return 1;
        }
    }
    std::cout << "File parsed OK\n";

    cx::File file(unit, file_name);
    cx::SourceLocation location(unit, file, 11, 32);
    cx::Cursor cursor(unit, location);

    if (cursor.isNull()) {
        std::cout << "Cursor is null\n";
        return 0;
    }

    unsigned line, column, offset;
    location.getFileLocation(&file, &line, &column, &offset);
    std::cout << "Location: ";
    if (file) {
        std::cout << file.getFileName();
    } else {
        std::cout << "[no file]";
    }
    std::cout << ", line " << line << ", "
              << "column " << column << ", offset " << offset << "\n";

    std::cout << "Location is from main file? " << std::boolalpha << location.isFromMainFile() << "\n";
    std::cout << "Cursor kind: " << cursor.getCursorKind() << "\n";

    return 0;
}
