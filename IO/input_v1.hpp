/*
 * @title: input_v1.hpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#ifndef __IO_INPUT_V1_HPP__
#define __IO_INPUT_V1_HPP__

#include "../OBJECT/basis.hpp"
void reverseMemcpy(void* dest, const void* src, size_t size) {
  const char* srcBytes = static_cast<const char*>(src);
  char* destBytes = static_cast<char*>(dest);

  for (size_t i = 0; i < size; ++i) {
    destBytes[i] = srcBytes[size - 1 - i];
  }
}
class InputFile5D {
 public:
  bool inputRule5D(std::vector<Rule_5D>&, const char*);
  bool inputPacket5D(std::vector<Packet_5D>&, const char*);
  void rule_5D_ip_merge(std::vector<Rule_5D>&);
  void packet_5D_ip_merge(std::vector<Packet_5D>&);
};
#endif
