#include "tSearch.hpp"
void TSearch::partition(std::vector<Rule5D>& rule5V, const size_t Rule5V_num) {
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

  if (Rule5V_num !=
      (exactSubNum + exactSub_ipSNum + exactSub_ipDNum + exactSub_portDNum +
       zeroSubNum + smallSubNum + bigSubNum)) {
    std::cerr << "Wrong partition!!\n";
    exit(1);
  }

  // ==== test txt ==== //
  InputFile5D_test inputFile5D_test;
  const char* ExactSub_path = "./INFO/ExactSub.txt";
  const char* ExactSub_ipS_path = "./INFO/ExactSub_ipS.txt";
  const char* ExactSub_ipD_path = "./INFO/ExactSub_ipD.txt";
  const char* ExactSub_portD_path = "./INFO/ExactSub_portD.txt";
  const char* ZeroSub_path = "./INFO/ZeroSub.txt";
  const char* SmallSubList0_path = "./INFO/SmallSubList0.txt";
  const char* SmallSubList1_path = "./INFO/SmallSubList1.txt";
  const char* SmallSubList2_path = "./INFO/SmallSubList2.txt";
  const char* SmallSubList3_path = "./INFO/SmallSubList3.txt";
  const char* BigSub_path = "./INFO/BigSub.txt";

  inputFile5D_test.loadRule5D_test(exactSub, ExactSub_path);
  inputFile5D_test.loadRule5D_test(exactSub_ipS, ExactSub_ipS_path);
  inputFile5D_test.loadRule5D_test(exactSub_ipD, ExactSub_ipD_path);
  inputFile5D_test.loadRule5D_test(exactSub_portD, ExactSub_portD_path);
  inputFile5D_test.loadRule5D_test(zeroSub, ZeroSub_path);
  inputFile5D_test.loadRule5D_test(smallSubList0, SmallSubList0_path);
  inputFile5D_test.loadRule5D_test(smallSubList1, SmallSubList1_path);
  inputFile5D_test.loadRule5D_test(smallSubList2, SmallSubList2_path);
  inputFile5D_test.loadRule5D_test(smallSubList3, SmallSubList3_path);
  inputFile5D_test.loadRule5D_test(bigSub, BigSub_path);
  // ==== test txt ==== //

  // ==== partitionSub to group ==== //
  partitionExactSub(exactSub);
  std::vector<Rule5D>().swap(exactSub);
  partitionExactSub_ipS(exactSub_ipS);
  std::vector<Rule5D>().swap(exactSub_ipS);
  partitionExactSub_ipD(exactSub_ipD);
  std::vector<Rule5D>().swap(exactSub_ipD);
  partitionExactSub_portD(exactSub_portD);
  std::vector<Rule5D>().swap(exactSub_portD);
  // ==== partitionSub to group ==== //

  // insertU16HashTable(exactSub_portD);
  // std::vector<Rule5D>().swap(exactSub_portD);
};
void TSearch::partitionExactSub(std::vector<Rule5D>& rule5V) {
  bool isUniqField[2] = {true};

  std::vector<Rule5D> uniq_ipSD;
  uniq_ipSD.emplace_back(rule5V[0]);
  // std::cout << "uniq_ipSD size: " << uniq_ipSD.size()
  //           << ", uniq_ipSD[0]: " << uniq_ipSD[0].ipS32 << std::endl;
  exactGroup.emplace_back(uniq_ipSD);
  if (!rule5V.empty()) {
    rule5V.erase(rule5V.begin());
  }

  // std::cout << "size: " << exactGroup.size()
  //           << ", [0]size: " << exactGroup[0].size()
  //           << ", [1]size: " << exactGroup[1].size()
  //           << ", exactGroup[0][0]: " << exactGroup[0][0].ipS32 << std::endl;

  for (const auto& rule : rule5V) {
    // std::cout << "pri: " << rule.pri << "\n";
    for (size_t gNum = 0; gNum < exactGroup.size(); ++gNum) {
      for (const auto& analysisV : exactGroup[gNum]) {
        if ((unsigned(rule.ipSMask) == 0) &&
            (unsigned(analysisV.ipSMask) == 0)) {
          isUniqField[0] = false;

        } else if (((unsigned(rule.ipSMask)) ==
                    (unsigned(analysisV.ipSMask))) &&
                   ((rule.ipS32 >> (32 - unsigned(rule.ipSMask))) ==
                    (analysisV.ipS32 >> (32 - unsigned(analysisV.ipSMask))))) {
          isUniqField[0] = false;
        }
        if ((unsigned(rule.ipDMask) == 0) &&
            (unsigned(analysisV.ipDMask) == 0)) {
          isUniqField[1] = false;

        } else if (((unsigned(rule.ipDMask)) ==
                    (unsigned(analysisV.ipDMask))) &&
                   ((rule.ipD32 >> (32 - unsigned(rule.ipDMask))) ==
                    (analysisV.ipD32 >> (32 - unsigned(analysisV.ipDMask))))) {
          isUniqField[1] = false;
        }
      }

      if (isUniqField[0] || isUniqField[1]) {
        // uniq_ipSD.emplace_back(rule);
        exactGroup[gNum].emplace_back(rule);
        gNum = 0;
        isUniqField[0] = true;
        isUniqField[1] = true;
        break;
      } else if (gNum >= exactGroup.size() - 1) {
        std::vector<Rule5D> tmp;
        tmp.emplace_back(rule);
        exactGroup.emplace_back(tmp);
        gNum = 0;
        isUniqField[0] = true;
        isUniqField[1] = true;
        break;
      }
      isUniqField[0] = true;
      isUniqField[1] = true;
    }
  }
  // // === //
  exactGroupNum = exactGroup.size();
  std::cout << "size: " << exactGroup.size()
            << ", [0]size: " << exactGroup[0].size()
            << ", [1]size: " << exactGroup[1].size() << std::endl;

  size_t counter = 0;
  for (const auto& innerVec : exactGroup) {
    for (const auto& val : innerVec) {
      // std::cout << val.ipS32 << " ";
      ++counter;
    }
    // std::cout << std::endl;
  }
  // std::cout << "counter: " << counter << std::endl;
  //  // === //
  if (counter != exactSubNum) {
    std::cerr << "counter != exactSubNum\n";
    exit(1);
  }
  if (exactGroupNum <= 0) {
    std::cerr << "exactGroupNum: " << exactGroupNum << " <= 0\n";
    exit(1);
  }
  std::cout << "exactGroupNum: " << exactGroupNum << "\n";
};

