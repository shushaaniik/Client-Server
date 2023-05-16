#include "prime_nums.hpp"

bool is_prime(int num) {
  if(num <= 1) { return false; }
  if(num <= 3) { return true; }
  if(num % 2 == 0 || num % 3 == 0) { return false; }
  for(int i = 5; i * i <= num; i++) {
    if(num % i == 0) { return false; }
  }
  return true;
}

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