/**
 * @file LinearSearch.hpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-04 <td>1.1     <td>jiachang     <td>description
 * </table>
 */

#ifndef _CLASSIFIERS_LINEARSEARCH_HPP_
#define _CLASSIFIERS_LINEARSEARCH_HPP_

#include "../lib/basis.hpp"
#include <vector>

class LinearSearch
{
public:
  void search(std::vector<Rule5D> &, const std::vector<Packet5D> &);

private:
  static unsigned long long memorySize;
};

#endif
