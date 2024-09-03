#ifndef _EQUIVALENTPRI_HPP__
#define _EQUIVALENTPRI_HPP__

#include <algorithm>
#include <cstring>  // For memset
#include <fstream>

#include "./basis.hpp"
class EquivalentPri {
 public:
  void pri_MSversion(const std::vector<Rule5D>&, size_t);
  std::vector<std::vector<Rule5D>> getG(void) { return Gv; };

  void print(const char* fileName);

 private:
  std::vector<std::vector<Rule5D>> Gv;
  bool inline isOverlap(Rule5D ri, Rule5D rj) {
    for (size_t i = 0; i < MAXDIMENSIONS; i++) {
      if ((std::max(ri.range[i][0], rj.range[i][0])) >
          (std::min(ri.range[i][1], rj.range[i][1]))) {
        return false;
      }
    }
    return true;
  };
};
#endif
