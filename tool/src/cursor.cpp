#include <cursor.h>

#include <iostream>

#include <source_location.h>
#include <translation-unit.h>

namespace cx {

CursorVisitor::CursorVisitor() {}

CursorVisitor::~CursorVisitor() {}

CXChildVisitResult CursorVisitor::Visit(Cursor&& /*cursor*/, Cursor&& /*parent*/) {
    return CXChildVisit_Continue;
}

Cursor::Cursor() {
    cursor_ = clang_getNullCursor();
}

Cursor::Cursor(CXCursor cursor) : cursor_(cursor) {}

Cursor::Cursor(TranslationUnit& unit) {
    cursor_ = clang_getTranslationUnitCursor(unit.unit_);
}

Cursor::Cursor(TranslationUnit& unit, SourceLocation& location) {
    cursor_ = clang_getCursor(unit.unit_, location.location_);
}

Cursor::Cursor(Cursor&& other) : cursor_(std::move(other.cursor_)) {}

Cursor::~Cursor() {}

CXCursorKind Cursor::getCursorKind() {
    return clang_getCursorKind(cursor_);
}

bool Cursor::isNull() {
    return clang_Cursor_isNull(cursor_) != 0;
}

CXLanguageKind Cursor::getCursorLanguage() {
    return clang_getCursorLanguage(cursor_);
}

unsigned Cursor::visitChildren(CursorVisitor* visitor) {
    return clang_visitChildren(cursor_, &Cursor::VisitorWrapper, static_cast<CXClientData>(visitor));
}

CXChildVisitResult Cursor::VisitorWrapper(CXCursor cursor, CXCursor parent, CXClientData client_data) {
    auto visitor = static_cast<CursorVisitor*>(client_data);
    return visitor->Visit(Cursor(cursor), Cursor(parent));
}

Type Cursor::getCursorType() {
    auto type = clang_getCursorType(cursor_);
    return Type(std::move(type));
}
}
