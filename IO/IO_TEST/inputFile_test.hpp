/*
 * @title: inputFile_test.hpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#ifndef __IO_TEST_INPUTFILE_TEST_HPP__
#define __IO_TEST_INPUTFILE_TEST_HPP__
#include "../../OBJECT/basis.hpp"
class InputFile5D_test {
 public:
  bool inputRule5D_test(std::vector<Rule_5D>&, const char*);
  bool inputPacket5D_test(std::vector<Packet_5D>&, const char*,
                          std::vector<int>&);
};
#endif
