/**
 * @file rulesetAnalysis.cpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.4
 * @date 2024-02-11
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>analyze ruleset
 * distribution
 * </table>
 */

#include "rulesetAnalysis.hpp"

RulesetAnalysis::RulesetAnalysis(const std::vector<Rule5D> &rule5V) {
  // 0 -> not range
  int isSportRange = 0;
  int isDportRange = 0;
  bool isUniqField[5] = {true};

  analysisRule5D analy_tmp;
  analy_tmp.rule5D = rule5V[0];
  analy_tmp.matchField = 0;
  uniqRule5V.emplace_back(analy_tmp);
  analy_tmp.matchField = 1;
  uniqRule5V.emplace_back(analy_tmp);
  analy_tmp.matchField = 2;
  uniqRule5V.emplace_back(analy_tmp);
  analy_tmp.matchField = 3;
  uniqRule5V.emplace_back(analy_tmp);
  analy_tmp.matchField = 4;
  uniqRule5V.emplace_back(analy_tmp);
  for (const auto &rule : rule5V) {
    if (rule.portS[0] != rule.portS[1]) {
      isSportRange = 1;
    }
    if (rule.portD[0] != rule.portD[1]) {
      isDportRange = 1;
    }
    unsigned int ipSMask = unsigned(rule.ipSMask);
    unsigned int ipDMask = unsigned(rule.ipDMask);
    rule5V_arr[ipSMask][ipDMask][isSportRange][isDportRange].emplace_back(
        rule.pri);
    isSportRange = 0;
    isDportRange = 0;
    // std::cout << "pri: " << rule.pri << "\n";

    for (const auto &analysisV : uniqRule5V) {
      if ((unsigned(rule.ipSMask) == 0) &&
          (unsigned(analysisV.rule5D.ipSMask) == 0)) {
        isUniqField[0] = false;

      } else if (((unsigned(rule.ipSMask)) ==
                  (unsigned(analysisV.rule5D.ipSMask))) &&
                 ((rule.ipS32 >> (32 - unsigned(rule.ipSMask))) ==
                  (analysisV.rule5D.ipS32 >>
                   (32 - unsigned(analysisV.rule5D.ipSMask))))) {
        isUniqField[0] = false;
      }
      if ((unsigned(rule.ipDMask) == 0) &&
          (unsigned(analysisV.rule5D.ipDMask) == 0)) {
        isUniqField[1] = false;

      } else if (((unsigned(rule.ipDMask)) ==
                  (unsigned(analysisV.rule5D.ipDMask))) &&
                 ((rule.ipD32 >> (32 - unsigned(rule.ipDMask))) ==
                  (analysisV.rule5D.ipD32 >>
                   (32 - unsigned(analysisV.rule5D.ipDMask))))) {
        isUniqField[1] = false;
      }
      if ((rule.portS[0] == analysisV.rule5D.portS[0]) &&
          (rule.portS[1] == analysisV.rule5D.portS[1])) {
        isUniqField[2] = false;
      }
      if ((rule.portD[0] == analysisV.rule5D.portD[0]) &&
          (rule.portD[1] == analysisV.rule5D.portD[1])) {
        isUniqField[3] = false;
      }
      if ((rule.protocol[0] == analysisV.rule5D.protocol[0]) &&
          (rule.protocol[1] == analysisV.rule5D.protocol[1])) {
        isUniqField[4] = false;
      }
    }
    for (int i = 0; i < 5; ++i) {
      if (isUniqField[i]) {
        analy_tmp.matchField = i;
        analy_tmp.rule5D = rule;
        uniqRule5V.emplace_back(analy_tmp);
      }
      isUniqField[i] = true;
    }
  }
  size_t uniqRule5V_num = uniqRule5V.size();
  if (uniqRule5V_num <= 0) {
    std::cerr << "uniqRule5V_num: " << uniqRule5V_num << " <= 0\n";
    exit(1);
  }
  std::cout << "uniqRule5V: " << uniqRule5V_num << "\n";
};

