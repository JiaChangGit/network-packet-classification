#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <vector>

#define LowDim 0
#define HighDim 1
#define MAXDIMENSIONS 5
#define COVERCHECKER_MANY

struct Rule5D {
#ifdef COVERCHECKER_MANY
  Rule5D(unsigned int dim = 5)
      : dim(dim), range(dim, {{0, 0}}), elements_id(dim, {{0, 0}}) {};
  Rule5D(unsigned int dim, unsigned int priority,
         const std::vector<std::array<uint32_t, 2>>& range)
      : dim(dim),
        priority(priority),
        range(range),
        elements_id(dim, {{0, 0}}) {}
  std::vector<std::array<uint32_t, 2>> elements_id;
#else
  Rule5D(unsigned int dim = 5) : dim(dim), range(dim, {{0, 0}}) {};
#endif
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

// Function to convert ranges to elementary intervals across all dimensions
void convertToElementaryIntervals(std::vector<Rule5D>& rules) {
  std::vector<std::vector<uint32_t>> boundaries(MAXDIMENSIONS);
  // Find boundaries for each dimension
  for (size_t axis = 0; axis < MAXDIMENSIONS; ++axis) {
    boundaries[axis] = findBoundaries(rules, axis);
  }

  // Iterate over each rule and map it to elementary intervals
  const size_t num = rules.size();
  for (size_t id = 0; id < num; ++id) {
    for (size_t axis = 0; axis < 5; ++axis) {
      std::vector<uint32_t> elements_id_tmp;
      for (size_t i = 0; i < boundaries[axis].size() - 1; ++i) {
        uint32_t low = boundaries[axis][i];
        uint32_t high = boundaries[axis][i + 1] - 1;

        // Check if the current elementary interval overlaps with the rule's
        // range
        if (low >= rules[id].range[axis][LowDim] &&
            high <= rules[id].range[axis][HighDim]) {
          elements_id_tmp.emplace_back(i);  // Store the elementary interval ID
        }
      }

      rules[id].elements_id[axis][0] = elements_id_tmp[0];
      rules[id].elements_id[axis][1] =
          elements_id_tmp[elements_id_tmp.size() - 1];
    }
  }
}

int main() {
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
  convertToElementaryIntervals(rules);

  // Print the elementary intervals mapped to each rule
  for (size_t rule_idx = 0; rule_idx < rules.size(); ++rule_idx) {
    std::cout << "R.pri= " << (rule_idx + 1)
              << ", uses elementary intervals:\n";
    for (unsigned int axis = 0; axis < rules[rule_idx].dim; ++axis) {
      std::cout << "  Dimension " << axis << ": ";
      for (const auto& elem_id : rules[rule_idx].elements_id[axis]) {
        std::cout << elem_id << " ";
      }
      std::cout << "\n";
    }
  }

  return 0;
}
