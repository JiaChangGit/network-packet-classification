// g++ -O3 -o a1 a1.cpp -DDEBUG -DCOVER_MANY
// ./a1

// 先將五維range轉為elementary intervals
// 開始檢查 COVER_MANY
//     先 目標rule(Rx) 向上check
//     overlap，收集overlap_set(selectedHyperrectangles)。
//
//     再coveredPoints為與Rx在五維空間中，有overlap的ruleset的elementary_intervals集合。
//
//     最後coversRx函式裡，暴力check，Rx在五維空間中，是否皆被著色。
#include <omp.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#define LowDim 0
#define HighDim 1
#define MAXDIMENSIONS 5

// #define DEBUG
// #define COVER_MANY

// WARNING: O(2^n), n = rules.size()
// #define ALLSETS

struct Rule5D {
  Rule5D(unsigned int dim = 5) : dim(dim), range(dim, {{0, 0}}) {};
  Rule5D(unsigned int dim, unsigned int priority,
         const std::vector<std::array<uint32_t, 2>>& range)
      : dim(dim), priority(priority), range(range) {}

  unsigned int dim;
  unsigned int priority;
  std::vector<std::array<uint32_t, 2>> range;
};

// Helper function to find all unique boundaries for a given axis
std::vector<uint32_t> findBoundaries(const std::vector<Rule5D>& rules,
                                     size_t axis) {
  std::set<uint32_t> boundaries;
  for (const auto& rule : rules) {
    boundaries.insert(rule.range[axis][LowDim]);       // lower bound
    boundaries.insert(rule.range[axis][HighDim] + 1);  // upper bound + 1
  }
  return std::vector<uint32_t>(boundaries.begin(), boundaries.end());
}

/**
 * @brief 將規則範圍轉換為基本區間
 *
 * @param rules 輸入的規則列表
 * @param rule5V_num 規則數量
 */
void convertToElementaryIntervals(std::vector<Rule5D>& rules,
                                  const size_t rule5V_num) {
  std::vector<std::vector<uint32_t>> boundaries(
      MAXDIMENSIONS, std::vector<uint32_t>(2 * rule5V_num));

// Find boundaries for each dimension
// 用OpenMP 平行化加速
#pragma omp parallel for
  for (size_t axis = 0; axis < MAXDIMENSIONS; ++axis) {
    boundaries[axis] = findBoundaries(rules, axis);
  }

  // Iterate over each rule and map it to elementary intervals
  for (size_t id = 0; id < rule5V_num; ++id) {
    std::vector<uint32_t> elements_id_tmp;
    for (size_t axis = 0; axis < MAXDIMENSIONS; ++axis) {
      const size_t boundSize = boundaries[axis].size();
      for (size_t i = 0; i < boundSize - 1; ++i) {
        uint32_t low = boundaries[axis][i];
        uint32_t high = boundaries[axis][i + 1] - 1;

        // Check if the current elementary interval overlaps with the rule's
        // range
        if (low >= rules[id].range[axis][LowDim] &&
            high <= rules[id].range[axis][HighDim]) {
          elements_id_tmp.emplace_back(i);  // Store the elementary interval ID
        }
      }

      rules[id].range[axis][0] = elements_id_tmp[0];
      rules[id].range[axis][1] = elements_id_tmp[elements_id_tmp.size() - 1];
      elements_id_tmp.clear();
    }
  }
}

// ======================================= //
class CoverChecker_many {
 public:
  void checkCoverageAndRecord(const std::vector<Rule5D>& rules,
                              const std::string& fileName);
};

class HyperrectangleCoverChecker {
 public:
  using Hyperrectangle = Rule5D;

  explicit HyperrectangleCoverChecker(const Hyperrectangle& rx);

  void addHyperrectangle(const Hyperrectangle& hyperrect);

  void findFullyCoveredCombinations();

  void outputResultToFile(const std::string& fileName) const;

  const std::vector<std::vector<int>>& getResult() const;

 private:
  Hyperrectangle Rx;
  std::vector<Hyperrectangle> hyperrectangles;
  std::vector<std::vector<int>> result_of_Rx_covered_by;

  //===============//
  /**
   * @struct ArrayHash
   * @brief 用於哈希 `std::array<uint32_t, MAXDIMENSIONS>` 的函數對象。
   *
   * 此結構用於在 `unordered_set` 中儲存和查找 5D 坐標的哈希值。
   */
  struct ArrayHash {
    /**
     * @brief 計算 `std::array<uint32_t, MAXDIMENSIONS>` 的哈希值。
     * @param arr 要哈希的 5D 坐標數組。
     * @return 返回哈希值。
     */
    std::size_t operator()(
        const std::array<uint32_t, MAXDIMENSIONS>& arr) const {
      std::size_t seed = 33;
      for (const auto& i : arr) {
        seed ^=
            std::hash<uint32_t>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    }
  };

