/**
 * @file main.cpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.1
 * @date 2024-02-03
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-03 <td>1.1     <td>jiachang     <td>main
 * </table>
 */

#include "inputFile_test.hpp"
#include "input.hpp"
#include "linearSearch.hpp"
#include <getopt.h>
#include <fstream>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::ofstream;
using std::vector;

int main(int argc, char *argv[])
{
     vector<Rule5D> rule5V;
     vector<Packet5D> packet5V;
     InputFile5D inputFile5D;
     InputFile5D_test inputFile5D_test;
     Timer timer;

     static struct option long_options[] = {
         {"ruleset", required_argument, NULL, 'r'},
         {"trace", required_argument, NULL, 'p'},
         {"test", no_argument, NULL, 't'},
         {"help", no_argument, NULL, 'h'},
         {0, 0, 0, 0} // End of options marker
     };
     int option;
     while ((option = getopt_long(argc, argv, "r:p:t::h::", long_options,
                                  nullptr)) != -1)
     {
          switch (option)
          {
          case 'r':
               cout << "Read ruleset:  " << optarg << "\n";
               timer.timeReset();
               if (inputFile5D.loadRule5D(rule5V, optarg))
               {
                    cout << "Read ruleset ERROR!!\n";
                    return -1;
               }
               cout << "Read ruleset time(ns): " << timer.elapsed_ns()
                    << "\n";
               cout << "Read ruleset time(s): " << timer.elapsed_s()
                    << "\n";
               break;
          case 'p':
               cout << "Rread trace: " << optarg << "\n";
               timer.timeReset();
               if (inputFile5D.loadPacket5D(packet5V, optarg))
               {
                    cout << "Read trace ERROR!!\n";
                    return -1;
               }
               cout << "Read trace time(ns): " << timer.elapsed_ns()
                    << "\n";
               cout << "Read trace time(s): " << timer.elapsed_s()
                    << "\n";
               break;
          case 't':
               // Don't need argument
               timer.timeReset();
               if (inputFile5D_test.loadRule5D_test(rule5V,
                                                    "./INFO/loadRule5D_test.txt"))
               {
                    cout << "Input Rule test ERROR!!\n";
                    return -1;
               }
               cout << "Input rule test time(ns): " << timer.elapsed_ns()
                    << "\n";
               cout << "Input rule test time(s): " << timer.elapsed_s()
                    << "\n";

               timer.timeReset();
               if (inputFile5D_test.loadPacket5D_test(
                       packet5V, "./INFO/loadPacket5D_test.txt"))
               {
                    cout << "Input Packet test ERROR!!\n";
                    return -1;
               }
               cout << "Input packet test time(ns): "
                    << timer.elapsed_ns() << "\n";
               cout << "Input packet test time(s): " << timer.elapsed_s()
                    << "\n";
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

     //// === ip_merge === ////
     timer.timeReset();
     for (auto &rule : rule5V)
     {
          rule.ip_merge();
     }
     for (auto &packet : packet5V)
     {
          packet.ip_merge();
     }
     cout << "Merge ip time(ns): " << timer.elapsed_ns() << "\n";
     cout << "Merge ip time(s): " << timer.elapsed_s() << "\n";
     inputFile5D_test.loadRule5D_ip_merge_test(rule5V, "./INFO/loadRule5D_merge_test.txt");
     inputFile5D_test.loadPacket5D_ip_merge_test(packet5V, "./INFO/loadPacket5D_merge_test.txt");
     //// === ip_merge === ////

     //// === LinearSearch === ////
     LinearSearch linearSearch;
     int packetNum = packet5V.size();
     timer.timeReset();
     linearSearch.search(rule5V, packet5V);
     cout << "LinearSearch time avg (ns): " << (timer.elapsed_ns() / packetNum) << "\n";
     cout << "LinearSearch time avg (s): " << (timer.elapsed_s() / packetNum) << "\n";
     //// === LinearSearch === ////
     return 0;
}
