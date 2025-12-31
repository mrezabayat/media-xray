#include <iostream>
#include <string>

#include <cxxopts.hpp>

#include "version.h"

namespace {
void print_usage(const cxxopts::Options &options) {
    std::cout << options.help({""}) << "\n";
}
}

int main(int argc, char **argv) {
    cxxopts::Options options("media-xray", "MediaXray CLI");
    options.positional_help("<command> [args]");
    options.add_options()
        ("h,help", "Print usage")
        ("v,version", "Print version")
        ("command", "Command to run", cxxopts::value<std::string>())
        ("input", "Input path", cxxopts::value<std::string>());

    options.parse_positional({"command", "input"});

    cxxopts::ParseResult result;
    try {
        result = options.parse(argc, argv);
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        print_usage(options);
        return 1;
    }

    if (result.count("help") > 0) {
        print_usage(options);
        return 0;
    }

    if (result.count("version") > 0) {
        std::cout << media_xray::version_string() << "\n";
        return 0;
    }

    if (result.count("command") == 0) {
        print_usage(options);
        return 0;
    }

    const std::string command = result["command"].as<std::string>();
    if (command == "analyze") {
        if (result.count("input") == 0) {
            std::cerr << "Error: missing <input>\n";
            return 1;
        }
        std::cout << "Not implemented\n";
        return 0;
    }

    std::cerr << "Error: unknown command\n";
    print_usage(options);
    return 1;
}
