/**
 * @file rulesetAnalysis.hpp
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

#ifndef __LIB_RULESETANALYSIS_HPP__
#define __LIB_RULESETANALYSIS_HPP__

#include "basis.hpp"
#include <vector>
#include <fstream>

class RulesetAnalysis
{

public:
  RulesetAnalysis(const std::vector<Rule5D> &);
  void printRule5VV(size_t);

private:
  // sIp_prefixLength, dIp_prefixLength, port isRange 0-> not range [src, dst, protocol]
  std::vector<unsigned int> rule5VV[33][33][2][2][2];
};

#endif
