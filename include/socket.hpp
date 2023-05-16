#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace os 
{
  class Socket 
  {
  private:
    int _socket_fd;
  public:
    void bind(unsigned short port);
    void listen(int size);
    Socket accept();
    void connect(const char* ip, unsigned short port);
    int recv(void* buff, int length);
    int send(const void* buff, int length);
    void close();

    Socket();
    Socket(int);
    Socket(const Socket&);
    ~Socket() = default;
  };
}


#endif