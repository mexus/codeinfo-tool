#include <index.h>

namespace cx {

Index::Index(int exclude_declarations_from_pch, bool display_diagnostics) {
    index_ = clang_createIndex(exclude_declarations_from_pch, display_diagnostics ? 0 : 1);
}

Index::~Index() {
    clang_disposeIndex(index_);
}
}
