/**
 * @file rulesetAnalysis.cpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.2
 * @date 2024-02-07
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-07 <td>1.1     <td>jiachang     <td>analyze ruleset distribution
 * </table>
 */

#include "rulesetAnalysis.hpp"

RulesetAnalysis::RulesetAnalysis(const std::vector<Rule5D> &rule5V)
{
  // 0 -> not range
  int isSportRange = 0;
  int isDportRange = 0;
  int isprotocolRange = 0;

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
    if (rule.protocol[0] != rule.protocol[1])
    {
      isprotocolRange = 1;
    }
    unsigned int ipSMask = unsigned(rule.ipSMask);
    unsigned int ipDMask = unsigned(rule.ipSMask);
    rule5V_arr[ipSMask][ipSMask][isSportRange][isDportRange][isprotocolRange].push_back(rule.pri);
    isSportRange = 0;
    isDportRange = 0;
    isprotocolRange = 0;
    // std::cout << "pri: " << rule.pri << "\n";
  }
};

void RulesetAnalysis::printRule5VV(size_t rule5V_num)
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
  outputFile << "sIp_prefixLength, dIp_prefixLength, port isRange? 0-> not range [src, dst, protocol]: rule.priority\n";
  for (int i = 0; i < 33; ++i)
  {
    for (int j = 0; j < 33; ++j)
    {
      for (int k = 0; k < 2; ++k)
      {
        for (int l = 0; l < 2; ++l)
        {
          for (int m = 0; m < 2; ++m)
          {
            // Print the index
            outputFile << "rule5V_arr[" << i << "][" << j << "][" << k << "][" << l << "][" << m << "]: ";
            if (!rule5V_arr[i][j][k][l][m].empty())
            {
              // Print the rule.pri
              for (const auto &element : rule5V_arr[i][j][k][l][m])
              {
                outputFile << element << " ";
                ruleNum++;
              }
              outputFile << "\n==========================\n"
                         << "=== number of element: ===\n"
                         << rule5V_arr[i][j][k][l][m].size() << "\n==========================\n";
            }
            else
            {
              outputFile << "NULL\n";
            }
          }
        }
      }
    }
  }
  if (ruleNum != rule5V_num)
    std::cout << "analysis wrong!!\n";
  outputFile.close();
};
