/**
 * @file input.hpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.2
 * @date 2024-02-03
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-03 <td>1.1     <td>jiachang     <td>load rule-set and trace-set
 * </table>
 */

#ifndef __IO_INPUT_HPP__
#define __IO_INPUT_HPP__

#include "../lib/basis.hpp"
#include <vector>

class InputFile5D
{
public:
  bool loadRule5D(std::vector<Rule5D> &, const char *);
  bool loadPacket5D(std::vector<Packet5D> &, const char *);
};
#endif
