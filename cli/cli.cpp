#include "cli.h"

#include <iostream>
#include <string>

#include <cxxopts.hpp>

#include "version.h"

namespace {
struct CommandInfo {
  const char *name;
  const char *description;
};

constexpr CommandInfo kCommands[] = {
    {"analyze <input>", "Analyze the given input"},
    {"help", "Show this help"},
};

cxxopts::Options make_help_options() {
  cxxopts::Options options("media-xray", "MediaXray CLI");
  options.custom_help("<command> [args]");
  options.add_options("Global")("h,help", "Print usage")("v,version",
                                                         "Print version");
  return options;
}

void print_general_help() {
  cxxopts::Options options = make_help_options();
  std::cout << options.help({"Global"}) << "\n";
  std::cout << "Commands:\n";
  for (const auto &command : kCommands) {
    std::cout << "  " << command.name << "  " << command.description << "\n";
  }
}

void print_analyze_help() {
  cxxopts::Options analyze_options("media-xray analyze",
                                   "Analyze the given input");
  analyze_options.positional_help("<input>");
  analyze_options.add_options()("h,help", "Print usage")(
      "input", "Input path", cxxopts::value<std::string>());
  analyze_options.parse_positional({"input"});
  std::cout << analyze_options.help() << "\n";
}
} // namespace

namespace media_xray {
int run_cli(int argc, char **argv) {
  cxxopts::Options options = make_help_options();
  options.add_options()("command", "Command to run",
                        cxxopts::value<std::string>());
  options.parse_positional({"command"});

  if (argc <= 1) {
    print_general_help();
    return 0;
  }

  const std::string first_arg = argv[1];
  if (first_arg == "-v" || first_arg == "--version") {
    std::cout << media_xray::version_string() << "\n";
    return 0;
  }

  const std::string command = first_arg;

  if (command == "-h" || command == "--help" || command == "help") {
    print_general_help();
    return 0;
  }

  if (command == "analyze") {
    cxxopts::Options analyze_options("media-xray analyze",
                                     "Analyze the given input");
    analyze_options.positional_help("<input>");
    analyze_options.add_options()("h,help", "Print usage")(
        "input", "Input path", cxxopts::value<std::string>());
    analyze_options.parse_positional({"input"});

    cxxopts::ParseResult analyze_result;
    try {
      analyze_result = analyze_options.parse(argc - 1, argv + 1);
    } catch (const std::exception &ex) {
      std::cerr << "Error: " << ex.what() << "\n";
      print_analyze_help();
      return 1;
    }

    if (analyze_result.count("help") > 0) {
      print_analyze_help();
      return 0;
    }

    if (analyze_result.count("input") == 0) {
      std::cerr << "Error: missing <input>\n";
      print_analyze_help();
      return 1;
    }

    std::cout << "Not implemented\n";
    return 0;
  }

  if (!command.empty() && command[0] == '-') {
    std::cerr << "Error: unknown option\n";
    print_general_help();
    return 1;
  }

  std::cerr << "Error: unknown command\n";
  print_general_help();
  return 1;
}
} // namespace media_xray
