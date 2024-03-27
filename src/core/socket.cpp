#include "socket.h"

#include <netdb.h>
#include <spdlog/spdlog.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <exception>
#include <string>

namespace mux {

int tcp_connect(const SockAddr sockaddr);
int tcp_listen(const SockAddr sockaddr);

void tcp_client(const SockAddr sockaddr, const std::string message) {
  // Connect to hostname:port by opening socket
  auto sfd = mux::tcp_connect(sockaddr);
  spdlog::info("successful connection to {}:{}", sockaddr.hostname,
               sockaddr.port);

  ssize_t nread{0};
  if ((nread = send(sfd, message.data(), message.size(), 0)) == -1) {
    spdlog::error("write error: {}", std::strerror(errno));
  }

  spdlog::debug("send {} bytes: {}", nread, message.data());

  if (static_cast<std::size_t>(nread) != message.size()) {
    spdlog::warn("tried to send {} bytes but only {} bytes were sent",
                 sizeof(message.data()), nread);
  }
}

void tcp_server(const SockAddr sockaddr) {
  std::string host(NI_MAXHOST, '\0');
  std::string service(NI_MAXSERV, '\0');
  sockaddr_storage peer_addr{};
  socklen_t peer_addrlen{sizeof(peer_addr)};
  auto cfd{0};
  ssize_t nread{0};

  const auto BUFFER_SIZE{20};
  std::array<char, BUFFER_SIZE> buffer = {0};
  auto sfd = mux::tcp_listen(sockaddr);
  spdlog::info("listening to {}:{}", sockaddr.hostname, sockaddr.port);

  for (;;) {
    // Accept an incoming connection (blocking call)
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    if ((cfd = accept(sfd, reinterpret_cast<struct sockaddr*>(&peer_addr),
                      &peer_addrlen)) == -1) {
      spdlog::error(std::strerror(errno));
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    const auto status = getnameinfo(
        reinterpret_cast<struct sockaddr*>(&peer_addr), peer_addrlen,
        host.data(), NI_MAXHOST, service.data(), NI_MAXSERV, NI_NUMERICSERV);
    if (status != 0) {
      spdlog::error(gai_strerror(status));
    }

    spdlog::debug("accepted incoming connection from {}:{}", host, service);

    // Read bytes from accepted connection
    if ((nread = recv(cfd, buffer.data(), buffer.size(), 0)) == -1) {
      spdlog::error(std::strerror(errno));
    }

    spdlog::debug("received {} bytes from {}:{}", nread, host, service);
    spdlog::info("received message from {}:{}: {}", host, service,
                 buffer.data());
  }
}

int tcp_connect(const SockAddr sockaddr) {
  // Translate network address
  addrinfo* addrs{nullptr};
  const addrinfo hints{0, AF_UNSPEC, SOCK_STREAM, 0,
                       0, nullptr,   nullptr,     nullptr};
  const auto status =
      getaddrinfo(sockaddr.hostname.c_str(),
                  std::to_string(sockaddr.port).c_str(), &hints, &addrs);
  if (status != 0) {
    throw std::runtime_error(gai_strerror(status));
  }
  if (addrs == nullptr) {
    throw std::runtime_error("translation error for " + sockaddr.hostname +
                             ":" + std::to_string(sockaddr.port));
  }

  spdlog::debug("network addresses translated from {}:{}", sockaddr.hostname,
                sockaddr.port);

  auto sfd{0};
  addrinfo* addr{nullptr};
  // Run throught all addresses found by getaddrinfo and try to create a
  // connection
  for (addr = addrs; addr != nullptr; addr = addr->ai_next) {
    // Creating socket file descriptor and continue to next address if error
    sfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sfd == -1) continue;

    spdlog::debug("opened socket {}", sfd);

    // If connection on current socket file descriptor is successful we leave
    // here
    if (connect(sfd, addr->ai_addr, addr->ai_addrlen) != -1) break;

    spdlog::debug("connection failed with socket {}", sfd);

    // If connection on current socket file descriptor is unsuccessful we close
    // the current opened socket
    close(sfd);

    spdlog::debug("closed socket {}", sfd);
  }

  // addrs no longer needed after for loop
  freeaddrinfo(addrs);

  // nullptr would mean no socket have been able to connect among available
  // addrs
  if (addr == nullptr) {
    throw std::runtime_error(std::strerror(errno));
  }

  spdlog::debug("connection successful with socket {}", sfd);

  return sfd;
}

int tcp_listen(const SockAddr sockaddr) {
  // Translate network address
  addrinfo* addrs{nullptr};
  const addrinfo hints{AI_PASSIVE, AF_UNSPEC, SOCK_STREAM, 0,
                       0,          nullptr,   nullptr,     nullptr};
  const auto status =
      getaddrinfo(sockaddr.hostname.c_str(),
                  std::to_string(sockaddr.port).c_str(), &hints, &addrs);
  if (status != 0) {
    throw std::runtime_error(gai_strerror(status));
  }

  spdlog::debug("network addresses translated from {}", sockaddr.port);

  const auto opt{1};
  auto sfd{0};
  addrinfo* addr{nullptr};
  // Run throught all addresses found by getaddrinfo and try to create a
  // connection
  for (addr = addrs; addr != nullptr; addr = addr->ai_next) {
    // Creating socket file descriptor and continue to next address if error
    if ((sfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) ==
        -1) {
      continue;
    }
    spdlog::debug("opened socket {}", sfd);

    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)) == -1) {
      close(sfd);
      continue;
    }

    // Bind the socket to the network address and port provided
    if (bind(sfd, addr->ai_addr, addr->ai_addrlen) == 0) break;
    close(sfd);
  }

  // Addresses no longer needed after for loop
  freeaddrinfo(addrs);

  // nullptr would mean no socket have been able to connect among available
  // addrs
  if (addr == nullptr) {
    throw std::runtime_error(std::strerror(errno));
  }

  // Listen for connection to
  if (listen(sfd, 3) != 0) {
    throw std::runtime_error(std::strerror(errno));
  }

  spdlog::debug("listen successful with socket {}", sfd);

  return sfd;
}
}  // namespace mux
