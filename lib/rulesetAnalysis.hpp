/**
 * @file rulesetAnalysis.hpp
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

#ifndef __LIB_RULESETANALYSIS_HPP__
#define __LIB_RULESETANALYSIS_HPP__

#include <fstream>
#include <vector>

#include "basis.hpp"

class RulesetAnalysis {
 public:
  RulesetAnalysis(const std::vector<Rule5D> &);
  void printRule5V_arr(size_t);

 private:
  // sIp_prefixLength, dIp_prefixLength, port isRange 0-> not range [src, dst]
  std::vector<unsigned int> rule5V_arr[33][33][2][2];
};

#endif
