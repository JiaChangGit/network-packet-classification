#include "equivalentPri.hpp"
void EquivalentPri::pri_MSversion(const std::vector<Rule5D>& rule5V,
                                  size_t rule5VSize) {
  std::cout << "START\n\n";
  bool flag = false;

  auto it = rule5V.begin();
  Gv.emplace_back(std::vector<Rule5D>(1, *it));
  ++it;
  while (it != rule5V.end()) {
    for (int gRight = (Gv.size() - 1); gRight >= 0; --gRight) {
      for (const auto& gIt : Gv.at(gRight)) {
        if (isOverlap(*it, gIt)) {
          if (gRight == (Gv.size() - 1)) {
            Gv.emplace_back(std::vector<Rule5D>(1, *it));
            flag = true;
            break;
          } else {
            Gv.at(gRight + 1).emplace_back(*it);
            flag = true;
            break;
          }

        }
        // std::cout << "continue\n";
      }
      if (flag) {
        flag = false;
        break;
      }
      if (0 == gRight) {
        Gv[0].emplace_back(*it);
      }
    }
    ++it;
  }
  size_t checkCount = 0;
  for (int gSize = (Gv.size() - 1); gSize >= 0; --gSize) {
    checkCount = checkCount + Gv.at(gSize).size();
  }
  if (checkCount != rule5VSize) {
    std::cerr << "equivalentPri error: " << checkCount << "\n";
    exit(1);
  } else {
    std::cout << "checkCount: " << checkCount << "\n";
  }
}

void EquivalentPri::print(const char* FileName) {
  std::ofstream outFile(FileName);
  if (!outFile.is_open()) {
    std::cerr << "Failed to open " << FileName << " for writing" << "\n";
    return;
  }
  size_t gPri = 1, counter = 0;
  for (const auto& rule5V : Gv) {
    for (const auto& rule : rule5V) {
      outFile << "gPri: " << gPri << "\n"
              << "priority: " << rule.priority << "\n";
      outFile << "prefix_length: ";
      for (const auto& length : rule.prefix_length) {
        outFile << length << " ";
      }
      outFile << "\n";
      outFile << "range: ";
      for (const auto& r : rule.range) {
        outFile << "[" << r[0] << ", " << r[1] << "] ";
      }
      outFile << "\n\n";
      ++counter;
    }
    std::cout << "gPri= " << gPri << ", nums: " << counter << "\n";
    counter = 0;
    ++gPri;
  }
  outFile.close();
  std::cout << "gPri: " << gPri - 1 << "\n";
}
