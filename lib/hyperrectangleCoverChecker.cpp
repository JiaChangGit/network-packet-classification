#include "hyperrectangleCoverChecker.hpp"

void CoverChecker_many::checkCoverageAndRecord(const std::vector<Rule5D>& rules,
                                               const std::string& fileName) {
  std::ofstream outfile(fileName);
  if (!outfile.is_open()) {
    std::cerr << "無法打開文件: " << fileName << "\n";
    exit(1);
  }
  const size_t rSize = rules.size();
  // 逐一檢查每個 Rule5D 是否被前面的規則集合完全覆蓋
  for (size_t i = 1; i < rSize; ++i) {
    const Rule5D& ruleCurrent = rules[i];
    HyperrectangleCoverChecker checker(ruleCurrent);

    // 將前面的規則添加到 checker 中
    for (size_t j = 0; j < i; ++j) {
      checker.addHyperrectangle(rules[j]);
    }

    // 查找所有能完全覆蓋 Rx 的超矩形組合
    checker.findFullyCoveredCombinations();

    // 確認當前規則是否被完全覆蓋
    if (!checker.getResult().empty()) {
      outfile << "R.Pri= " << (ruleCurrent.priority) << ": Y\n";
    } else {
      outfile << "R.Pri= " << (ruleCurrent.priority) << ": N\n";
    }
  }

  outfile.close();
}

HyperrectangleCoverChecker::HyperrectangleCoverChecker(const Hyperrectangle& rx)
    : Rx(rx) {}

void HyperrectangleCoverChecker::addHyperrectangle(
    const Hyperrectangle& hyperrect) {
  hyperrectangles.emplace_back(hyperrect);
}

void HyperrectangleCoverChecker::findFullyCoveredCombinations() {
  const int n = hyperrectangles.size();
  std::unordered_set<std::vector<int>, VectorHash> uniqueCombinations(n);

#ifdef ALLSETS
  for (int mask = 1; mask < (1 << n); ++mask) {
#endif
    std::vector<int> selectedHyperrectangles;
    selectedHyperrectangles.reserve(n);
    std::unordered_set<std::array<uint32_t, MAXDIMENSIONS>, ArrayHash>
        coveredPoints;

    for (int j = 0; j < n; ++j) {
#ifdef ALLSETS
      if (mask & (1 << j)) {
#endif
        const auto& hyperrect = hyperrectangles[j];

        if (!intersects(hyperrect, Rx)) {
          continue;
        }

        selectedHyperrectangles.emplace_back(j);

        uint32_t x_start = std::max(hyperrect.range[0][0], Rx.range[0][0]);
        uint32_t x_end = std::min(hyperrect.range[0][1], Rx.range[0][1]);
        uint32_t y_start = std::max(hyperrect.range[1][0], Rx.range[1][0]);
        uint32_t y_end = std::min(hyperrect.range[1][1], Rx.range[1][1]);
        uint32_t z_start = std::max(hyperrect.range[2][0], Rx.range[2][0]);
        uint32_t z_end = std::min(hyperrect.range[2][1], Rx.range[2][1]);
        uint32_t w_start = std::max(hyperrect.range[3][0], Rx.range[3][0]);
        uint32_t w_end = std::min(hyperrect.range[3][1], Rx.range[3][1]);
        uint32_t v_start = std::max(hyperrect.range[4][0], Rx.range[4][0]);
        uint32_t v_end = std::min(hyperrect.range[4][1], Rx.range[4][1]);

        // coveredPoints.reserve((x_end - x_start + 1) * (y_end - y_start + 1) *
        //                       (z_end - z_start + 1) * (w_end - w_start + 1) *
        //                       (v_end - v_start + 1));

        for (uint32_t x = x_start; x <= x_end; ++x) {
          for (uint32_t y = y_start; y <= y_end; ++y) {
            for (uint32_t z = z_start; z <= z_end; ++z) {
              for (uint32_t w = w_start; w <= w_end; ++w) {
                for (uint32_t v = v_start; v <= v_end; ++v) {
                  coveredPoints.insert({x, y, z, w, v});
                }
              }
            }
          }
        }
#ifdef ALLSETS
      }
#endif
    }

    if (coversRx(coveredPoints)) {
#ifndef ALLSETS
      // To delete all elements and release memory:
      std::unordered_set<std::array<uint32_t, 5ULL>,
                         HyperrectangleCoverChecker::ArrayHash>()
          .swap(coveredPoints);
#endif
      std::sort(selectedHyperrectangles.begin(), selectedHyperrectangles.end());
      if (uniqueCombinations.emplace(selectedHyperrectangles).second) {
        result_of_Rx_covered_by.emplace_back(
            buildCombinationVector(selectedHyperrectangles));
      }
    }
#ifdef ALLSETS
  }
#endif
}

void HyperrectangleCoverChecker::outputResultToFile(
    const std::string& fileName) const {
  std::ofstream outfile(fileName);
  if (!outfile.is_open()) {
    std::cerr << "無法打開文件: " << fileName << "\n";
    return;
  }

  for (const auto& combination : result_of_Rx_covered_by) {
    outfile << "Rx 被 (";
    size_t combSize = combination.size();
    for (size_t j = 0; j < combSize; ++j) {
      outfile << "R.Pri: " << hyperrectangles[combination[j]].priority;
      if (j < combSize - 1) {
        outfile << ", ";
      }
    }
    outfile << ")\n";
  }
  outfile.close();
}

const std::vector<std::vector<int>>& HyperrectangleCoverChecker::getResult()
    const {
  return result_of_Rx_covered_by;
}

inline bool HyperrectangleCoverChecker::coversRx(
    const std::unordered_set<std::array<uint32_t, MAXDIMENSIONS>, ArrayHash>&
        coveredPoints) const {
  for (uint32_t x = Rx.range[0][0]; x <= Rx.range[0][1]; ++x) {
    for (uint32_t y = Rx.range[1][0]; y <= Rx.range[1][1]; ++y) {
      for (uint32_t z = Rx.range[2][0]; z <= Rx.range[2][1]; ++z) {
        for (uint32_t w = Rx.range[3][0]; w <= Rx.range[3][1]; ++w) {
          for (uint32_t v = Rx.range[4][0]; v <= Rx.range[4][1]; ++v) {
            if (coveredPoints.find({x, y, z, w, v}) == coveredPoints.end()) {
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

inline bool HyperrectangleCoverChecker::intersects(
    const Hyperrectangle& hyperrect1, const Hyperrectangle& hyperrect2) const {
  for (size_t i = 0; i < MAXDIMENSIONS; ++i) {
    if (std::max(hyperrect1.range[i][0], hyperrect2.range[i][0]) >
        std::min(hyperrect1.range[i][1], hyperrect2.range[i][1])) {
      return false;
    }
  }
  return true;
}

inline std::vector<int> HyperrectangleCoverChecker::buildCombinationVector(
    const std::vector<int>& selectedHyperrectangles) const {
  return selectedHyperrectangles;
}
