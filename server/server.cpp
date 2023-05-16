#include <iostream>
#include <cmath>
#include <cstring>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

// Maximum number of threads in the thread pool
#define MAX_THREADS 10

// Queue for holding incoming connection requests
std::queue<int> connection_queue;

// Mutex for safe connection queue
std::mutex connection_mutex;

// condition variable for signaling when a new connection is requested
std::condition_variable connection_cv;

// Function for checking if the number is prime
bool is_prime(int num) {
  if(num <= 1) { return false; }
  if(num <= 3) { return true; }
  if(num % 2 == 0 || num % 3 == 0) { return false; }
  for(int i = 5; i * i <= num; i++) {
    if(num % i == 0) { return false; }
  }
  return true;
}

// Function for finding the n-th prime number
long long int calculate_prime(int n) {
  if (n <= 0) return 0;
  long long int count = 0;
  long long int num = 2;
  while (count < n) {
    if (is_prime(num)) { count++; }
    num++;
  }
  return num - 1;
}

// Function to handle client connections
void handleConnection(int clientSocket)
{
  // Receive the input number from the client
  int inputNumber;
  if (recv(clientSocket, &inputNumber, sizeof(inputNumber), 0) != sizeof(inputNumber))
  {
    std::cerr << strerror(errno) << std::endl;
    close(clientSocket);
    exit(errno);
  }

  // Calculate the n-th prime number
  long long int result = calculate_prime(inputNumber);

  // Send the calculated number back to the client
  if (send(clientSocket, &result, sizeof(result), 0) != sizeof(result))
  {
    std::cerr << "Failed to send result to client" << std::endl;
  }

  // Close the client socket
  close(clientSocket);
}

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "2 arguments required" << std::endl <<
                 "Usage: " << argv[0] << " <port>" << std::endl;
    exit(-1);
  }
  int port = std::atoi(argv[1]);
  
  // Create a thread pool
  std::vector<std::thread> thread_pool(MAX_THREADS);

  // Create a TCP socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0)
  {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
  }

  // Bind the socket to the specified port
  sockaddr_in serverAddress;

  // For security doing memset()
  memset(&serverAddress, 0, sizeof(sockaddr_in));

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);
  if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1)
  {
   std::cerr << strerror(errno) << std::endl;
   close(serverSocket);
   exit(errno);    
  }

  // Listen for incoming connections
  if (listen(serverSocket, SOMAXCONN) == -1)
  {
    std::cerr << strerror(errno) << std::endl;
    close(serverSocket);
    exit(errno);
  }

  // Accept and handle client connections
  while (true)
  {
    // Accept a client connection
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    memset(&clientAddress, 0, clientAddressLength);
    int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
    if (clientSocket == -1)
    {
      std::cerr << strerror(errno) << std::endl;
      continue;
    }

    // Create a new thread to handle the client connection
    std::thread clientThread(handleConnection, clientSocket);
    clientThread.detach();
  }

  // Close the server socket
  close(serverSocket);
  return 0;
}