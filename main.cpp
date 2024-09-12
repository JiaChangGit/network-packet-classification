/**
 * @file main.cpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.5
 * @date 2024-02-11
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-11 <td>1.5     <td>jiachang     <td>main
 * </table>
 */

#include <getopt.h>
#include <omp.h>

#include <fstream>
#include <set>

#include "checkCovered_one.hpp"
#include "equivalentPri.hpp"
#include "hyperrectangleCoverChecker.hpp"
#include "input.hpp"
#include "inputFile_test.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::ofstream;
using std::string;
using std::vector;

#define P15
// #define DEBUG
// #define LAYER
// #define COVER_ONE
// #define ELEMENTARY
// #define COVER_MANY
// #define FOUR

#if defined ELEMENTARY || defined FOUR
// Helper function to find all unique boundaries for a given axis
inline std::vector<uint32_t> findBoundaries(const std::vector<Rule5D>& rules,
                                            const size_t axis) {
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
  std::vector<std::vector<uint32_t>> boundaries(MAXDIMENSIONS);

  // 用OpenMP 平行化加速
#pragma omp parallel for
  for (size_t axis = 0; axis < MAXDIMENSIONS; ++axis) {
    boundaries[axis] = findBoundaries(rules, axis);
  }

  // 迭代每個規則，並將其映射到基本區間
  for (size_t id = 0; id < rule5V_num; ++id) {
    for (size_t axis = 0; axis < MAXDIMENSIONS; ++axis) {
      const size_t boundSize = boundaries[axis].size();
      std::vector<uint32_t> elements_id_tmp(boundSize, 0);
      size_t ele_tmp_id = 0;
      for (size_t i = 0; i < boundSize - 1; ++i) {
        uint32_t low = boundaries[axis][i];
        uint32_t high = boundaries[axis][i + 1] - 1;

        // 檢查當前的基本區間是否與規則的範圍重疊
        if (low >= rules[id].range[axis][LowDim] &&
            high <= rules[id].range[axis][HighDim]) {
          elements_id_tmp[ele_tmp_id] = (i);  // 存儲基本區間 ID
          ++ele_tmp_id;
        }
      }
      if (ele_tmp_id > 0) {
        rules[id].range[axis][0] = elements_id_tmp[0];
        rules[id].range[axis][1] = elements_id_tmp[ele_tmp_id - 1];
      } else {
#ifdef DEBUG
        std::cout << "id, dim: " << id << ", " << axis << "; ele_tmp_id == 0\n";
#endif
        rules[id].range[axis][0] = elements_id_tmp[0];
        rules[id].range[axis][1] = elements_id_tmp[0];
      }
    }
  }
}
// 核心邏輯說明：

// 目標：
// 這段代碼的目標是將一組多維範圍 (Rule5D) 轉換為 elementary
// intervals，並記錄每個規則在不同維度上對應的 elementary intervals。
// 最終目的是通過 OpenMP 並行化進行優化，加快這一過程。

// 1. findBoundaries 函數：
// 這個函數提取每個維度上所有規則的邊界 (lower bound 和 upper bound +
// 1)，並將它們存儲在 std::set 中，然後轉換為 std::vector。 使用 std::set
// 確保了邊界的唯一性和有序性，這是正確的。

// 2. convertToElementaryIntervals 函數：
//    邊界計算：
//    使用 findBoundaries 函數來計算每個維度的邊界，並將結果存儲在 boundaries
//    向量中。 這裡使用了 OpenMP
//    並行化，平行計算每個維度的邊界。這在理論上是正確的，因為每個維度是獨立的。

//    迭代規則和映射到 elementary intervals：
//    內部的兩個循環遍歷每個規則和每個維度的邊界，判斷規則範圍是否與該維度的
//    elementary interval 重疊。如果重疊，則記錄該 elementary interval。
//    邏輯上這部分是正確的，因為它檢查了範圍的重疊，並使用 elements_id_tmp
//    記錄該重疊的 ID。

//    處理 elements_id_tmp：
//    內部循環中，elements_id_tmp 用於暫存對應的 elementary intervals
//    ID，並在每次維度處理結束後重置為 0。 使用
//    std::fill(elements_id_tmp.begin(), elements_id_tmp.end(), 0)
//    是正確的做法，這樣保證向量的大小不變，同時清空其內容以便下一次使用。

//    範圍更新：
//    最後，根據 elements_id_tmp
//    來更新規則在每個維度的範圍（即記錄該規則在每個維度上包含的 elementary
//    intervals 的 ID 範圍）。 當 ele_tmp_id == 0
//    時，表示該規則在該維度上不包含任何 elementary intervals，因此將
//    range[axis][1] 設置為 elements_id_tmp[0] 也是合理的。

