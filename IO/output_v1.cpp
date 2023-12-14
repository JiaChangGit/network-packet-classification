#/*
* @title: output_v1.cpp
* @author: Jia-Chang, Chang
* @date: 2023-12-10
*/
#include "output_v1.hpp"

uint64_t OutputFile5D::getMemSize() { return this->memSize; };
void OutputFile5D::memReset() { this->memSize = 0; };

void OutputFile5D::gen_trace(std::vector<Packet_5D>& packets,
                             std::vector<Rule_5D>& rules, unsigned int size) {
  std::random_device seed;
  std::mt19937 rd(seed());
  std::uniform_int_distribution<> dis(0, rules.size() - 1);

  unsigned int protocol[] = {1, 2, 3, 4, 5, 6, 7, 8, 17, 47, 50, 51, 88, 89};

  unsigned int sip, dip, index;
  unsigned short sport, dport;
  unsigned int smask, dmask;
  for (unsigned int i = 0; i < size; i++) {
    Packet_5D p;
    index = dis(rd);
    memcpy(&sip, rules[index].ipS, sizeof(int));
    memcpy(&dip, rules[index].ipD, sizeof(int));
    smask = rules[index].ipSMask;
    dmask = rules[index].ipDMask;
    if (smask == 0)
      sip = rd();
    else if (smask < 32) {
      int mbit = 32 - smask;
      unsigned int temp = sip >> mbit;
      temp = (temp << mbit) + (rd() % (1 << mbit));
      if (temp >> mbit == sip >> mbit)
        sip = temp;
      else
        fprintf(stderr, "Error - gen sip error.\n");
    }
    memcpy(p.ipS, &sip, sizeof(int));
    if (dmask == 0)
      dip = rd();
    else if (dmask < 32) {
      int mbit = 32 - dmask;
      unsigned int temp = dip >> mbit;
      temp = (temp << mbit) + (rd() % (1 << mbit));
      if (temp >> mbit == dip >> mbit)
        dip = temp;
      else
        fprintf(stderr, "Error - gen dip error.\n");
    }
    memcpy(p.ipD, &dip, sizeof(int));
    int Pwidth = rules[index].portS[1] - rules[index].portS[0];
    if (Pwidth == 0)
      sport = rules[index].portS[0];
    else {
      sport = rd() % Pwidth + rules[index].portS[0];
      if (sport < rules[index].portS[0] || sport > rules[index].portS[1])
        fprintf(stderr, "Error - gen sport error.\n");
    }
    p.portS = sport;
    Pwidth = rules[index].portD[1] - rules[index].portD[0];
    if (Pwidth == 0)
      dport = rules[index].portD[0];
    else {
      dport = rd() % Pwidth + rules[index].portD[0];
      if (dport < rules[index].portD[0] || dport > rules[index].portD[1])
        fprintf(stderr, "Error - gen dport error.\n");
    }
    p.portD = dport;
    if (rules[index].protocol[0] == 0)
      p.protocol = protocol[rd() % (sizeof(protocol) / 4)];
    else
      p.protocol = rules[index].protocol[1];
    packets.emplace_back(p);
  }
}
