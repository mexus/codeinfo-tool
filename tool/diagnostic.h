#pragma once
#include <clang-c/Index.h>
#include <string>

namespace cx {

class TranslationUnit;

class Diagnostic {
public:
    Diagnostic(TranslationUnit& unit, unsigned index);
    ~Diagnostic();

    std::string formatDiagnostic(unsigned options = clang_defaultDiagnosticDisplayOptions());
    CXDiagnosticSeverity getDiagnosticSeverity();

private:
    Diagnostic(CXDiagnostic diagnostic);

    CXDiagnostic diagnostic_;
};

}
