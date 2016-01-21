#include <clang-c/Index.h>
#include <string>

namespace cx {

std::string CXStringToStdString(CXString& string);
std::string CXStringToStdString(CXString&& string);
}