  /**
   * @struct VectorHash
   * @brief 用於哈希 `std::vector<int>` 的函數對象。
   *
   * 此結構用於在 `unordered_set` 或 `unordered_map` 中儲存和查找向量的哈希值。
   */
  struct VectorHash {
    /**
     * @brief 計算 `std::vector<int>` 的哈希值。
     * @param vec 要哈希的整數向量。
     * @return 返回哈希值。
     */
    std::size_t operator()(const std::vector<int>& vec) const {
      std::size_t seed = 33;
      for (const auto& i : vec) {
        seed ^= std::hash<int>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    }
  };
  //===============//
  inline bool coversRx(
      const std::unordered_set<std::array<uint32_t, MAXDIMENSIONS>, ArrayHash>&
          coveredPoints) const;

  inline bool intersects(const Hyperrectangle& hyperrect1,
                         const Hyperrectangle& hyperrect2) const;

  inline std::vector<int> buildCombinationVector(
      const std::vector<int>& selectedHyperrectangles) const;
};
// ======================================= //
//  ==============  //
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
      outfile << "R.pri= " << (i + 1) << ": Y\n";
    } else {
      outfile << "R.pri= " << (i + 1) << ": N\n";
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
    std::vector<int> selectedHyperrectangles(n);
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

        coveredPoints.reserve((x_end - x_start + 1) * (y_end - y_start + 1) *
                              (z_end - z_start + 1) * (w_end - w_start + 1) *
                              (v_end - v_start + 1));
#pragma omp parallel for
        for (uint32_t x = x_start; x <= x_end; ++x) {
#pragma omp parallel for
          for (uint32_t y = y_start; y <= y_end; ++y) {
#pragma omp parallel for
            for (uint32_t z = z_start; z <= z_end; ++z) {
#pragma omp parallel for
              for (uint32_t w = w_start; w <= w_end; ++w) {
#pragma omp parallel for
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
//  ==============  //

int main() {
#ifdef COVER_MANY
  const char* CheckCovered_many_path = "CheckCovered_many_a.txt";
#endif

  // Example usage with 5D space
  std::vector<Rule5D> rules = {
      {{MAXDIMENSIONS}, 1, {{14, 14}, {2, 6}, {11, 15}, {7, 18}, {5, 10}}},
      {{MAXDIMENSIONS}, 2, {{8, 13}, {9, 20}, {6, 18}, {14, 22}, {12, 15}}},
      {{MAXDIMENSIONS}, 3, {{3, 25}, {4, 7}, {10, 12}, {8, 30}, {20, 25}}},
      {{MAXDIMENSIONS}, 4, {{1, 5}, {2, 8}, {7, 14}, {15, 20}, {22, 28}}},
      {{MAXDIMENSIONS}, 5, {{10, 20}, {5, 15}, {8, 17}, {11, 19}, {3, 9}}},
      {{MAXDIMENSIONS}, 6, {{6, 11}, {12, 17}, {1, 7}, {14, 25}, {18, 24}}},
      {{MAXDIMENSIONS}, 7, {{7, 15}, {10, 12}, {5, 9}, {8, 15}, {12, 20}}},
      {{MAXDIMENSIONS}, 8, {{2, 9}, {6, 11}, {10, 15}, {16, 23}, {4, 10}}},
      {{MAXDIMENSIONS}, 9, {{13, 18}, {3, 8}, {9, 14}, {11, 17}, {5, 12}}},
      {{MAXDIMENSIONS}, 10, {{15, 22}, {8, 14}, {6, 13}, {19, 27}, {7, 13}}},
      {{MAXDIMENSIONS}, 11, {{5, 10}, {11, 16}, {8, 13}, {21, 28}, {15, 21}}},
      {{MAXDIMENSIONS}, 12, {{8, 12}, {7, 10}, {12, 18}, {14, 19}, {3, 8}}},
      {{MAXDIMENSIONS}, 13, {{3, 7}, {5, 9}, {14, 19}, {9, 16}, {17, 22}}},
      {{MAXDIMENSIONS}, 14, {{9, 14}, {4, 10}, {7, 13}, {11, 17}, {21, 27}}},
      {{MAXDIMENSIONS}, 15, {{12, 17}, {2, 6}, {10, 15}, {8, 13}, {5, 10}}},
      {{MAXDIMENSIONS}, 16, {{10, 20}, {5, 15}, {8, 17}, {11, 19}, {3, 9}}},
  };

  // Convert ranges to elementary intervals
  const size_t rule5V_num = rules.size();
  convertToElementaryIntervals(rules, rule5V_num);

#ifdef DEBUG
  // Print the elementary intervals mapped to each rule
  for (size_t rule_idx = 0; rule_idx < rule5V_num; ++rule_idx) {
    std::cout << "R.pri= " << (rule_idx + 1)
              << ", uses elementary intervals:\n";
    for (size_t axis = 0; axis < MAXDIMENSIONS; ++axis) {
      std::cout << "  Dimension " << axis << ": ";
      for (const auto& elem_id : rules[rule_idx].range[axis]) {
        std::cout << elem_id << " ";
      }
      std::cout << "\n";
    }
  }
#endif

#ifdef COVER_MANY
  CoverChecker_many coverChecker_many;
  coverChecker_many.checkCoverageAndRecord(rules, CheckCovered_many_path);
#endif

  return 0;
}