void RulesetAnalysis::printRule5V_arr(size_t rule5V_num) {
  const char *RulesetAnalysisPrint_path = "./INFO/rulesetAnalysis.txt";
  size_t ruleNum = 0;
  std::ofstream outputFile(RulesetAnalysisPrint_path);
  if (!outputFile.is_open()) {
    std::cerr << "Unable to open file! rulesetAnalysis.txt\n";
    exit(1);
  }
  outputFile << "rule numbers: " << rule5V_num << "\n";
  outputFile << "sIp_prefixLength, dIp_prefixLength, port isRange? 0-> not "
                "range [src, dst]: rule.priority\n\n";
  for (int i = 0; i < 33; ++i) {
    for (int j = 0; j < 33; ++j) {
      for (int k = 0; k < 2; ++k) {
        for (int l = 0; l < 2; ++l) {
          if (!rule5V_arr[i][j][k][l].empty()) {
            // Print the index
            outputFile << "rule5V_arr[" << i << "][" << j << "][" << k << "]["
                       << l << "]: ";
            // Print the rule.pri
            float rule5V_arrSize = rule5V_arr[i][j][k][l].size();
            for (const auto &element : rule5V_arr[i][j][k][l]) {
              outputFile << element << " ";
              ruleNum++;
            }
            outputFile << "\n==========================\n"
                       << "=== number of elements: ===\n"
                       << rule5V_arrSize << "\n=== Ratio: ===\n"
                       << rule5V_arrSize / rule5V_num
                       << "\n==========================\n\n";
          } else {
            // Print the NULL
            // outputFile << "rule5V_arr[" << i << "][" << j << "][" << k <<
            // "][" << l <<  "]: "; outputFile << "NULL\n";
          }
        }
      }
    }
  }
  if (ruleNum != rule5V_num) std::cout << "uniqRule5V wrong!!\n";
  outputFile.close();
};

