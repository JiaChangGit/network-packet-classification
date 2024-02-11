/**
 * @file input.hpp
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
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>load rule-set and
 * trace-set
 * </table>
 */

#ifndef __IO_INPUT_HPP__
#define __IO_INPUT_HPP__

#include <cstring>
#include <vector>

#include "../lib/basis.hpp"

class InputFile5D {
 public:
  void loadRule5D(std::vector<Rule5D> &, const char *);
  void loadPacket5D(std::vector<Packet5D> &, const char *);
};
#endif
