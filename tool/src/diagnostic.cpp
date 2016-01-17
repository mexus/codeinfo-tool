#include <diagnostic.h>
#include <translation-unit.h>

namespace cx {

Diagnostic::Diagnostic(TranslationUnit& unit, unsigned index) {
    diagnostic_ = clang_getDiagnostic(unit.unit_, index);
}

Diagnostic::~Diagnostic() {
    clang_disposeDiagnostic(diagnostic_);
}

std::string Diagnostic::formatDiagnostic(unsigned options) {
    CXString string = clang_formatDiagnostic(diagnostic_, options);
    std::string result(clang_getCString(string));
    clang_disposeString(string);
    return result;
}

CXDiagnosticSeverity Diagnostic::getDiagnosticSeverity() {
    return clang_getDiagnosticSeverity(diagnostic_);
}
}
