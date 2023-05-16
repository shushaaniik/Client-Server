#include "talker.hpp"
#include "prime_nums.hpp"
#include "thread_pool.hpp"
#include <iostream>
#include <cstring>

os::Talker::Talker(const os::Socket& socket) : _socket(socket) {}

void os::Talker::run() {
  os::Talker talker(_socket);
  auto entryPoint = [&talker](os::input_t input) {
    return talker.talk(input);
  };

  os::threadpool::instance().enqueue_work(static_cast<os::entry_point_t>(entryPoint),
                                          NULL, NULL);
  std::cout << "Connected.\n";
}

os::output_t os::Talker::talk(os::input_t arg) {
  while(true) { 
    // Receive the input number from the client
    int input_number;
    if(_socket.recv(&input_number, sizeof(input_number)) != sizeof(input_number))
    {
      std::cerr << strerror(errno) << std::endl;
      exit(errno);
    }

    // Calculate the n-th prime number
    long long int result = calculate_prime(input_number);

    // Send the calculated number back to the client
    if(_socket.send(&result, sizeof(result)) != sizeof(result)) {
      std::cerr << strerror(errno) << std::endl;
      exit(errno);
    }
  }

  // Close the client socket
  _socket.close();
  return NULL;
}