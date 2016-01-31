#include <clangxx/type.h>

#include <utility>

#include <clangxx/cx_string.h>

namespace clangxx {

Type::Type(Type&& other) : type_(std::move(other.type_)) {}

Type::Type(CXType&& type) : type_(std::move(type)) {}

CXTypeKind Type::GetKind() const {
    return type_.kind;
}

std::string Type::getTypeSpelling() {
    return CXStringToStdString(clang_getTypeSpelling(type_));
}

Type Type::getCanonicalType() {
    return Type(clang_getCanonicalType(type_));
}
}
