/**
 * @file linearSearch.cpp
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
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>brutely linear search
 * </table>
 */

#include "linearSearch.hpp"

void LinearSearch::search(std::vector<Rule5D> &rule5V,
                          const std::vector<Packet5D> &packet5V) {
  const char *search_path = "./INFO/LinearSearch_FaultPacket5D_test.txt";
  std::ofstream outFile(search_path);
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
      outFile << "Source IP: " << unsigned(packet.ipS32) << "\n";
      outFile << "Destination IP: " << unsigned(packet.ipD32) << "\n";
      outFile << "Source Port: " << unsigned(packet.portS) << "\n";
      outFile << "Destination Port: " << unsigned(packet.portD) << "\n";
      outFile << "Protocol: 0x" << std::hex
              << static_cast<unsigned>(packet.protocol) << std::dec << "\n";
      outFile << "\n";
    }
    isBreak = false;
  }
  outFile << "LinearSearch.packetCounter = " << packetCounter << "\n";
  outFile.close();
  std::cout << "LinearSearch.packetCounter = " << packetCounter << "\n";
};
