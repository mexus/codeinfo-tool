#include <clangxx/translation-unit.h>

#include <stdexcept>
#include <vector>

#include <clangxx/compilation_db.h>
#include <clangxx/diagnostic.h>
#include <clangxx/index.h>
#include <clangxx/source_location.h>

namespace clangxx {

namespace {

std::string ErrorCodeToString(CXErrorCode code) {
    switch (code) {
        case CXError_Success:
            return "Success";
        case CXError_Failure:
            return "Failure";
        case CXError_Crashed:
            return "Crashed";
        case CXError_InvalidArguments:
            return "Invalid arguments";
        case CXError_ASTReadError:
            return "AST read error";
        default:;
    }
    return "Unknown error code";
}
}

TranslationUnit::TranslationUnit(Index& index, const std::string& source, CompilationDatabase& comp_db) {
    auto commands = comp_db.getCompileCommands(source);
    unsigned cmd_args = commands.getSize();
    if (cmd_args == 0) {
        throw std::runtime_error("No compilation info for file `" + source + "`");
    }
    auto command = commands.getCommand(0);
    auto arguments = command.GetArguments(1);
    arguments.push_back("-I" + comp_db.GetClangHeadersLocation());
    std::vector<const char*> c_arguments;
    c_arguments.reserve(arguments.size());
    bool skip = false;
    for (auto& arg : arguments) {
        if (skip) {
            skip = false;
            continue;
        }
        if (arg == "-c") {
            skip = true;
            continue;
        }
        c_arguments.push_back(arg.c_str());
    }
    CXErrorCode code = clang_parseTranslationUnit2(index.index_, source.c_str(), c_arguments.data(), c_arguments.size(),
                                                   nullptr, 0, CXTranslationUnit_DetailedPreprocessingRecord, &unit_);
    if (code != CXError_Success) {
        throw std::runtime_error("Error while parsing file `" + source + "`: " + ErrorCodeToString(code));
    }
}

TranslationUnit::~TranslationUnit() {
    clang_disposeTranslationUnit(unit_);
}

unsigned TranslationUnit::getNumDiagnostics() {
    return clang_getNumDiagnostics(unit_);
}

std::vector<Diagnostic> TranslationUnit::GetDiagnostics() {
    std::vector<Diagnostic> result;
    for (unsigned i = 0, l = getNumDiagnostics(); i != l; ++i) {
        auto diagnostic = Diagnostic(clang_getDiagnostic(unit_, i));
        result.push_back(std::move(diagnostic));
    }
    return result;
}
}
