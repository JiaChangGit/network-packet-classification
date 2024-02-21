#ifndef _CLASSIFIERS_TSEARCH_HPP_
#define _CLASSIFIERS_TSEARCH_HPP_

#include <algorithm>
#include <fstream>
#include <sparsehash/dense_hash_map>

#include "../io/inputFile_test.hpp"
#include "../lib/basis.hpp"
#include "linearSearch.hpp"
class TSearch {
 public:
  TSearch()
      : memorySize(0),
        packetCounter(0),
        exactSubNum(0),
        exactSub_ipSNum(0),
        exactSub_ipDNum(0),
        exactSub_portDNum(0),
        smallSubNum(0),
        zeroSubNum(0),
        smallSubListNum{0},
        bigSubNum(0){

        };
  struct HashUint64 {
    size_t operator()(uint64_t key) const { return key; }
  };
  struct HashUint32 {
    size_t operator()(uint32_t key) const { return key; }
  };

  void partition(std::vector<Rule5D> &, const size_t);
  void partitionExactSub(std::vector<Rule5D> &);
  void partitionExactSub_ipS(std::vector<Rule5D> &);
  void partitionExactSub_ipD(std::vector<Rule5D> &);
  void partitionExactSub_portD(std::vector<Rule5D> &);

  void insertHT(std::vector<std::vector<Rule5D>> &);
  void insertHT_ipS(std::vector<std::vector<Rule5D>> &);
  void insertHT_ipD(std::vector<std::vector<Rule5D>> &);
  void insertHT_portD(std::vector<std::vector<Rule5D>> &);
  void printHashTableToFile64(
      const std::vector<google::dense_hash_map<uint64_t, Rule5D, HashUint64>> &,
      const char *);
  void printHashTableToFile32(
      const std::vector<google::dense_hash_map<uint32_t, Rule5D, HashUint32>> &,
      const char *);
  void search(std::vector<Rule5D> &, const std::vector<Packet5D> &);

 private:
  unsigned long long memorySize;
  unsigned long long packetCounter;
  // const size_t Threshold1;
  // const size_t BucketNum;
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
  std::vector<google::dense_hash_map<uint64_t, Rule5D, HashUint64>> hashTableV;
  size_t hashTableV_Num;
  std::vector<google::dense_hash_map<uint32_t, Rule5D, HashUint32>>
      hashTableV_ipS;
  size_t hashTableV_ipSNum;
  std::vector<google::dense_hash_map<uint32_t, Rule5D, HashUint32>>
      hashTableV_ipD;
  size_t hashTableV_ipDNum;
  std::vector<google::dense_hash_map<uint32_t, Rule5D, HashUint32>>
      hashTableV_portD;
  size_t hashTableV_portDNum;
  // === //
};

#endif
