#include <diagnostic.h>

namespace cx {

Diagnostic::Diagnostic(Diagnostic&& other) : diagnostic_(std::move(other.diagnostic_)) {
    other.diagnostic_ = nullptr;
}

Diagnostic::Diagnostic(CXDiagnostic diagnostic) : diagnostic_(diagnostic) {}

Diagnostic::~Diagnostic() {
    if (diagnostic_) {
        clang_disposeDiagnostic(diagnostic_);
    }
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
