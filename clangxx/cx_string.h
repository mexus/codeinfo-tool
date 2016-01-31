#include <clang-c/Index.h>
#include <string>

namespace clangxx {

std::string CXStringToStdString(CXString& string);
std::string CXStringToStdString(CXString&& string);
}
