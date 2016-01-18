#pragma once
#include <string>
#include <tuple>

struct Options {
    bool display_diagnostic;
    int exclude_declarations_from_pch;
    std::string path_to_compile_commands;
    std::string source_name;
    std::string file_name;
    unsigned line;
    unsigned column;
};

std::tuple<Options, bool> ParseCmdLine(int argc, char** argv);
