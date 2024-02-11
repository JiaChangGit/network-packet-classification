/**
 * @file basis.hpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.4
 * @date 2024-02-11
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>basic data structures
 * </table>
 */

#ifndef __LIB_BASIS_HPP__
#define __LIB_BASIS_HPP__

#include <chrono>
#include <iostream>

class Packet5D {
 public:
  uint16_t portS;
  uint16_t portD;
  union {
    uint8_t ipS[4];
    uint32_t ipS32;
  };
  uint8_t protocol;
  union {
    uint8_t ipD[4];
    uint32_t ipD32;
  };

  void eightBitsGroup_ip_merge();
};

class Rule5D {
 public:
  unsigned int pri = 0;
  union {
    uint8_t ipS[4];
    uint32_t ipS32;
  };
  union {
    uint8_t ipD[4];
    uint32_t ipD32;
  };
  uint16_t portS[2];
  uint16_t portD[2];
  uint8_t ipSMask;
  uint8_t ipDMask;
  uint8_t protocol[2];

  void eightBitsGroup_ip_merge();
  bool isMatch(const Packet5D &);
};

class Timer {
 private:
  // Type aliases to make accessing nested type easier
  using Clock = std::chrono::steady_clock;
  using Second = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<Clock> m_beg{Clock::now()};

 public:
  void timeReset();
  double elapsed_s() const;
  unsigned long long elapsed_ns() const;
};

// https://www.learncpp.com/cpp-tutorial/timing-your-code/
// Timer using ex:
// int main()
// {
//     std::array<int, g_arrayElements> array;
//     std::iota(array.rbegin(), array.rend(), 1);
//     Timer t;
//     sortArray(array);
//     std::cout << "Time taken: " << t.elapsed_s() << " seconds\n";
//     return 0;
// }

#endif
