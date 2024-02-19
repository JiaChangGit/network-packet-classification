#ifndef _CLASSIFIERS_KSETSEARCH_HPP_
#define _CLASSIFIERS_KSETSEARCH_HPP_

#include <cmath>
#include <fstream>
#include <vector>

#include "../lib/basis.hpp"

class KsetSearch {
 public:
  KsetSearch()
      : memorySize(0),
        packetCounter(0),
        subsetNum{0},
        usedBits{0},
        Threshold1(0),
        Threshold2(0){};
  void partition(std::vector<Rule5D> &, const size_t, const size_t);
  void search(std::vector<Rule5D> &, const std::vector<Packet5D> &);

 private:
  unsigned long long memorySize;
  unsigned long long packetCounter;
  std::vector<Rule5D> subset0;
  std::vector<Rule5D> subset1;
  std::vector<Rule5D> subset2;
  std::vector<Rule5D> subset3;
  size_t subsetNum[4];
  int usedBits[3];
  const size_t Threshold1;
  const size_t Threshold2;

  struct BigSegment {
    int uf = -1;      // used exact field
    int bf = -1;      // -1: not use, 0: list, 1: hash
    int ub = 0;       // hash table used bits
    int ht_size = 0;  // hash table size

    std::vector<Rule5D> list;    // smaller than threshold2
    std::vector<Rule5D> *htPtr;  // need to hash
  };
  struct SegmentNode {
    std::vector<Rule5D> smallSegList;

    // -1 = NULL, 0 = Small, 1 = Big; flag
    int segFlag = -1;

    // four hash table or list, the number is the search order
    BigSegment bigSeg[4];
    // 0 = small group, 1 = big group; r_flag
    int groupFlag = -1;
    int r_max_pri = 0;
    int rp_max_pri[3] = {0};
    std::vector<Rule5D> rmd;      // remainder
    std::vector<Rule5D> rmdp[3];  // partition with protocol, tcp, udp, other
  };
};

#endif
