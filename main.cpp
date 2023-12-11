/*
 * @title: main.cpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-08
 */
#include "./IO/IO_TEST/inputFile_test.hpp"
#include "./IO/input_v1.hpp"
#include "./IO/output_v1.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::vector;
int main(int argc, char *argv[]) {
  vector<Rule_5D> rule5V;
  vector<Packet_5D> packet5V;
  InputFile5D InputFile_5D;
  InputFile5D_test InputFile5D_test;
  OutputFile5D OutputFile_5D;
  vector<int> filterNum;

  static struct option long_options[] = {
      {"ruleset", required_argument, NULL, 'r'},
      {"trace", required_argument, NULL, 'p'},
      {"unit_test", no_argument, NULL, 't'},
      {"merge", no_argument, NULL, 'm'},
      {"merge_test", no_argument, NULL, 'n'},
      {"help", no_argument, NULL, 'h'},
      {0, 0, 0, 0}  // End of options marker
  };
  int option;
  while ((option = getopt_long(argc, argv, "r:p:t::m::n::h::", long_options,
                               nullptr)) != -1) {
    switch (option) {
      case 'r':
        cout << "Read ruleset:  " << optarg << "\n";
        OutputFile_5D.timer.timeReset();
        if (InputFile_5D.inputRule5D(rule5V, optarg)) {
          cout << "Read ruleset ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Read ruleset time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Read ruleset time(s): " << OutputFile_5D.timer.elapsed_s()
             << "\n";
        break;
      case 'p':
        cout << "Rread trace: " << optarg << "\n";
        OutputFile_5D.timer.timeReset();
        if (InputFile_5D.inputPacket5D(packet5V, optarg, filterNum)) {
          cout << "Read trace ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Read trace time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Read trace time(s): " << OutputFile_5D.timer.elapsed_s()
             << "\n";
        break;
      case 't':
        // Don't need argument
        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputRule5D_test(rule5V,
                                              "./test/inputRule5D_test.txt")) {
          cout << "Input Rule test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input rule test time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Input rule test time(s): " << OutputFile_5D.timer.elapsed_s()
             << "\n";

        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputPacket5D_test(
                packet5V, "./test/inputPacket5D_test.txt", filterNum)) {
          cout << "Input Packet test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input packet test time(ns): "
             << OutputFile_5D.timer.elapsed_ns() << "\n";
        cout << "Input packet test time(s): " << OutputFile_5D.timer.elapsed_s()
             << "\n";
        break;
      case 'm':
        // Don't need argument
        OutputFile_5D.timer.timeReset();
        InputFile_5D.rule_5D_ip_merge(rule5V);
        InputFile_5D.packet_5D_ip_merge(packet5V);
        cout << "Merge ip time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Merge ip time(s): " << OutputFile_5D.timer.elapsed_s() << "\n";
        break;
      case 'n':
        // Don't need argument
        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputRule5D_merge_test(
                rule5V, "./test/inputRule5D_merge_test.txt")) {
          cout << "Input Rule merge test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input rule merge test time(ns): "
             << OutputFile_5D.timer.elapsed_ns() << "\n";
        cout << "Input rule merge test time(s): "
             << OutputFile_5D.timer.elapsed_s() << "\n";

        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputPacket5D_merge_test(
                packet5V, "./test/inputPacket5D_merge_test.txt", filterNum)) {
          cout << "Input Packet merge test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input packet merge test time(ns): "
             << OutputFile_5D.timer.elapsed_ns() << "\n";
        cout << "Input packet merge test time(s): "
             << OutputFile_5D.timer.elapsed_s() << "\n";
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
        cerr << "Usage: " << argv[0] << " -h   to get help"
             << "\n";

        return 1;
      default:
        break;
    }
  }

  return 0;
}
