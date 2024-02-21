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

#include <fstream>

#include "input.hpp"
#include "inputFile_test.hpp"
#include "linearSearch.hpp"
#include "tSearch.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::ofstream;
using std::vector;

int main(int argc, char* argv[]) {
  vector<Rule5D> rule5V;
  vector<Packet5D> packet5V;
  InputFile5D inputFile5D;
  InputFile5D_test inputFile5D_test;
  Timer timer;
  const char* LoadRule5D_test_path = "./INFO/loadRule5D_test.txt";
  const char* LoadPacket5D_test_path = "./INFO/loadPacket5D_test.txt";

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
        inputFile5D_test.loadRule5D_test(rule5V, LoadRule5D_test_path);

        cout << "Input rule test time(ns): " << timer.elapsed_ns() << "\n";
        cout << "Input rule test time(s): " << timer.elapsed_s() << "\n";

        timer.timeReset();
        inputFile5D_test.loadPacket5D_test(packet5V, LoadPacket5D_test_path);

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

        exit(1);
      default:
        break;
    }
  }

  size_t rule5V_num = rule5V.size();
  if (rule5V_num <= 0) {
    cerr << "rule5V_num: " << rule5V_num << " <= 0\n";
    exit(1);
  }
  cout << "rule5V_num: " << rule5V_num << "\n";
  size_t packet5V_num = packet5V.size();
  if (packet5V_num <= 0) {
    cerr << "packet5V_num: " << packet5V_num << " <= 0\n";
    exit(1);
  }
  cout << "packet5V_num: " << packet5V_num << "\n";

  // //// === LinearSearch === ////
  // LinearSearch linearSearch;
  // timer.timeReset();
  // linearSearch.search(rule5V, packet5V);
  // cout << "LinearSearch time avg (ns): " << (timer.elapsed_ns() /
  // packet5V_num)
  //      << "\n";
  // cout << "LinearSearch time avg (s): " << (timer.elapsed_s() / packet5V_num)
  //      << "\n";
  // //// === LinearSearch === ////

  //// === tSearch === ////
  TSearch tSearch(8, 17);
  tSearch.partition(rule5V, rule5V_num);
  //// === tSearch === ////

  return 0;
}
