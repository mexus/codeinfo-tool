#include <options.h>

#include <iostream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

std::tuple<Options, bool> ParseCmdLine(int argc, char** argv) {
    using namespace boost::program_options;
    Options options;
    options.line = 0;
    options.column = 0;
    options_description desc("Options");
    desc.add_options()("help", "help message");
    desc.add_options()("cc", value<std::string>(&options.path_to_compile_commands)->default_value("."),
                       "Directory of the `compile_commands.json` file");
    desc.add_options()("source,s", value<std::string>(&options.source_name), "Source file");
    desc.add_options()("file,f", value<std::string>(&options.file_name),
                       "File to analyze, if empty, equals to 'source file'");
    desc.add_options()("diag,d", value<bool>(&options.display_diagnostic)->default_value(true), "Display diagnostics");
    desc.add_options()("exclude-pch", value<int>(&options.exclude_declarations_from_pch)->default_value(0),
                       "Exclude declarations from precompiled headers (PCH)");
    desc.add_options()("line", value<unsigned>(&options.line), "Line in the file");
    desc.add_options()("col", value<unsigned>(&options.column), "Column on the line");

    variables_map vm;
    try {
        store(parse_command_line(argc, argv, desc), vm);
    } catch (const boost::program_options::unknown_option& e) {
        std::cerr << "Unrecognized option `" << e.get_option_name() << "`\n";
        return std::make_tuple(options, false);
    }
    notify(vm);

    if (vm.count("help") != 0) {
        std::cout << desc << "\n";
        return std::make_tuple(options, false);
    }
    bool res = true;
    if (options.source_name.empty()) {
        std::cerr << "Source name should not be empty\n";
        res = false;
    }
    if (options.line == 0) {
        std::cerr << "Line should be non-zero\n";
        res = false;
    }
    if (options.column == 0) {
        std::cerr << "Columnt should be non-zero\n";
        res = false;
    }
    if (!res) {
        std::cout << desc << "\n";
    }
    return std::make_tuple(options, res);
}
