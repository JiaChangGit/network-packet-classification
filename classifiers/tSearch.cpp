#include "tSearch.hpp"
void TSearch::partition(std::vector<Rule5D>& rule5V, const size_t rule5V_num) {
  for (const auto& rule : rule5V) {
    if ((rule.ipSMask == 32) && (rule.ipDMask == 32)) {
      exactSub.emplace_back(rule);
    } else if ((rule.ipSMask == 32) && (rule.ipDMask != 32)) {
      exactSub_ipS.emplace_back(rule);
    } else if ((rule.ipSMask != 32) && (rule.ipDMask == 32)) {
      exactSub_ipD.emplace_back(rule);
    } else if (rule.portD[0] == rule.portD[1]) {
      exactSub_portD.emplace_back(rule);
    } else if ((rule.ipSMask == 0) || (rule.ipDMask == 0)) {
      zeroSub.emplace_back(rule);
    } else if (16 > unsigned((rule.ipSMask + rule.ipDMask))) {
      tmpSmallSub.emplace_back(rule);
    } else {
      bigSub.emplace_back(rule);
    }
  }
  exactSubNum = exactSub.size();
  std::cout << "exactSubNum: " << exactSubNum << "\n";
  exactSub_ipSNum = exactSub_ipS.size();
  std::cout << "exactSub_ipSNum: " << exactSub_ipSNum << "\n";
  exactSub_ipDNum = exactSub_ipD.size();
  std::cout << "exactSub_ipDNum: " << exactSub_ipDNum << "\n";
  exactSub_portDNum = exactSub_portD.size();
  std::cout << "exactSub_portDNum: " << exactSub_portDNum << "\n";
  bigSubNum = bigSub.size();
  std::cout << "bigSubNum: " << bigSubNum << "\n";
  zeroSubNum = zeroSub.size();
  std::cout << "zeroSubNum: " << zeroSubNum << "\n";
  smallSubNum = tmpSmallSub.size();
  std::cout << "smallSubNum: " << smallSubNum << "\n";

  for (const auto& smallRule : tmpSmallSub) {
    if ((smallRule.ipSMask > 7) && (smallRule.ipDMask > 7)) {
      smallSubList0.emplace_back(smallRule);
    } else if ((smallRule.ipSMask > 7) && (smallRule.ipDMask <= 7)) {
      smallSubList1.emplace_back(smallRule);
    } else if ((smallRule.ipSMask <= 7) && (smallRule.ipDMask > 7)) {
      smallSubList2.emplace_back(smallRule);
    } else if ((smallRule.ipSMask <= 7) && (smallRule.ipDMask <= 7)) {
      smallSubList3.emplace_back(smallRule);
    }
  }
  std::vector<Rule5D>().swap(tmpSmallSub);
  smallSubNum = 0;
  smallSubListNum[0] = smallSubList0.size();
  smallSubListNum[1] = smallSubList1.size();
  smallSubListNum[2] = smallSubList2.size();
  smallSubListNum[3] = smallSubList3.size();
  for (size_t i = 0; i < 4; ++i) {
    std::cout << "smallSubListNum[ " << i << " ]: " << smallSubListNum[i]
              << "\n";
    smallSubNum = smallSubNum + smallSubListNum[i];
  }

  if (rule5V_num !=
      (exactSubNum + exactSub_ipSNum + exactSub_ipDNum + exactSub_portDNum +
       zeroSubNum + smallSubNum + bigSubNum)) {
    std::cerr << "Wrong partition!!\n";
    exit(1);
  }
  insertU16HashTable(exactSub_portD);
  std::vector<Rule5D>().swap(exactSub_portD);
};

inline void TSearch::insertU16HashTable(std::vector<Rule5D>& rule5V){};
