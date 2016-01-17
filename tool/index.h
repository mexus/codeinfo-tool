#pragma once
#include <clang-c/Index.h>

namespace cx {

class Index {
public:
    Index(int excludeDeclarationsFromPCH, bool displayDiagnostics);
    Index(const Index&) = delete;
    ~Index();

private:
    CXIndex index_;

    friend class TranslationUnit;
};

}
