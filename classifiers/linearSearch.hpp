/**
 * @file LinearSearch.hpp
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
 * <tr><td>2024-02-11 <td>1.5     <td>jiachang     <td>brutely linear search
 * </table>
 */

#ifndef _CLASSIFIERS_LINEARSEARCH_HPP_
#define _CLASSIFIERS_LINEARSEARCH_HPP_

#include <fstream>

#include "../lib/basis.hpp"

class LinearSearch {
 public:
  LinearSearch() : memorySize(0), packetCounter(0){};
  void inline search(std::vector<Rule5D> &rule5V,
                     const std::vector<Packet5D> &packet5V) {
    std::ofstream outFile(LinearSearch_path);
    bool isBreak = false;
    for (const auto &packet : packet5V) {
      for (auto &rule : rule5V) {
        if (rule.isMatch(packet)) {
          ++packetCounter;
          isBreak = true;
          // std::cout << "match: " << rule.pri << "\n";
          break;
        }
      }
      if (!isBreak) {
        outFile << "Source IP: " << packet[0] << "\n";
        outFile << "Destination IP: " << packet[1] << "\n";
        outFile << "Source Port: " << packet[2] << "\n";
        outFile << "Destination Port: " << packet[3] << "\n";
        outFile << "Protocol: 0x" << std::hex << packet[4] << std::dec << "\n";
        outFile << "\n";
      }
      isBreak = false;
    }
    outFile << "LinearSearch.packetCounter = " << packetCounter << "\n";
    outFile.close();
    std::cout << "LinearSearch.packetCounter = " << packetCounter << "\n";
  };
  void inline search(std::vector<Rule5D> &rule5V, const Packet5D &packet) {
    std::ofstream outFile(LinearSearch_path);
    bool isBreak = false;

    for (auto &rule : rule5V) {
      if (rule.isMatch(packet)) {
        ++packetCounter;
        isBreak = true;
        // std::cout << "match: " << rule.pri << "\n";
        break;
      }
    }
    if (!isBreak) {
      outFile << "Source IP: " << packet[0] << "\n";
      outFile << "Destination IP: " << packet[1] << "\n";
      outFile << "Source Port: " << packet[2] << "\n";
      outFile << "Destination Port: " << packet[3] << "\n";
      outFile << "Protocol: 0x" << std::hex << packet[4] << std::dec << "\n";
      outFile << "\n";
    }
    isBreak = false;

    outFile << "LinearSearch.packetCounter = " << packetCounter << "\n";
    outFile.close();
    std::cout << "LinearSearch.packetCounter = " << packetCounter << "\n";
  };

 private:
  const char *LinearSearch_path = "./INFO/LinearSearch_FaultPacket5D_test.txt";
  unsigned long long memorySize;
  unsigned long long packetCounter;
};

#endif
