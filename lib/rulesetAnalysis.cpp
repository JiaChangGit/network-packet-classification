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
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>analyze ruleset distribution
 * </table>
 */

#include "rulesetAnalysis.hpp"

RulesetAnalysis::RulesetAnalysis(const std::vector<Rule5D> &rule5V)
{
  // 0 -> not range
  int isSportRange = 0;
  int isDportRange = 0;

  for (const auto &rule : rule5V)
  {
    if (rule.portS[0] != rule.portS[1])
    {
      isSportRange = 1;
    }
    if (rule.portD[0] != rule.portD[1])
    {
      isDportRange = 1;
    }
    unsigned int ipSMask = unsigned(rule.ipSMask);
    unsigned int ipDMask = unsigned(rule.ipSMask);
    rule5V_arr[ipSMask][ipSMask][isSportRange][isDportRange].push_back(rule.pri);
    isSportRange = 0;
    isDportRange = 0;
    // std::cout << "pri: " << rule.pri << "\n";
  }
};

void RulesetAnalysis::printRule5V_arr(size_t rule5V_num)
{
  const char *RulesetAnalysisPrint_path = "./INFO/rulesetAnalysis.txt";
  size_t ruleNum = 0;
  std::ofstream outputFile(RulesetAnalysisPrint_path);
  if (!outputFile.is_open())
  {
    std::cerr << "Unable to open file! rulesetAnalysis.txt\n";
    return;
  }
  outputFile << "rule numbers: " << rule5V_num << "\n";
  outputFile << "sIp_prefixLength, dIp_prefixLength, port isRange? 0-> not range [src, dst]: rule.priority\n\n";
  for (int i = 0; i < 33; ++i)
  {
    for (int j = 0; j < 33; ++j)
    {
      for (int k = 0; k < 2; ++k)
      {
        for (int l = 0; l < 2; ++l)
        {
          if (!rule5V_arr[i][j][k][l].empty())
          {
            // Print the index
            outputFile << "rule5V_arr[" << i << "][" << j << "][" << k << "][" << l << "]: ";
            // Print the rule.pri
            float rule5V_arrSize = rule5V_arr[i][j][k][l].size();
            for (const auto &element : rule5V_arr[i][j][k][l])
            {
              outputFile << element << " ";
              ruleNum++;
            }
            outputFile << "\n==========================\n"
                       << "=== number of elements: ===\n"
                       << rule5V_arrSize << "\n=== Ratio: ===\n"
                       << rule5V_arrSize / rule5V_num << "\n==========================\n\n";
          }
          else
          {
            // Print the index
            // outputFile << "rule5V_arr[" << i << "][" << j << "][" << k << "][" << l <<  "]: ";
            // outputFile << "NULL\n";
          }
        }
      }
    }
  }
  if (ruleNum != rule5V_num)
    std::cout << "analysis wrong!!\n";
  outputFile.close();
};
