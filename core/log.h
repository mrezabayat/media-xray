#pragma once

#include <string_view>

namespace media_xray {
enum class LogLevel { ERROR, WARN, INFO, DEBUG };

void set_log_level(LogLevel level);
LogLevel log_level();

void log_error(std::string_view message);
void log_warn(std::string_view message);
void log_info(std::string_view message);
void log_debug(std::string_view message);
} // namespace media_xray
