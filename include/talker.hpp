#ifndef TALKER_HPP
#define TALKER_HPP

#include "socket.hpp"
#include "thread_pool.hpp"

namespace os 
{
  class Talker
  {
    private:
      Socket _socket;
      os::output_t talk(os::input_t);
    public:
      Talker(const os::Socket& sock);
      void run();
  };
}

#endif