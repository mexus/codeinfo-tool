#pragma once
#include <clang-c/Index.h>

namespace clangxx {

class TranslationUnit;
class File;
class Cursor;

class SourceLocation {
public:
    SourceLocation(TranslationUnit& unit, File& file, unsigned line, unsigned column);
    SourceLocation(Cursor& cursor);
    SourceLocation(const SourceLocation&) = delete;

    bool isFromMainFile();
    void getFileLocation(File* file = nullptr, unsigned* line = nullptr, unsigned* column = nullptr,
                         unsigned* offset = nullptr);

private:
    SourceLocation();

    CXSourceLocation location_;

    friend class Cursor;
};
}
