#ifndef _CLASSIFIERS_TSEARCH_HPP_
#define _CLASSIFIERS_TSEARCH_HPP_

#include <algorithm>
#include <fstream>
#include <vector>

#include "../io/inputFile_test.hpp"
#include "../lib/basis.hpp"
#include "../lib/rulesetAnalysis.hpp"
class TSearch {
 public:
  TSearch(const size_t _Threshold1, const size_t _BucketNum)
      : memorySize(0),
        packetCounter(0),
        exactSubNum(0),
        exactSub_ipSNum(0),
        exactSub_ipDNum(0),
        exactSub_portDNum(0),
        smallSubNum(0),
        zeroSubNum(0),
        smallSubListNum{0},
        bigSubNum(0),
        Threshold1(_Threshold1),
        BucketNum(_BucketNum),
        exactHashTable(BucketNum){

        };
  void partition(std::vector<Rule5D> &, const size_t);
  void partitionExactSub(std::vector<Rule5D> &);
  void partitionExactSub_ipS(std::vector<Rule5D> &);
  void partitionExactSub_ipD(std::vector<Rule5D> &);
  void partitionExactSub_portD(std::vector<Rule5D> &);

  inline bool comparePri(const Rule5D &a, const Rule5D &b) {
    return a.pri < b.pri;
  }
  inline bool compareIpS(const Rule5D &a, const Rule5D &b) {
    return a.ipS32 < b.ipS32;
  }
  inline bool compareIpD(const Rule5D &a, const Rule5D &b) {
    return a.ipD32 < b.ipD32;
  }
  inline bool comparePortD(const Rule5D &a, const Rule5D &b) {
    return a.portD[0] < b.portD[0];
  }
  inline size_t u64Hash(const uint64_t Val) { return Val % BucketNum; };
  inline size_t u32Hash(const uint32_t Val) { return Val % BucketNum; };
  inline size_t u16Hash(const uint16_t Val) { return Val % BucketNum; };

  inline void insertU64HashTable(std::vector<Rule5D> &);
  inline void insertU32HashTable(std::vector<Rule5D> &);
  inline void insertU16HashTable(std::vector<Rule5D> &);
  void search(std::vector<Rule5D> &, const std::vector<Packet5D> &);

 private:
  unsigned long long memorySize;
  unsigned long long packetCounter;
  const size_t Threshold1;
  const size_t BucketNum;
  // === //
  std::vector<Rule5D> exactSub;
  size_t exactSubNum;
  std::vector<Rule5D> exactSub_ipS;
  size_t exactSub_ipSNum;
  std::vector<Rule5D> exactSub_ipD;
  size_t exactSub_ipDNum;
  std::vector<Rule5D> exactSub_portD;
  size_t exactSub_portDNum;
  std::vector<Rule5D> tmpSmallSub;
  size_t smallSubNum;
  // === //
  std::vector<Rule5D> zeroSub;
  size_t zeroSubNum;
  // === //
  // === //
  std::vector<Rule5D> smallSubList0;
  std::vector<Rule5D> smallSubList1;
  std::vector<Rule5D> smallSubList2;
  std::vector<Rule5D> smallSubList3;
  size_t smallSubListNum[4];
  // === //
  std::vector<Rule5D> bigSub;
  size_t bigSubNum;
  // === //
  std::vector<std::vector<Rule5D>> exactGroup;
  size_t exactGroupNum;
  std::vector<std::vector<Rule5D>> exactGroup_ipS;
  size_t exactGroup_ipSNum;
  std::vector<std::vector<Rule5D>> exactGroup_ipD;
  size_t exactGroup_ipDNum;
  std::vector<std::vector<Rule5D>> exactGroup_portD;
  size_t exactGroup_portDNum;
  // === //
  struct ExactNode {
    Rule5D rule;

    ExactNode *left;
    ExactNode *right;
    ExactNode(Rule5D _rule) : rule(_rule), left(nullptr), right(nullptr) {}
  };
  struct ExactHashTable {
    std::vector<ExactNode *> buckets;
    size_t size;
    ExactHashTable(size_t tableSize) : size(tableSize) {
      buckets.resize(size, nullptr);
    }
  };
  ExactHashTable exactHashTable;
};

#endif
