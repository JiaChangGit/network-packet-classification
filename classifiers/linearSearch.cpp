/**
 * @file linearSearch.cpp
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

#include "linearSearch.hpp"

void LinearSearch::search(std::vector<Rule5D> &rule5V,
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
