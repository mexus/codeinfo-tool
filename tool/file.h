#pragma once
#include <clang-c/Index.h>
#include <string>

namespace cx {

class TranslationUnit;

class File {
public:
    File();
    File(TranslationUnit& unit, const std::string& file_name);
    File(const File&) = delete;

    operator bool() const;
    std::string getFileName();

private:
    CXFile file_;

    friend class SourceLocation;
};
}
