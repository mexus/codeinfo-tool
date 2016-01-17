#include <file.h>

#include <stdexcept>

#include <translation-unit.h>

namespace cx {

File::File(TranslationUnit& unit, const std::string& file_name) {
    file_ = clang_getFile(unit.unit_, file_name.c_str());
    if (file_ == nullptr) {
        throw std::runtime_error("File `" + file_name + "` is not a part of the translation unit");
    }
}

File::File() : file_(nullptr) {}

std::string File::getFileName() {
    if (!file_) {
        throw std::logic_error("file_ is null");
    }
    CXString path = clang_getFileName(file_);
    std::string result(clang_getCString(path));
    clang_disposeString(path);
    return result;
}

File::operator bool() const {
    return !(!file_);
}
}