// 潛在問題：
// 1. 元素 ID 的範圍：
// 在處理 elements_id_tmp
// 時，確保每個範圍的更新是正確的。如果一個規則的範圍不覆蓋任何 elementary
// interval，代碼會將其 range[axis][1] 設置為
// elements_id_tmp[0]，這可能需要檢查是否符合邏輯要求。

// 2. 內存和性能：
// 在每個規則和每個維度的循環中，向量 elements_id_tmp 會被重置為 0
// 以便下一次使用。這可能導致不必要的內存操作，尤其是在向量非常大時。不過，這樣做的目的是為了確保每次處理的數據是獨立的，從這個角度來看是合理的。

// 3. OpenMP 並行化的影響：
// 雖然使用 OpenMP
// 並行化計算邊界是正確的，但要確保這部分代碼在多核環境下實際上能夠獲得性能提升。在某些情況下，並行化帶來的額外開銷可能會抵消性能提升。

// 結論：
// 功能上，這段代碼是邏輯正確的，應該能夠達到將範圍轉換為 elementary intervals
// 並記錄相應 ID 的目標。性能上，主要的考量是 OpenMP
// 的並行化效果以及內存操作的開銷。

#endif

int main(int argc, char* argv[]) {
  vector<Rule5D> rule5V;
  vector<Packet5D> packet5V;
  InputFile5D inputFile5D;
  InputFile5D_test inputFile5D_test;
  Timer timer;
  const char* LoadRule5D_test_path = "../../INFO/loadRule5D_test.txt";
  const char* LoadPacket5D_test_path = "../../INFO/loadPacket5D_test.txt";

#ifdef P15
  const char* prefix15Uniq_path = "../../INFO/Prefix15Uniq.txt";
#endif
#ifdef LAYER
  const char* EquivalentPri_path = "../../INFO/EquivalentPri.txt";
#endif
#ifdef COVER_ONE
  const char* CheckCovered_one_path = "../../INFO/CheckCovered_one.txt";
#endif
#ifdef ELEMENTARY
  const char* Elementary_path = "../../INFO/Elementary.txt";
#endif
#ifdef COVER_MANY
  const char* CheckCovered_many_path = "../../INFO/CheckCovered_many.txt";
#endif
#ifdef FOUR
  const char* Elementary_SMALL_path = "../../INFO/Elementary_SMALL.txt";
  const char* Elementary_BIG_path = "../../INFO/Elementary_BIG.txt";
  const char* Elementary_BIG_SIP_path = "../../INFO/Elementary_BIG_SIP.txt";
  const char* Elementary_BIG_DIP_path = "../../INFO/Elementary_BIG_DIP.txt";

  const char* CheckCovered_SMALL_path = "../../INFO/CheckCovered_SMALL.txt";
  const char* CheckCovered_BIG_path = "../../INFO/CheckCovered_BIG.txt";
  const char* CheckCovered_BIG_SIP_path = "../../INFO/CheckCovered_BIG_SIP.txt";
  const char* CheckCovered_BIG_DIP_path = "../../INFO/CheckCovered_BIG_DIP.txt";
#endif

  static struct option long_options[] = {
      {"ruleset", required_argument, NULL, 'r'},
      {"trace", required_argument, NULL, 'p'},
      {"test", no_argument, NULL, 't'},
      {"help", no_argument, NULL, 'h'},
      {0, 0, 0, 0}  // End of options marker
  };
  int option;
  while ((option = getopt_long(argc, argv, "r:p:t::h::", long_options,
                               nullptr)) != -1) {
    switch (option) {
      case 'r':
        cout << "Read ruleset:  " << optarg << "\n";
        timer.timeReset();
        inputFile5D.loadRule5D(rule5V, optarg);

        cout << "Read ruleset time(ns): " << timer.elapsed_ns() << "\n";
        // cout << "Read ruleset time(s): " << timer.elapsed_s() << "\n";
        break;
      case 'p':
        cout << "Rread trace: " << optarg << "\n";
        timer.timeReset();
        inputFile5D.loadPacket5D(packet5V, optarg);

        cout << "Read trace time(ns): " << timer.elapsed_ns() << "\n";
        // cout << "Read trace time(s): " << timer.elapsed_s() << "\n";
        break;
      case 't':
        // Don't need argument
        timer.timeReset();
        inputFile5D_test.loadRule5D_test(rule5V, LoadRule5D_test_path);

        cout << "Input rule test time(ns): " << timer.elapsed_ns() << "\n";
        // cout << "Input rule test time(s): " << timer.elapsed_s() << "\n";

        timer.timeReset();
        inputFile5D_test.loadPacket5D_test(packet5V, LoadPacket5D_test_path);

        cout << "Input packet test time(ns): " << timer.elapsed_ns() << "\n";
        // cout << "Input packet test time(s): " << timer.elapsed_s() << "\n";
        break;

      case 'h':
        // Don't need argument
        cout << "****************************"
             << "\n";

        cout << "****************************"
             << "\n";

        break;
      case '?':
        // Invalid option or missing argument
        cerr << "Usage: " << argv[0] << " -h   to get help\n";

        exit(1);
      default:
        break;
    }
  }

  const size_t rule5V_num = rule5V.size();
  rule5V.resize(rule5V_num);
#ifdef DEBUG
  if (rule5V_num <= 0) {
    cerr << "rule5V_num: " << rule5V_num << " <= 0\n";
    exit(1);
  }
#endif
  cout << "rule5V_num: " << rule5V_num << "\n";

  size_t packet5V_num = packet5V.size();
#ifdef DEBUG
  if (packet5V_num <= 0) {
    cerr << "packet5V_num: " << packet5V_num << " <= 0\n";
    exit(1);
  }
#endif
  cout << "packet5V_num: " << packet5V_num << "\n";
  packet5V.resize(packet5V_num);

  // ************ //

#ifdef P15
  ofstream prefix15Uniq_out(prefix15Uniq_path);
  vector<Rule5D> v15;
  for (const auto& It : rule5V) {
    if (It.prefix_length[0] >= 15) {
      v15.emplace_back(It);
    }
  }

  // 2^15 = 32768
  vector<unsigned int> priV[32768];
  for (const auto& It : v15) {
    uint32_t sa = It.range[0][0] >> (32 - 15);
    priV[sa].emplace_back(It.priority);
  }
  size_t pSize_one = 0;
  size_t pSize_max = 0;
  size_t spacesNum = 0;

  for (size_t i = 0; i < 32768; ++i) {
    size_t pSize = priV[i].size();
    prefix15Uniq_out << "i: " << i << "\n";
    for (size_t j = 0; j < pSize; ++j) {
      string spaces(spacesNum, ' ');
      prefix15Uniq_out << spaces << "-> " << priV[i][j] << "\n";
      ++spacesNum;
    }
    prefix15Uniq_out << "\n";
    spacesNum = 0;
    if (pSize == 1) {
      pSize_one++;
    }
    if (pSize_max < pSize) {
      pSize_max = pSize;
    }
  }
  cout << "pSize_one = " << pSize_one << "\n";
  cout << "pSize_max = " << pSize_max << "\n";
  prefix15Uniq_out.close();
#endif
// ************ //

// ================ //
#ifdef LAYER
  EquivalentPri equivalentPri;
  equivalentPri.pri_MSversion(rule5V, rule5V_num);
  equivalentPri.print(EquivalentPri_path);
#endif
// ================ //

// =======================//
#ifdef COVER_ONE
  timer.timeReset();
  CoverChecker_one coverChecker_one;
  coverChecker_one.checkCoverageAndRecord(rule5V, CheckCovered_one_path);
  cout << "coverChecker_one   time(s): " << timer.elapsed_s() << "\n";
#endif
// =======================//

// ==================================================== //
// Convert ranges to elementary intervals
#ifdef ELEMENTARY
  timer.timeReset();
  convertToElementaryIntervals(rule5V, rule5V_num);
  cout << "convert To ElementaryIntervals END   time(s): " << timer.elapsed_s()
       << "\n";

  ofstream outfile_elem(Elementary_path);
  for (size_t i = 0; i < rule5V_num; ++i) {
    outfile_elem << "R.pri= " << (i + 1) << ", elementary:\n"
                 << static_cast<unsigned int>(rule5V[i].range[0][0]) << ", "
                 << static_cast<unsigned int>(rule5V[i].range[0][1]) << "\n"
                 << static_cast<unsigned int>(rule5V[i].range[1][0]) << ",  "
                 << static_cast<unsigned int>(rule5V[i].range[1][1]) << "\n"
                 << static_cast<unsigned int>(rule5V[i].range[2][0]) << ",   "
                 << static_cast<unsigned int>(rule5V[i].range[2][1]) << "\n"
                 << static_cast<unsigned int>(rule5V[i].range[3][0]) << ",    "
                 << static_cast<unsigned int>(rule5V[i].range[3][1]) << "\n"
                 << static_cast<unsigned int>(rule5V[i].range[4][0]) << ",     "
                 << static_cast<unsigned int>(rule5V[i].range[4][1])
                 << "\n===============================================\n\n";
  }
  outfile_elem.close();
#endif
  // ==================================================== //

  // ==================================================== //
#ifdef COVER_MANY
  timer.timeReset();
  CoverChecker_many coverChecker_many;
  coverChecker_many.checkCoverageAndRecord(rule5V, CheckCovered_many_path);
  cout << "CoverChecker_many   time(s): " << timer.elapsed_s() << "\n";
#endif
// ==================================================== //

// ==================================================== //
#ifdef FOUR
  vector<Rule5D> rules_Small;
  vector<Rule5D> rules_Big;
  vector<Rule5D> rules_Big_SIP;
  vector<Rule5D> rules_Big_DIP;
  for (auto& it : rule5V) {
    if ((it.prefix_length[0] >= 10) && (it.prefix_length[1] >= 10)) {
      rules_Small.emplace_back(it);
    }
    if ((it.prefix_length[0] <= 12) && (it.prefix_length[1] <= 12)) {
      rules_Big.emplace_back(it);
    }
    if ((it.prefix_length[0] <= 12) && (it.prefix_length[1] >= 10)) {
      rules_Big_SIP.emplace_back(it);
    }
    if ((it.prefix_length[0] >= 10) && (it.prefix_length[1] <= 12)) {
      rules_Big_DIP.emplace_back(it);
    }
  }
  const size_t rules_SmallSize = rules_Small.size();
  const size_t rules_BigSize = rules_Big.size();
  const size_t rules_Big_SIP_Size = rules_Big_SIP.size();
  const size_t rules_Big_DIP_Size = rules_Big_DIP.size();
  rules_Small.resize(rules_SmallSize);
  rules_Big.resize(rules_BigSize);
  rules_Big_SIP.resize(rules_Big_SIP_Size);
  rules_Big_DIP.resize(rules_Big_DIP_Size);
  rule5V.clear();
  rule5V.shrink_to_fit();

  timer.timeReset();
  convertToElementaryIntervals(rules_Small, rules_SmallSize);
  convertToElementaryIntervals(rules_Big, rules_BigSize);
  convertToElementaryIntervals(rules_Big_SIP, rules_Big_SIP_Size);
  convertToElementaryIntervals(rules_Big_DIP, rules_Big_DIP_Size);
  cout << "convert To ElementaryIntervals(S&B) END  time(s): "
       << timer.elapsed_s() << "\n";
  cout << "rules_Small size: " << rules_SmallSize
       << ", rules_Big size: " << rules_BigSize
       << ", rules_Big_SIP size: " << rules_Big_SIP_Size
       << ", rules_Big_DIP size: " << rules_Big_DIP_Size << "\n";

  ofstream outfile_elemSMALL(Elementary_SMALL_path);
  for (size_t i = 0; i < rules_SmallSize; ++i) {
    outfile_elemSMALL
        << "R.pri= " << (rules_Small[i].priority) << ", elementary:\n"
        << static_cast<unsigned int>(rules_Small[i].range[0][0]) << ", "
        << static_cast<unsigned int>(rules_Small[i].range[0][1]) << "\n"
        << static_cast<unsigned int>(rules_Small[i].range[1][0]) << ",  "
        << static_cast<unsigned int>(rules_Small[i].range[1][1]) << "\n"
        << static_cast<unsigned int>(rules_Small[i].range[2][0]) << ",   "
        << static_cast<unsigned int>(rules_Small[i].range[2][1]) << "\n"
        << static_cast<unsigned int>(rules_Small[i].range[3][0]) << ",    "
        << static_cast<unsigned int>(rules_Small[i].range[3][1]) << "\n"
        << static_cast<unsigned int>(rules_Small[i].range[4][0]) << ",     "
        << static_cast<unsigned int>(rules_Small[i].range[4][1])
        << "\n===============================================\n\n";
  }
  outfile_elemSMALL.close();

  ofstream outfile_elemBIG(Elementary_BIG_path);
  for (size_t i = 0; i < rules_BigSize; ++i) {
    outfile_elemBIG
        << "R.pri= " << (rules_Big[i].priority) << ", elementary:\n"
        << static_cast<unsigned int>(rules_Big[i].range[0][0]) << ", "
        << static_cast<unsigned int>(rules_Big[i].range[0][1]) << "\n"
        << static_cast<unsigned int>(rules_Big[i].range[1][0]) << ",  "
        << static_cast<unsigned int>(rules_Big[i].range[1][1]) << "\n"
        << static_cast<unsigned int>(rules_Big[i].range[2][0]) << ",   "
        << static_cast<unsigned int>(rules_Big[i].range[2][1]) << "\n"
        << static_cast<unsigned int>(rules_Big[i].range[3][0]) << ",    "
        << static_cast<unsigned int>(rules_Big[i].range[3][1]) << "\n"
        << static_cast<unsigned int>(rules_Big[i].range[4][0]) << ",     "
        << static_cast<unsigned int>(rules_Big[i].range[4][1])
        << "\n===============================================\n\n";
  }
  outfile_elemBIG.close();

  ofstream outfile_elemBIG_SIP(Elementary_BIG_SIP_path);
  for (size_t i = 0; i < rules_Big_SIP_Size; ++i) {
    outfile_elemBIG_SIP
        << "R.pri= " << (rules_Big_SIP[i].priority) << ", elementary:\n"
        << static_cast<unsigned int>(rules_Big_SIP[i].range[0][0]) << ", "
        << static_cast<unsigned int>(rules_Big_SIP[i].range[0][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_SIP[i].range[1][0]) << ",  "
        << static_cast<unsigned int>(rules_Big_SIP[i].range[1][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_SIP[i].range[2][0]) << ",   "
        << static_cast<unsigned int>(rules_Big_SIP[i].range[2][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_SIP[i].range[3][0]) << ",    "
        << static_cast<unsigned int>(rules_Big_SIP[i].range[3][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_SIP[i].range[4][0]) << ",     "
        << static_cast<unsigned int>(rules_Big_SIP[i].range[4][1])
        << "\n===============================================\n\n";
  }
  outfile_elemBIG_SIP.close();

  ofstream outfile_elemBIG_DIP(Elementary_BIG_DIP_path);
  for (size_t i = 0; i < rules_Big_DIP_Size; ++i) {
    outfile_elemBIG_DIP
        << "R.pri= " << (rules_Big_DIP[i].priority) << ", elementary:\n"
        << static_cast<unsigned int>(rules_Big_DIP[i].range[0][0]) << ", "
        << static_cast<unsigned int>(rules_Big_DIP[i].range[0][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_DIP[i].range[1][0]) << ",  "
        << static_cast<unsigned int>(rules_Big_DIP[i].range[1][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_DIP[i].range[2][0]) << ",   "
        << static_cast<unsigned int>(rules_Big_DIP[i].range[2][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_DIP[i].range[3][0]) << ",    "
        << static_cast<unsigned int>(rules_Big_DIP[i].range[3][1]) << "\n"
        << static_cast<unsigned int>(rules_Big_DIP[i].range[4][0]) << ",     "
        << static_cast<unsigned int>(rules_Big_DIP[i].range[4][1])
        << "\n===============================================\n\n";
  }
  outfile_elemBIG_DIP.close();

  timer.timeReset();
  CoverChecker_many coverChecker_many_SMALL;
  coverChecker_many_SMALL.checkCoverageAndRecord(rules_Small,
                                                 CheckCovered_SMALL_path);
  cout << "coverChecker_many_SMALL  time(s): " << timer.elapsed_s() << "\n";
  rules_Small.clear();
  rules_Small.shrink_to_fit();

  timer.timeReset();
  CoverChecker_many coverChecker_many_BIG;
  coverChecker_many_BIG.checkCoverageAndRecord(rules_Big,
                                               CheckCovered_BIG_path);
  cout << "coverChecker_many_BIG  time(s): " << timer.elapsed_s() << "\n";
  rules_Big.clear();
  rules_Big.shrink_to_fit();

  timer.timeReset();
  CoverChecker_many coverChecker_many_BIG_SIP;
  coverChecker_many_BIG_SIP.checkCoverageAndRecord(rules_Big_SIP,
                                                   CheckCovered_BIG_SIP_path);
  cout << "coverChecker_many_BIG_SIP  time(s): " << timer.elapsed_s() << "\n";
  rules_Big_SIP.clear();
  rules_Big_SIP.shrink_to_fit();

  timer.timeReset();
  CoverChecker_many coverChecker_many_BIG_DIP;
  coverChecker_many_BIG_DIP.checkCoverageAndRecord(rules_Big_DIP,
                                                   CheckCovered_BIG_DIP_path);
  cout << "coverChecker_many_BIG_DIP  time(s): " << timer.elapsed_s() << "\n";
  rules_Big_DIP.clear();
  rules_Big_DIP.shrink_to_fit();
#endif
  // ==================================================== //

  return 0;
}
