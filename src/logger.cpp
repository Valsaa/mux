#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>

auto setup_logger() -> void {
  auto stdout = spdlog::stdout_color_mt("stdout");
  spdlog::set_default_logger(stdout);
  spdlog::set_level(spdlog::level::debug);
}
