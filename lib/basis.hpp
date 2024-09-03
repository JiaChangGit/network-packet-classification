/**
 * @file basis.hpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.5
 * @date 2024-02-11
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-11 <td>1.5     <td>jiachang     <td>basic data structures
 * </table>
 */

#ifndef __LIB_BASIS_HPP__
#define __LIB_BASIS_HPP__

#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#define LowDim 0
#define HighDim 1
#define MAXDIMENSIONS 5

typedef std::vector<uint32_t> Packet5D;

struct Rule5D {
  Rule5D(unsigned int dim = 5)
      : dim(dim), priority(0), range(dim, {{0, 0}}), prefix_length(dim, 0) {};

  unsigned int dim;
  unsigned int priority;

  std::vector<uint32_t> prefix_length;

  std::vector<std::array<uint32_t, 2>> range;

  bool inline isMatch(const Packet5D& p) const {
    for (size_t i = 0; i < dim; i++) {
      if (p[i] < range[i][LowDim] || p[i] > range[i][HighDim]) return false;
    }
    return true;
  }
};

class Timer {
 private:
  // Type aliases to make accessing nested type easier
  using Clock = std::chrono::steady_clock;
  using Second = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<Clock> m_beg{Clock::now()};

 public:
  void inline timeReset() { m_beg = Clock::now(); };
  double inline elapsed_s() const {
    return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
  };
  unsigned long long inline elapsed_ns() const {
    return std::chrono::milliseconds((Clock::now() - m_beg).count()).count();
  };
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
