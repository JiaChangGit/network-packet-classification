
#include "checkCovered.hpp"
void CoverChecker::checkCoverageAndRecord(const std::vector<Rule5D>& rules,
                                          const std::string& filename) {
  std::ofstream outfile(filename);

  for (size_t i = 1; i < rules.size(); ++i) {
    std::vector<unsigned int> coveringPriorities;
    for (size_t j = 0; j < i; ++j) {
      if (isRuleCovered(rules[i], rules[j])) {
        coveringPriorities.push_back(rules[j].priority);
      }
    }

    if (!coveringPriorities.empty()) {
      outfile << "Rule " << i + 1 << " is covered by rules with priorities: ";
      for (auto priority : coveringPriorities) {
        outfile << priority << " ";
      }
      outfile << std::endl;
    }
  }

  outfile.close();
}

inline bool CoverChecker::isCovered(const std::array<uint32_t, 2>& range1,
                                    const std::array<uint32_t, 2>& range2) {
  return range1[0] >= range2[0] && range1[1] <= range2[1];
}

inline bool CoverChecker::isRuleCovered(const Rule5D& rule,
                                        const Rule5D& other) {
  for (size_t i = 0; i < rule.dim; ++i) {
    if (!isCovered(rule.range[i], other.range[i])) {
      return false;
    }
  }
  return true;
}
