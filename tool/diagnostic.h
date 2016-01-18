#pragma once
#include <clang-c/Index.h>
#include <string>

namespace cx {

class TranslationUnit;

class Diagnostic {
public:
    Diagnostic(Diagnostic&& other);
    Diagnostic(const Diagnostic&) = delete;
    ~Diagnostic();

    std::string formatDiagnostic(unsigned options = clang_defaultDiagnosticDisplayOptions());
    CXDiagnosticSeverity getDiagnosticSeverity();

private:
    Diagnostic(CXDiagnostic diagnostic);

    CXDiagnostic diagnostic_;

    friend TranslationUnit;
};

}
