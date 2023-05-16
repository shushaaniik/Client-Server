#include "socket.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cassert>
#include <cstring>


void os::Socket::bind(unsigned short port)
{
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bind_status = ::bind(_socket_fd, (sockaddr*)&addr, sizeof(addr));
    if (bind_status == -1) {
        std::cerr << "bind:: " << strerror(errno) << std::endl;
        exit(errno);
    }
}

void os::Socket::listen(int size)
{
    int listen_status = ::listen(_socket_fd, size);
    if (listen_status == -1) {
        std::cerr << "listen:: " << strerror(errno) << std::endl;
        exit(errno);
    }
}

os::Socket os::Socket::accept()
{
    int sock_fd = ::accept(_socket_fd, nullptr, nullptr);
    if (sock_fd == -1) {
        std::cerr << "Can't accept client" << std::endl;
    }
    return Socket(sock_fd);
}

void os::Socket::connect(const char* ip, unsigned short int port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    int convertion_status = inet_pton(AF_INET, ip, &addr.sin_addr);
    if (convertion_status == 0) {
      std::cerr << "Error: Failed IP address convertion process\nNon-valid network address\n";
    }
    if (convertion_status == -1) {
      std::cerr << "Error: Failed IP address convertion process\nNon-valid address family\n";
    }
    int connect_status = ::connect(_socket_fd, (sockaddr*)&addr, sizeof(addr));
    if (connect_status == -1) {
      std::cerr << "Error: Failed connection process\n";
    }
}

int os::Socket::recv(void* buff, int length)
{
    return ::recv(_socket_fd, buff, length, 0);
}

int os::Socket::send(const void* buff, int length)
{
    return ::send(_socket_fd, buff, length, 0);
}

void os::Socket::close()
{
    ::close(_socket_fd);
}

os::Socket::Socket() {
  _socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if(_socket_fd < 0) {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
  }
}

os::Socket::Socket(int fd) : _socket_fd(fd) {}

os::Socket::Socket(const os::Socket& other) : _socket_fd(other._socket_fd){}
