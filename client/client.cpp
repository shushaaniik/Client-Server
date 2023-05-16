#include "socket.hpp"
#include <iostream>


int main(int argc, char** argv) {
  if(argc != 3) {
    std::cerr << "3 arguments required" << std::endl <<
                 "Usage: " << argv[0] << " <hostname> <port>" << std::endl;
    exit(-1);
  }

  const char* ip = argv[1];
  int port = atoi(argv[2]);

  os::Socket client;
  client.connect(ip, port);

  while(true) {
    int num = 0;
    std::cout << "Enter number(0 to quit): ";
    std::cin >> num;
    if(!num) { break; }

    client.send(&num, sizeof(num));

    long long int result;
    client.recv(&result, sizeof(result));

    std::cout << "Result: " << result << std::endl;
  }

  client.close();

  return 0;
}