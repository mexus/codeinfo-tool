#pragma once
#include <string>
#include <clang-c/Index.h>

namespace cx {

class Index;
class CompilationDatabase;
class SourceLocation;

class TranslationUnit {
public:
    TranslationUnit(Index& index, const std::string& source, CompilationDatabase& comp_db);
    TranslationUnit(const TranslationUnit&) = delete;
    ~TranslationUnit();

    unsigned getNumDiagnostics();

private:
    CXTranslationUnit unit_;

    friend class File;
    friend class SourceLocation;
    friend class Cursor;
    friend class Diagnostic;
};

}
