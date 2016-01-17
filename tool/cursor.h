#pragma once
#include <clang-c/Index.h>

namespace cx {

class TranslationUnit;
class SourceLocation;
class Cursor;

class CursorVisitor {
public:
    CursorVisitor();
    virtual ~CursorVisitor();

    CXChildVisitResult Visit(Cursor&& cursor, Cursor&& parent);
};

class Cursor {
public:
    Cursor();
    Cursor(TranslationUnit& unit);
    Cursor(TranslationUnit& unit, SourceLocation& location);
    Cursor(Cursor&& other);
    Cursor(const Cursor&) = delete;
    virtual ~Cursor();

    CXCursorKind getCursorKind();
    CXLanguageKind getCursorLanguage();
    bool isNull();

    unsigned visitChildren(CursorVisitor* visitor);

private:
    Cursor(CXCursor cursor);

    CXCursor cursor_;

    friend class SourceLocation;

    static CXChildVisitResult VisitorWrapper(CXCursor cursor, CXCursor parent, CXClientData client_data);
};

}
