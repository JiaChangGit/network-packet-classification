#include "ksetSearch.hpp"
void KsetSearch::partition(std::vector<Rule5D>& rule5V, const size_t rule5V_num,
                           const size_t prefixPartition) {
  for (const auto& rule : rule5V) {
    if ((rule.ipSMask >= 16) && (rule.ipDMask >= 16)) {
      subset0.emplace_back(rule);
    } else if ((rule.ipSMask >= 16) && (rule.ipDMask < 16)) {
      subset1.emplace_back(rule);
    } else if ((rule.ipSMask < 16) && (rule.ipDMask >= 16)) {
      subset2.emplace_back(rule);
    } else if ((rule.ipSMask < 16) && (rule.ipDMask < 16)) {
      subset3.emplace_back(rule);
    }
  }
  subsetNum[0] = subset0.size();
  subsetNum[1] = subset1.size();
  subsetNum[2] = subset2.size();
  subsetNum[3] = subset3.size();
  for (int i = 0; i < 3; ++i) {
    if (subsetNum[i] < 1) {
      std::cerr << "Wrong subsetNum[ " << i << " ]\n";
      exit(1);
    }
    usedBits[i] = log2(subsetNum[i]);
    if (8 > usedBits[i]) {
      std::cout << "!! usedBits[ " << i << " ] < 8\n";
      usedBits[i] = 8;
    } else if (16 < usedBits[i]) {
      std::cout << "!! usedBits[ " << i << " ] > 16\n";
      usedBits[i] = 16;
    }
    std::cout << "usedBits[ " << i << " ]: " << usedBits[i] << "\n";
  }
  std::cout << "rule5V_num: " << rule5V_num << "\n";
  std::cout << "subsetNum: " << subsetNum[0] << ", " << subsetNum[1] << ", "
            << subsetNum[2] << ", " << subsetNum[3] << "\n";

  if (rule5V_num !=
      (subsetNum[0] + subsetNum[1] + subsetNum[2] + subsetNum[3])) {
    std::cerr << "Wrong prePartition!!\n";
    exit(1);
  }

  std::vector<Rule5D>().swap(subset0);
  std::vector<Rule5D>().swap(subset1);
  std::vector<Rule5D>().swap(subset2);
  std::vector<Rule5D>().swap(subset3);
  for (const auto& rule : rule5V) {
    if ((rule.ipSMask >= usedBits[0]) && (rule.ipDMask >= usedBits[0])) {
      subset0.emplace_back(rule);
    } else if (rule.ipSMask >= usedBits[1]) {
      subset1.emplace_back(rule);
    } else if (rule.ipDMask >= usedBits[2]) {
      subset2.emplace_back(rule);
    } else {
      subset3.emplace_back(rule);
    }
  }
  subsetNum[0] = subset0.size();
  subsetNum[1] = subset1.size();
  subsetNum[2] = subset2.size();
  subsetNum[3] = subset3.size();
  std::cout << "subsetNum: " << subsetNum[0] << ", " << subsetNum[1] << ", "
            << subsetNum[2] << ", " << subsetNum[3] << "\n";
  if (rule5V_num !=
      (subsetNum[0] + subsetNum[1] + subsetNum[2] + subsetNum[3])) {
    std::cerr << "Wrong partition !!\n";
    exit(1);
  }
};
