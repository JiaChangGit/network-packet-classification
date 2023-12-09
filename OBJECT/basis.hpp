/*
 * @title: basis.hpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#ifndef __OBJECT_BASIS_HPP__
#define __OBJECT_BASIS_HPP__
#include <getopt.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

class Rule_5D {
 public:
  unsigned int pri = 0;
  uint8_t ipS[5];
  uint8_t ipD[5];
  uint16_t portS[2];
  uint16_t portD[2];
  uint8_t protocol[2];
};

class Packet_5D {
 public:
  uint16_t portS;
  uint16_t portD;

  uint8_t ipS[4];
  uint8_t protocol;
  uint8_t ipD[4];
};

class Dialog {
 private:
  uint64_t memSize = 0;

  // Type aliases to make accessing nested type easier
  using Clock = std::chrono::steady_clock;
  using Second = std::chrono::duration<double, std::ratio<1> >;

  std::chrono::time_point<Clock> m_beg{Clock::now()};

 public:
  uint64_t getMemSize();
  void memReset();
  void timeReset();
  double elapsed_s() const;
  unsigned long long elapsed_ns() const;
};

#endif

// https://www.learncpp.com/cpp-tutorial/timing-your-code/
// Dialog using ex:
// int main()
// {
//     std::array<int, g_arrayElements> array;
//     std::iota(array.rbegin(), array.rend(), 1);
//     Dialog t;
//     sortArray(array);
//     std::cout << "Time taken: " << t.elapsed_s() << " seconds\n";
//     return 0;
// }