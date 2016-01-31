#include <clangxx/cx_string.h>

namespace {
template <class T>
std::string Convert(T&& string) {
    std::string result(clang_getCString(string));
    clang_disposeString(string);
    return result;
}
}

namespace clangxx {

std::string CXStringToStdString(CXString& string) {
    return Convert(std::forward<CXString&>(string));
}

std::string CXStringToStdString(CXString&& string) {
    return Convert(std::forward<CXString&&>(string));
}
}
