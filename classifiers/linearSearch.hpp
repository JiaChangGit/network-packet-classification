/**
 * @file LinearSearch.hpp
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
 * <tr><td>2024-02-11 <td>1.5     <td>jiachang     <td>brutely linear search
 * </table>
 */

#ifndef _CLASSIFIERS_LINEARSEARCH_HPP_
#define _CLASSIFIERS_LINEARSEARCH_HPP_

#include <fstream>

#include "../lib/basis.hpp"

class LinearSearch {
 public:
  LinearSearch() : memorySize(0), packetCounter(0){};
  void search(std::vector<Rule5D> &, const std::vector<Packet5D> &);

 private:
  const char *LinearSearch_path = "./INFO/LinearSearch_FaultPacket5D_test.txt";
  unsigned long long memorySize;
  unsigned long long packetCounter;
};

#endif
