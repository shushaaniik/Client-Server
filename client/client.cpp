#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>


int main(int argc, char** argv) {
  if(argc != 3) {
    std::cerr << "3 arguments required" << std::endl <<
                 "Usage: " << argv[0] << " <hostname> <port>" << std::endl;
    exit(-1);
  }

  const char* host = argv[1];
  int port = atoi(argv[2]);

  // create a socket for the client to connect to the server
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0)
  {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
  }

  // Bind the socket to the specified port
  sockaddr_in serverAddress;

  // For security doing memset()
  memset(&serverAddress, 0, sizeof(sockaddr_in));

  // Connect to the server
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = inet_addr(host);
  serverAddress.sin_port = htons(port);
  if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), 
              sizeof(serverAddress)) == -1) {
    std::cerr << strerror(errno) << std::endl;
    close(clientSocket);
    exit(errno);
  }

  while(true) {
    int num;
    std::cout << "Enter number: ";
    std::cin >> num;
    if(!num) { break; }

    if(send(clientSocket, &num, sizeof(num), 0) < 0) {
      std::cerr << strerror(errno) << std::endl;
      exit(errno);
    }

    long long int result;

    if(recv(clientSocket, &result, sizeof(result), 0) <= 0) {
      std::cerr << strerror(errno) << std::endl;
      exit(errno);
    }

    std::cout << "Result: " << result << std::endl;
  }

  close(clientSocket);
  return 0;
}