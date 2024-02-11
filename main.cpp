/**
 * @file main.cpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.4
 * @date 2024-02-11
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>main
 * </table>
 */

#include <getopt.h>

#include <fstream>
#include <vector>

#include "input.hpp"
#include "inputFile_test.hpp"
#include "linearSearch.hpp"
#include "rulesetAnalysis.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::ofstream;
using std::vector;

int main(int argc, char *argv[]) {
  vector<Rule5D> rule5V;
  vector<Packet5D> packet5V;
  InputFile5D inputFile5D;
  InputFile5D_test inputFile5D_test;
  Timer timer;
  const char *loadRule5D_test_path = "./INFO/loadRule5D_test.txt";
  const char *loadPacket5D_test_path = "./INFO/loadPacket5D_test.txt";
  const char *loadRule5D_ip_test_path = "./INFO/loadRule5D_merge_test.txt";
  const char *loadPacket5D_ip_test_path = "./INFO/loadPacket5D_merge_test.txt";

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
        cout << "Read ruleset time(s): " << timer.elapsed_s() << "\n";
        break;
      case 'p':
        cout << "Rread trace: " << optarg << "\n";
        timer.timeReset();
        inputFile5D.loadPacket5D(packet5V, optarg);

        cout << "Read trace time(ns): " << timer.elapsed_ns() << "\n";
        cout << "Read trace time(s): " << timer.elapsed_s() << "\n";
        break;
      case 't':
        // Don't need argument
        timer.timeReset();
        inputFile5D_test.loadRule5D_test(rule5V, loadRule5D_test_path);

        cout << "Input rule test time(ns): " << timer.elapsed_ns() << "\n";
        cout << "Input rule test time(s): " << timer.elapsed_s() << "\n";

        timer.timeReset();
        inputFile5D_test.loadPacket5D_test(packet5V, loadPacket5D_test_path);

        cout << "Input packet test time(ns): " << timer.elapsed_ns() << "\n";
        cout << "Input packet test time(s): " << timer.elapsed_s() << "\n";
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

        return 1;
      default:
        break;
    }
  }

  inputFile5D_test.loadRule5D_ip_test(rule5V, loadRule5D_ip_test_path);
  inputFile5D_test.loadPacket5D_ip_test(packet5V, loadPacket5D_ip_test_path);

  //// === rulesetAnalysis === ////
  cout << "rulesetAnalysis\n";
  size_t rule5V_num = rule5V.size();
  RulesetAnalysis rulesetAnalysis(rule5V);
  rulesetAnalysis.printRule5V_arr(rule5V_num);
  //// === rulesetAnalysis === ////

  //// === LinearSearch === ////
  LinearSearch linearSearch;
  int packet5V_num = packet5V.size();
  timer.timeReset();
  linearSearch.search(rule5V, packet5V);
  cout << "packet5V_num: " << packet5V_num << "\n";
  cout << "LinearSearch time avg (ns): " << (timer.elapsed_ns() / packet5V_num)
       << "\n";
  cout << "LinearSearch time avg (s): " << (timer.elapsed_s() / packet5V_num)
       << "\n";
  //// === LinearSearch === ////
  return 0;
}
