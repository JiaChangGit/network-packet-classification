#ifndef _HYPERRECTANGLE_COVER_CHECKER_HPP__
#define _HYPERRECTANGLE_COVER_CHECKER_HPP__

#include <algorithm>
#include <fstream>
#include <limits>
#include <unordered_set>

#include "./basis.hpp"

// #define ALLSETS
// NOTICE: 2^n , n = rule5V.size()

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
   * @brief 用於哈希 `std::array<uint32_t, 5>` 的函數對象。
   *
   * 此結構用於在 `unordered_set` 中儲存和查找 5D 坐標的哈希值。
   */
  struct ArrayHash {
    /**
     * @brief 計算 `std::array<uint32_t, 5>` 的哈希值。
     * @param arr 要哈希的 5D 坐標數組。
     * @return 返回哈希值。
     */
    std::size_t operator()(const std::array<uint32_t, 5>& arr) const {
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

#endif
