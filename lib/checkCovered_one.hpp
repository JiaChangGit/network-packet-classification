#ifndef _CHCKCOVERED_ONE_HPP__
#define _CHCKCOVERED_ONE_HPP__

#include <algorithm>
#include <fstream>

#include "./basis.hpp"

class CoverChecker_one {
 public:
  void checkCoverageAndRecord(const std::vector<Rule5D>& rules,
                              const std::string& fileName);

 private:
  inline bool isCovered(const std::array<uint32_t, 2>& range1,
                        const std::array<uint32_t, 2>& range2);

  inline bool isRuleCovered(const Rule5D& rule, const Rule5D& other);
};

#endif
