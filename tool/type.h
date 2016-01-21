#pragma once
#include <clang-c/Index.h>
#include <string>

namespace cx {

class Type {
public:
    Type(Type&& other);
    Type(const Type&) = delete;

    CXTypeKind GetKind() const;
    std::string getTypeSpelling();
    Type getCanonicalType();

private:
    Type(CXType&& type);
    CXType type_;

    friend class Cursor;
};
}
