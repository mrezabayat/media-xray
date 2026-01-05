#include "cli.h"

#include <cctype>
#include <iostream>
#include <string>
#include <string_view>

#include <cxxopts.hpp>

#include "errors.h"
#include "log.h"
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
  options.custom_help(
      "[global options] <command> [args]\n  <command> [args] [global options]");
  options.add_options("Global")("h,help", "Print usage")(
      "v,version", "Print version")("log-level",
                                    "Log level (error|warn|info|debug)",
                                    cxxopts::value<std::string>());
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
      "v,version", "Print version")("input", "Input path",
                                    cxxopts::value<std::string>())(
      "log-level", "Log level (error|warn|info|debug)",
      cxxopts::value<std::string>());
  analyze_options.parse_positional({"input"});
  std::cout << analyze_options.help() << "\n";
}

std::string lower_copy(std::string_view value) {
  std::string out;
  out.reserve(value.size());
  for (char ch : value) {
    out.push_back(
        static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
  }
  return out;
}

bool parse_log_level_value(std::string_view value, media_xray::LogLevel &out) {
  const std::string normalized = lower_copy(value);
  if (normalized == "error") {
    out = media_xray::LogLevel::ERROR;
    return true;
  }
  if (normalized == "warn" || normalized == "warning") {
    out = media_xray::LogLevel::WARN;
    return true;
  }
  if (normalized == "info") {
    out = media_xray::LogLevel::INFO;
    return true;
  }
  if (normalized == "debug") {
    out = media_xray::LogLevel::DEBUG;
    return true;
  }
  return false;
}

int find_command_index(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    std::string_view arg(argv[i]);
    if (arg == "--log-level") {
      if (i + 1 < argc) {
        ++i;
      }
      continue;
    }
    if (arg.rfind("--log-level=", 0) == 0) {
      continue;
    }
    if (arg == "--help" || arg == "-h" || arg == "--version" || arg == "-v") {
      continue;
    }
    if (!arg.empty() && arg.front() == '-') {
      continue;
    }
    return i;
  }
  return -1;
}
} // namespace

namespace media_xray {
int run_cli(int argc, char **argv) {
  cxxopts::Options options = make_help_options();
  options.add_options()("command", "Command to run",
                        cxxopts::value<std::string>());
  options.parse_positional({"command"});
  options.allow_unrecognised_options();

  cxxopts::ParseResult result;
  try {
    result = options.parse(argc, argv);
  } catch (const std::exception &ex) {
    log_error(ex.what());
    print_general_help();
    return EXIT_INVALID_ARGS;
  }

  if (result.count("log-level") > 0) {
    LogLevel level = LogLevel::INFO;
    const std::string value = result["log-level"].as<std::string>();
    if (!parse_log_level_value(value, level)) {
      log_error("Invalid value for --log-level");
      return EXIT_INVALID_ARGS;
    }
    set_log_level(level);
  }

  if (result.count("help") > 0) {
    print_general_help();
    return EXIT_OK;
  }

  if (result.count("version") > 0) {
    std::cout << media_xray::version_string() << "\n";
    return EXIT_OK;
  }

  if (result.count("command") == 0) {
    print_general_help();
    return EXIT_OK;
  }

  const std::string command = result["command"].as<std::string>();

  if (command == "help") {
    print_general_help();
    return EXIT_OK;
  }

  if (command == "analyze") {
    cxxopts::Options analyze_options("media-xray analyze",
                                     "Analyze the given input");
    analyze_options.positional_help("<input>");
    analyze_options.add_options()("h,help", "Print usage")("v,version",
                                                           "Print version")(
        "log-level", "Log level (error|warn|info|debug)",
        cxxopts::value<std::string>())("input", "Input path",
                                       cxxopts::value<std::string>());
    analyze_options.parse_positional({"input"});

    cxxopts::ParseResult analyze_result;
    try {
      const int command_index = find_command_index(argc, argv);
      if (command_index < 0) {
        log_error("Missing analyze command");
        return EXIT_INVALID_ARGS;
      }
      analyze_result =
          analyze_options.parse(argc - command_index, argv + command_index);
    } catch (const std::exception &ex) {
      log_error(ex.what());
      print_analyze_help();
      return EXIT_INVALID_ARGS;
    }

    if (analyze_result.count("help") > 0) {
      print_analyze_help();
      return EXIT_OK;
    }

    if (analyze_result.count("version") > 0) {
      std::cout << media_xray::version_string() << "\n";
      return EXIT_OK;
    }

    if (analyze_result.count("log-level") > 0) {
      LogLevel level = LogLevel::INFO;
      const std::string value = analyze_result["log-level"].as<std::string>();
      if (!parse_log_level_value(value, level)) {
        log_error("Invalid value for --log-level");
        return EXIT_INVALID_ARGS;
      }
      set_log_level(level);
    }

    if (analyze_result.count("input") == 0) {
      log_error("missing <input>");
      print_analyze_help();
      return EXIT_INVALID_ARGS;
    }

    log_info("Not implemented");
    return EXIT_OK;
  }

  if (!command.empty() && command[0] == '-') {
    log_error("unknown option");
    print_general_help();
    return EXIT_INVALID_ARGS;
  }

  log_error("unknown command");
  print_general_help();
  return EXIT_INVALID_ARGS;
}
} // namespace media_xray
