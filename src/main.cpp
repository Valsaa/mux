#include <spdlog/spdlog.h>

#include <cxxopts.hpp>
#include <iostream>

#include "core/socket.h"
#include "logger.h"

int main(const int argc, const char *argv[]) {
  mux::SockAddr sockaddr{};
  std::string message{""};
  bool listen{false};

  // Setup logger

  try {
    setup_logger();
  } catch (const spdlog::spdlog_ex &ex) {
    std::cerr << "Log initialization failed: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  // Parse arguments

  // clang-format off
  cxxopts::Options options("TCP Mux", "A TCP/IP multiplexer");
  options.add_options()
    ("h, help", "help page")
    ("l, listen", "enable listen mode")
    ("hostname", "hostname", cxxopts::value<std::string>())
    ("port", "port number", cxxopts::value<int>())
    ("message", "message to send", cxxopts::value<std::string>());
  // clang-format on

  try {
    auto result{options.parse(argc, argv)};
    if (result.count("help")) {
      std::cout << options.help() << std::endl;
      return EXIT_SUCCESS;
    }

    // Change parsing of positional arguments based on listen parameter
    if (result.count("listen")) {
      listen = true;
      options.parse_positional({"port"});
      result = options.parse(argc, argv);
    } else {
      listen = false;
      options.parse_positional({"hostname", "port", "message"});
      result = options.parse(argc, argv);
    }

    if (result.count("hostname")) {
      sockaddr.hostname = result["hostname"].as<std::string>();
    }

    if (result.count("port")) {
      sockaddr.port = result["port"].as<int>();
    }

    if (result.count("message")) {
      message = result["message"].as<std::string>();
    }
  } catch (const std::exception &e) {
    spdlog::error("Error while parsing options: {}", e.what());
    return EXIT_FAILURE;
  }

  // Run application in client or server mode

  if (listen) {
    try {
      mux::tcp_server(sockaddr);
    } catch (const std::runtime_error &e) {
      spdlog::error("server failed: {}", e.what());
      return EXIT_FAILURE;
    }
  } else {
    try {
      mux::tcp_client(sockaddr, message);
    } catch (const std::runtime_error &e) {
      spdlog::error("client failed: {}", e.what());
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
