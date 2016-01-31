#pragma once
#include <clang-c/Index.h>
#include <string>
#include <vector>

namespace clangxx {

class Index;
class CompilationDatabase;
class SourceLocation;
class Diagnostic;

class TranslationUnit {
public:
    TranslationUnit(Index& index, const std::string& source, CompilationDatabase& comp_db);
    TranslationUnit(const TranslationUnit&) = delete;
    ~TranslationUnit();

    unsigned getNumDiagnostics();
    std::vector<Diagnostic> GetDiagnostics();

private:
    CXTranslationUnit unit_;

    friend class File;
    friend class SourceLocation;
    friend class Cursor;
    friend class Diagnostic;
};
}
