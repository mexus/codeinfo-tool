#include <source_location.h>

#include <cursor.h>
#include <file.h>
#include <translation-unit.h>

namespace cx {

SourceLocation::SourceLocation() {
    location_ = clang_getNullLocation();
}

SourceLocation::SourceLocation(TranslationUnit& unit, File& file, unsigned line, unsigned column) {
    location_ = clang_getLocation(unit.unit_, file.file_, line, column);
}

SourceLocation::SourceLocation(Cursor& cursor) {
    location_ = clang_getCursorLocation(cursor.cursor_);
}

bool SourceLocation::isFromMainFile() {
    return clang_Location_isFromMainFile(location_) != 0;
}

void SourceLocation::getFileLocation(File* file, unsigned* line, unsigned* column, unsigned* offset) {
    CXFile* cx_file = nullptr;
    if (file) {
        cx_file = &(file->file_);
    }
    clang_getFileLocation(location_, cx_file, line, column, offset);
}
}
