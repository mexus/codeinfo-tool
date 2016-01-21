#include <diagnostic.h>
#include <cx_string.h>

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
    return CXStringToStdString(clang_formatDiagnostic(diagnostic_, options));
}

CXDiagnosticSeverity Diagnostic::getDiagnosticSeverity() {
    return clang_getDiagnosticSeverity(diagnostic_);
}
}
