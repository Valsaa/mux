/**
 * \file socket.h
 * \brief Socket related struct and functions.
 * \author Valsaa
 * \version 0.1.0
 * \date 27/03/2024
 *
 * Manage socket through a SockAddr struct.
 *
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <string>

namespace mux {

/**
 * \struct SockAddr
 * \brief Encapsulate socket address data
 *
 * Data structure to encapsulate socket address data.
 *
 */
struct SockAddr {
  std::string hostname; /*!< represents either a hostname in internet domain
                           notation or an IPv4/IPv6 address  */
  int port;             /*!< port number */
};


/**
 * \fn void tcp_client(const SockAddr sockaddr, const std::string message)
 * \brief Run a blocking TCP client
 *
 * \param sockaddr Server socket address to connect to
 * \param message String to send to server socket address
 * \throw std::runtime_error
 */
void tcp_client(const SockAddr sockaddr, const std::string message);

/**
 * \fn void tcp_server(const SockAddr sockaddr)
 * \brief Run a blocking TCP server
 *
 * \param sockaddr Server socket address to listen to
 * \throw std::runtime_error
 */
void tcp_server(const SockAddr sockaddr);

/**
 * \fn int tcp_connect(const mux::SockAddr sockaddr)
 * \brief Connect to socket address
 *
 * \param sockaddr Server socket address to connect to
 * \throw std::runtime_error
 */
int tcp_connect(const mux::SockAddr sockaddr);

/**
 * \fn int tcp_listen(const mux::SockAddr sockaddr)
 * \brief Listen to socket address
 *
 * \param sockaddr Server socket address to listen to
 * \throw std::runtime_error
 */
int tcp_listen(const mux::SockAddr sockaddr);
}  // namespace mux

#endif  // SOCKET_H
