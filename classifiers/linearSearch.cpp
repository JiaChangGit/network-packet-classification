/**
 * @file linearSearch.cpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.2
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-04 <td>1.1     <td>jiachang     <td>brutely linear search
 * </table>
 */

#include "linearSearch.hpp"

unsigned long long LinearSearch::memorySize = 0;

void LinearSearch::search(std::vector<Rule5D> &rule5V, const std::vector<Packet5D> &packet5V)
{
  for (const auto &packet : packet5V)
  {
    for (auto &rule : rule5V)
    {
      if (rule.isMatch(packet))
      {
        // std::cout << "match: " << rule.pri << "\n";
        break;
      }
    }
  }
};