void TSearch::partitionExactSub_ipS(std::vector<Rule5D>& rule5V) {
  bool isUniqField = true;
  std::vector<Rule5D> uniq_ipS;
  uniq_ipS.emplace_back(rule5V[0]);
  exactGroup_ipS.emplace_back(uniq_ipS);
  if (!rule5V.empty()) {
    rule5V.erase(rule5V.begin());
  }

  for (const auto& rule : rule5V) {
    // std::cout << "pri: " << rule.pri << "\n";
    for (size_t gNum = 0; gNum < exactGroup_ipS.size(); ++gNum) {
      for (const auto& analysisV : exactGroup_ipS[gNum]) {
        if ((unsigned(rule.ipSMask) == 0) &&
            (unsigned(analysisV.ipSMask) == 0)) {
          isUniqField = false;

        } else if (((unsigned(rule.ipSMask)) ==
                    (unsigned(analysisV.ipSMask))) &&
                   ((rule.ipS32 >> (32 - unsigned(rule.ipSMask))) ==
                    (analysisV.ipS32 >> (32 - unsigned(analysisV.ipSMask))))) {
          isUniqField = false;
        }
      }
      if (isUniqField) {
        exactGroup_ipS[gNum].emplace_back(rule);
        gNum = 0;
        isUniqField = true;
        break;
      } else if (gNum >= exactGroup_ipS.size() - 1) {
        std::vector<Rule5D> tmp;
        tmp.emplace_back(rule);
        exactGroup_ipS.emplace_back(tmp);
        gNum = 0;
        isUniqField = true;
        break;
      }
      isUniqField = true;
    }
  }
  // // === //
  exactGroup_ipSNum = exactGroup_ipS.size();
  std::cout << "size: " << exactGroup_ipS.size()
            << ", [0]size: " << exactGroup_ipS[0].size()
            << ", [1]size: " << exactGroup_ipS[1].size() << std::endl;

  size_t counter = 0;
  for (const auto& innerVec : exactGroup_ipS) {
    for (const auto& val : innerVec) {
      // std::cout << val.ipS32 << " ";
      ++counter;
    }
    // std::cout << std::endl;
  }
  // std::cout << "counter: " << counter << std::endl;
  //  // === //
  if (counter != exactSub_ipSNum) {
    std::cerr << "counter != exactSub_ipSNum\n";
    exit(1);
  }
  if (exactGroup_ipSNum <= 0) {
    std::cerr << "exactGroup_ipSNum: " << exactGroup_ipSNum << " <= 0\n";
    exit(1);
  }
  std::cout << "exactGroup_ipSNum: " << exactGroup_ipSNum << "\n";
};

