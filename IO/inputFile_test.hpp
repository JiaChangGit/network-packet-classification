/**
 * @file inputFile_test.hpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.0
 * @date 2024-02-03
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-03 <td>1.0     <td>jiachang     <td>test loading rule-set and loading trace-set
 * </table>
 */

#ifndef __IO_TEST_INPUTFILE_TEST_HPP__
#define __IO_TEST_INPUTFILE_TEST_HPP__

#include "../LIBRARY/basis.hpp"
#include <fstream>
#include <vector>

class InputFile5D_test
{
public:
  bool loadRule5D_test(std::vector<Rule5D> &, const char *);
  bool loadPacket5D_test(std::vector<Packet5D> &, const char *);
};
#endif