void RulesetAnalysis ::printUniqRule5V() {
  const char *UniqRule5VPrint_path = "./INFO/uniqRule5V.txt";
  const char *ExactRule5VPrint_path = "./INFO/exactRule5V.txt";
  std::ofstream outputFile(UniqRule5VPrint_path);
  if (!outputFile.is_open()) {
    std::cerr << "Unable to open file! uniqRule5V.txt\n";
    exit(1);
  }
  std::vector<analysisRule5D> analysisRule5D_ipS;
  std::vector<analysisRule5D> analysisRule5D_ipD;
  std::vector<analysisRule5D> analysisRule5D_portS;
  std::vector<analysisRule5D> analysisRule5D_portD;
  std::vector<analysisRule5D> analysisRule5D_protocol;
  for (const auto &analy : uniqRule5V) {
    if (analy.matchField == 0) {
      analysisRule5D_ipS.emplace_back(analy);
    } else if (analy.matchField == 1) {
      analysisRule5D_ipD.emplace_back(analy);
    } else if (analy.matchField == 2) {
      analysisRule5D_portS.emplace_back(analy);
    } else if (analy.matchField == 3) {
      analysisRule5D_portD.emplace_back(analy);
    } else if (analy.matchField == 4) {
      analysisRule5D_protocol.emplace_back(analy);
    } else {
      std::cerr << "analy.matchField: " << analy.matchField << " != 0~4\n";
      exit(1);
    }
  }
  outputFile << "========\n";
  outputFile << "uniq ipS: " << analysisRule5D_ipS.size() << "\n";
  outputFile << "========\n";
  for (const auto &uniq : analysisRule5D_ipS) {
    outputFile << "pri: " << uniq.rule5D.pri << "\n";
    outputFile << "ipS32: " << unsigned(uniq.rule5D.ipS[3]) << "."
               << unsigned(uniq.rule5D.ipS[2]) << "."
               << unsigned(uniq.rule5D.ipS[1]) << "."
               << unsigned(uniq.rule5D.ipS[0]) << "/"
               << unsigned(uniq.rule5D.ipSMask) << "\n";
  }
  outputFile << "\n========\n";
  outputFile << "uniq ipD: " << analysisRule5D_ipD.size() << "\n";
  outputFile << "========\n";
  for (const auto &uniq : analysisRule5D_ipD) {
    outputFile << "pri: " << uniq.rule5D.pri << "\n";
    outputFile << "ipD32: " << unsigned(uniq.rule5D.ipD[3]) << "."
               << unsigned(uniq.rule5D.ipD[2]) << "."
               << unsigned(uniq.rule5D.ipD[1]) << "."
               << unsigned(uniq.rule5D.ipD[0]) << "/"
               << unsigned(uniq.rule5D.ipDMask) << "\n";
  }
  outputFile << "\n========\n";
  outputFile << "uniq portS: " << analysisRule5D_portS.size() << "\n";
  outputFile << "========\n";
  for (const auto &uniq : analysisRule5D_portS) {
    outputFile << "pri: " << uniq.rule5D.pri << "\n";
    outputFile << "portS: " << unsigned(uniq.rule5D.portS[0]) << ":"
               << unsigned(uniq.rule5D.portS[1]) << "\n";
  }
  outputFile << "\n========\n";
  outputFile << "uniq portD: " << analysisRule5D_portD.size() << "\n";
  outputFile << "========\n";
  for (const auto &uniq : analysisRule5D_portD) {
    outputFile << "pri: " << uniq.rule5D.pri << "\n";
    outputFile << "portD: " << unsigned(uniq.rule5D.portD[0]) << ":"
               << unsigned(uniq.rule5D.portD[1]) << "\n";
  }
  outputFile << "\n========\n";
  outputFile << "uniq protocol: " << analysisRule5D_protocol.size() << "\n";
  outputFile << "========\n";
  for (const auto &uniq : analysisRule5D_protocol) {
    outputFile << "pri: " << uniq.rule5D.pri << "\n";
    outputFile << "protocol: " << unsigned(uniq.rule5D.protocol[0]) << ":"
               << unsigned(uniq.rule5D.protocol[1]) << "\n";
  }
  outputFile.close();
  // ==== exact ==== //
  std::ofstream outputExact(ExactRule5VPrint_path);
  if (!outputExact.is_open()) {
    std::cerr << "Unable to open file! exactRule5V.txt\n";
    exit(1);
  }
  size_t exactCounter = 0;

  for (const auto &exact : analysisRule5D_ipS) {
    if (exact.rule5D.ipSMask == 32) {
      ++exactCounter;
      outputExact << "pri: " << exact.rule5D.pri << "\n";
      outputExact << "ipS32: " << unsigned(exact.rule5D.ipS[3]) << "."
                  << unsigned(exact.rule5D.ipS[2]) << "."
                  << unsigned(exact.rule5D.ipS[1]) << "."
                  << unsigned(exact.rule5D.ipS[0]) << "/"
                  << unsigned(exact.rule5D.ipSMask) << "\n";
    }
  }
  outputExact << "========\n";
  outputExact << "exact ipS: " << exactCounter << "\n";
  outputExact << "========\n\n";
  exactCounter = 0;

  for (const auto &exact : analysisRule5D_ipD) {
    if (exact.rule5D.ipDMask == 32) {
      ++exactCounter;
      outputExact << "pri: " << exact.rule5D.pri << "\n";
      outputExact << "ipD32: " << unsigned(exact.rule5D.ipD[3]) << "."
                  << unsigned(exact.rule5D.ipD[2]) << "."
                  << unsigned(exact.rule5D.ipD[1]) << "."
                  << unsigned(exact.rule5D.ipD[0]) << "/"
                  << unsigned(exact.rule5D.ipDMask) << "\n";
    }
  }
  outputExact << "========\n";
  outputExact << "exact ipD: " << exactCounter << "\n";
  outputExact << "========\n\n";
  exactCounter = 0;

  for (const auto &exact : analysisRule5D_portS) {
    if (exact.rule5D.portS[0] == exact.rule5D.portS[1]) {
      ++exactCounter;
      outputExact << "pri: " << exact.rule5D.pri << "\n";
      outputExact << "portS: " << unsigned(exact.rule5D.portS[0]) << ":"
                  << unsigned(exact.rule5D.portS[1]) << "\n";
    }
  }
  outputExact << "========\n";
  outputExact << "exact portS: " << exactCounter << "\n";
  outputExact << "========\n\n";
  exactCounter = 0;

  for (const auto &exact : analysisRule5D_portD) {
    if (exact.rule5D.portD[0] == exact.rule5D.portD[1]) {
      ++exactCounter;
      outputExact << "pri: " << exact.rule5D.pri << "\n";
      outputExact << "portD: " << unsigned(exact.rule5D.portD[0]) << ":"
                  << unsigned(exact.rule5D.portD[1]) << "\n";
    }
  }
  outputExact << "========\n";
  outputExact << "exact portD: " << exactCounter << "\n";
  outputExact << "========\n\n";
  exactCounter = 0;

  for (const auto &exact : analysisRule5D_protocol) {
    if (exact.rule5D.protocol[0] == exact.rule5D.protocol[1]) {
      ++exactCounter;
      outputExact << "pri: " << exact.rule5D.pri << "\n";
      outputExact << "protocol: " << unsigned(exact.rule5D.protocol[0]) << ":"
                  << unsigned(exact.rule5D.protocol[1]) << "\n";
    }
  }
  outputExact << "========\n";
  outputExact << "exact protocol: " << exactCounter << "\n";
  outputExact << "========\n";
  outputExact.close();
  // ==== exact ==== //
};
