/*
 * @title: input_v1.hpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#ifndef __IO_INPUT_V1_HPP__
#define __IO_INPUT_V1_HPP__

#include "../OBJECT/basis.hpp"
class InputFile5D {
 public:
  bool inputRule5D(std::vector<Rule_5D>&, const char*);
  bool inputPacket5D(std::vector<Packet_5D>&, const char*, std::vector<int>&);
};
#endif