void TSearch::partitionExactSub_ipD(std::vector<Rule5D>& rule5V) {
  bool isUniqField = true;
  std::vector<Rule5D> uniq_ipD;
  uniq_ipD.emplace_back(rule5V[0]);
  exactGroup_ipD.emplace_back(uniq_ipD);
  if (!rule5V.empty()) {
    rule5V.erase(rule5V.begin());
  }

  for (const auto& rule : rule5V) {
    // std::cout << "pri: " << rule.pri << "\n";
    for (size_t gNum = 0; gNum < exactGroup_ipD.size(); ++gNum) {
      for (const auto& analysisV : exactGroup_ipD[gNum]) {
        if ((unsigned(rule.ipDMask) == 0) &&
            (unsigned(analysisV.ipDMask) == 0)) {
          isUniqField = false;

        } else if (((unsigned(rule.ipDMask)) ==
                    (unsigned(analysisV.ipDMask))) &&
                   ((rule.ipD32 >> (32 - unsigned(rule.ipDMask))) ==
                    (analysisV.ipD32 >> (32 - unsigned(analysisV.ipDMask))))) {
          isUniqField = false;
        }
      }
      if (isUniqField) {
        exactGroup_ipD[gNum].emplace_back(rule);
        gNum = 0;
        isUniqField = true;
        break;
      } else if (gNum >= exactGroup_ipD.size() - 1) {
        std::vector<Rule5D> tmp;
        tmp.emplace_back(rule);
        exactGroup_ipD.emplace_back(tmp);
        gNum = 0;
        isUniqField = true;
        break;
      }
      isUniqField = true;
    }
  }
  // // === //
  exactGroup_ipDNum = exactGroup_ipD.size();
  std::cout << "size: " << exactGroup_ipD.size()
            << ", [0]size: " << exactGroup_ipD[0].size()
            << ", [1]size: " << exactGroup_ipD[1].size() << std::endl;

  size_t counter = 0;
  for (const auto& innerVec : exactGroup_ipD) {
    for (const auto& val : innerVec) {
      // std::cout << val.ipS32 << " ";
      ++counter;
    }
    // std::cout << std::endl;
  }
  // std::cout << "counter: " << counter << std::endl;
  //  // === //
  if (counter != exactSub_ipDNum) {
    std::cerr << "counter != exactSub_ipDNum\n";
    exit(1);
  }
  if (exactGroup_ipDNum <= 0) {
    std::cerr << "exactGroup_ipDNum: " << exactGroup_ipDNum << " <= 0\n";
    exit(1);
  }
  std::cout << "exactGroup_ipDNum: " << exactGroup_ipDNum << "\n";
};

void TSearch::partitionExactSub_portD(std::vector<Rule5D>& rule5V) {
  bool isUniqField = true;
  std::vector<Rule5D> uniq_portD;
  uniq_portD.emplace_back(rule5V[0]);
  exactGroup_portD.emplace_back(uniq_portD);
  if (!rule5V.empty()) {
    rule5V.erase(rule5V.begin());
  }

  for (const auto& rule : rule5V) {
    // std::cout << "pri: " << rule.pri << "\n";
    for (size_t gNum = 0; gNum < exactGroup_portD.size(); ++gNum) {
      for (const auto& analysisV : uniq_portD) {
        if ((rule.portD[0] == analysisV.portD[0]) &&
            (rule.portD[1] == analysisV.portD[1])) {
          isUniqField = false;
        }
      }
      if (isUniqField) {
        exactGroup_portD[gNum].emplace_back(rule);
        gNum = 0;
        isUniqField = true;
        break;
      } else if (gNum >= exactGroup_portD.size() - 1) {
        std::vector<Rule5D> tmp;
        tmp.emplace_back(rule);
        exactGroup_portD.emplace_back(tmp);
        gNum = 0;
        isUniqField = true;
        break;
      }
      isUniqField = true;
    }
  }
  // // === //
  exactGroup_portDNum = exactGroup_portD.size();
  std::cout << "size: " << exactGroup_portD.size()
            << ", [0]size: " << exactGroup_portD[0].size()
            << ", [1]size: " << exactGroup_portD[1].size() << std::endl;

  size_t counter = 0;
  for (const auto& innerVec : exactGroup_portD) {
    for (const auto& val : innerVec) {
      // std::cout << val.ipS32 << " ";
      ++counter;
    }
    // std::cout << std::endl;
  }
  // std::cout << "counter: " << counter << std::endl;
  //  // === //
  if (counter != exactSub_portDNum) {
    std::cerr << "counter != exactSub_portDNum\n";
    exit(1);
  }
  if (exactGroup_portDNum <= 0) {
    std::cerr << "exactGroup_portDNum: " << exactGroup_portDNum << " <= 0\n";
    exit(1);
  }
  std::cout << "exactGroup_portDNum: " << exactGroup_portDNum << "\n";
};

inline void TSearch::insertU16HashTable(std::vector<Rule5D>& rule5V){};
