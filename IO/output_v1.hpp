/*
 * @title: output_v1.hpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-10
 */
#ifndef __IO_OUTPUT_V1_HPP__
#define __IO_OUTPUT_V1_HPP__
#include "../OBJECT/basis.hpp"
class OutputFile5D {
 public:
  uint64_t memSize = 0;
  Timer timer;

  uint64_t getMemSize();
  void memReset();

  void gen_trace(std::vector<Packet_5D>& packets, std::vector<Rule_5D>& rules,
                 unsigned int size);
};

#endif
