#include "talker.hpp"
#include <iostream>

// Maximum number of sockets in listen queue 
#define MAX_CLIENTS 10

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "2 arguments required" << std::endl <<
                 "Usage: " << argv[0] << " <port>" << std::endl;
    exit(-1);
  }
  int port = std::atoi(argv[1]);

  os::Socket server;
  server.bind(port);  
  server.listen(MAX_CLIENTS);

  while(true) {
    os::Socket client = server.accept();
    os::Talker* talker = new os::Talker(client);
    talker->run();
  }

  server.close();

  return 0;
}