#include "log.h"

#include <atomic>
#include <iostream>
#include <memory>

#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/spdlog.h>

namespace media_xray {
namespace {
int level_rank(LogLevel level) {
  switch (level) {
  case LogLevel::DEBUG:
    return 0;
  case LogLevel::INFO:
    return 1;
  case LogLevel::WARN:
    return 2;
  case LogLevel::ERROR:
    return 3;
  }
  return 1;
}

bool should_log(LogLevel message_level, LogLevel current) {
  return level_rank(message_level) >= level_rank(current);
}

std::shared_ptr<spdlog::logger> &stdout_logger() {
  static std::shared_ptr<spdlog::logger> logger = []() {
    auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(std::cout);
    auto log = std::make_shared<spdlog::logger>("media_xray_stdout", sink);
    log->set_level(spdlog::level::debug);
    log->set_pattern("[%L] %v");
    return log;
  }();
  return logger;
}

std::shared_ptr<spdlog::logger> &stderr_logger() {
  static std::shared_ptr<spdlog::logger> logger = []() {
    auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(std::cerr);
    auto log = std::make_shared<spdlog::logger>("media_xray_stderr", sink);
    log->set_level(spdlog::level::debug);
    log->set_pattern("[%L] %v");
    return log;
  }();
  return logger;
}

std::atomic<LogLevel> &current_level() {
  static std::atomic<LogLevel> level{LogLevel::INFO};
  return level;
}
} // namespace

void set_log_level(LogLevel level) { current_level().store(level); }

LogLevel log_level() { return current_level().load(); }

void log_error(std::string_view message) {
  if (!should_log(LogLevel::ERROR, log_level())) {
    return;
  }
  stderr_logger()->error("{}", message);
}

void log_warn(std::string_view message) {
  if (!should_log(LogLevel::WARN, log_level())) {
    return;
  }
  stderr_logger()->warn("{}", message);
}

void log_info(std::string_view message) {
  if (!should_log(LogLevel::INFO, log_level())) {
    return;
  }
  stdout_logger()->info("{}", message);
}

void log_debug(std::string_view message) {
  if (!should_log(LogLevel::DEBUG, log_level())) {
    return;
  }
  stdout_logger()->debug("{}", message);
}
} // namespace media_xray
