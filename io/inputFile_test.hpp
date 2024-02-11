/**
 * @file inputFile_test.hpp
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
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>test loading rule-set and
 * loading trace-set
 * </table>
 */

#ifndef __IO_INPUTFILE_TEST_HPP__
#define __IO_INPUTFILE_TEST_HPP__

#include <fstream>
#include <vector>

#include "../lib/basis.hpp"

class InputFile5D_test {
 public:
  void loadRule5D_test(const std::vector<Rule5D> &, const char *);
  void loadPacket5D_test(const std::vector<Packet5D> &, const char *);
  void loadRule5D_ip_test(const std::vector<Rule5D> &, const char *);
  void loadPacket5D_ip_test(const std::vector<Packet5D> &, const char *);
};
#endif
