/**
 * @file inputFile_test.cpp
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
 * <tr><td>2024-02-11 <td>1.5     <td>jiachang     <td>test loading rule-set and
 * loading trace-set
 * </table>
 */

#include "inputFile_test.hpp"

void InputFile5D_test::loadRule5D_test(const std::vector<Rule5D>& rule5V,
                                       const char* fileName) {
  std::ofstream outFile(fileName);
  if (!outFile.is_open()) {
    std::cerr << "Failed to open " << fileName << " for writing"
              << "\n";
    return;
  }

  for (const auto& rule : rule5V) {
    outFile << "priority: " << rule.priority << "\n";
    outFile << "prefix_length: ";
    for (const auto& length : rule.prefix_length) {
      outFile << length << " ";
    }
    outFile << "\n";
    outFile << "range: ";
    for (const auto& r : rule.range) {
      outFile << "[" << r[0] << ", " << r[1] << "] ";
    }
    outFile << "\n\n";
  }

  outFile.close();
}

void InputFile5D_test::loadPacket5D_test(const std::vector<Packet5D>& packet5V,
                                         const char* fileName) {
  std::ofstream outFile(fileName);
  if (!outFile.is_open()) {
    std::cerr << "Failed to open " << fileName << " for writing"
              << "\n";
    return;
  }
  outFile << "src ip: \tdst ip: \tsrc port: \tdst port: \tprotocol: \n";
  for (const auto& packet : packet5V) {
    for (const auto& val : packet) {
      outFile << val << " ";
    }
    outFile << "\n";
  }

  outFile.close();
}
