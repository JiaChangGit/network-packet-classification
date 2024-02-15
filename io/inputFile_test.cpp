/**
 * @file inputFile_test.cpp
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
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>test loading rule-set and
 * loading trace-set
 * </table>
 */

#include "inputFile_test.hpp"

void InputFile5D_test::loadRule5D_test(const std::vector<Rule5D> &rule5V,
                                       const char *fileName) {
  std::ofstream outFile(fileName);
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file: " << fileName << "\n";
    exit(1);  // error
  }
  // Timer t_loadRule5D_test;
  // Write extracted data to the output file
  for (const auto &rule : rule5V) {
    outFile << "Priority: " << rule.pri << "\n";
    outFile << "Source IP: " << unsigned(rule.ipS[3]) << "."
            << unsigned(rule.ipS[2]) << "." << unsigned(rule.ipS[1]) << "."
            << unsigned(rule.ipS[0]) << "/" << unsigned(rule.ipSMask) << "\n";
    outFile << "Destination IP: " << unsigned(rule.ipD[3]) << "."
            << unsigned(rule.ipD[2]) << "." << unsigned(rule.ipD[1]) << "."
            << unsigned(rule.ipD[0]) << "/" << unsigned(rule.ipDMask) << "\n";
    outFile << "Source Port: " << unsigned(rule.portS[0]) << " : "
            << unsigned(rule.portS[1]) << "\n";
    outFile << "Destination Port: " << unsigned(rule.portD[0]) << " : "
            << unsigned(rule.portD[1]) << "\n";
    outFile << "Protocol: 0x" << std::hex << unsigned(rule.protocol[0])
            << " / 0x" << unsigned(rule.protocol[1]) << std::dec << "\n";
    outFile << "\n";
  }
  //   std::cout << "Time taken: " << t_loadRule5D_test.elapsed_ns() << " ns"
  //             << "\n";
  //   std::cout << "Time taken: " << t_loadRule5D_test.elapsed_s() << " s"
  //             << "\n";

  std::cout << "Leave inputRule_test"
            << "\n";
  outFile.close();
};

void InputFile5D_test::loadPacket5D_test(const std::vector<Packet5D> &packet5V,
                                         const char *fileName) {
  std::ofstream outFile(fileName);
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file: " << fileName << "\n";
    exit(1);  // error
  }
  // Timer t_loadPacket5D_test;

  // Write extracted data to the output file
  for (const auto &packet : packet5V) {
    outFile << "Source IP: " << unsigned(packet.ipS[3]) << "."
            << unsigned(packet.ipS[2]) << "." << unsigned(packet.ipS[1]) << "."
            << unsigned(packet.ipS[0]) << "\n";
    outFile << "Destination IP: " << unsigned(packet.ipD[3]) << "."
            << unsigned(packet.ipD[2]) << "." << unsigned(packet.ipD[1]) << "."
            << unsigned(packet.ipD[0]) << "\n";
    outFile << "Source Port: " << unsigned(packet.portS) << "\n";
    outFile << "Destination Port: " << unsigned(packet.portD) << "\n";
    outFile << "Protocol: 0x" << std::hex << unsigned(packet.protocol)
            << std::dec << "\n";
    outFile << "\n";
  }
  //   std::cout << "Time taken: " << t_loadPacket5D_test.elapsed_ns() << " ns"
  //             << "\n";
  //   std::cout << "Time taken: " << t_loadPacket5D_test.elapsed_s() << " s"
  //             << "\n";

  std::cout << "Leave inputPacket_test"
            << "\n";
  outFile.close();
};
void InputFile5D_test::loadRule5D_ipSD_test(const std::vector<Rule5D> &rule5V,
                                            const char *fileName) {
  std::ofstream outFile(fileName);
  if (!outFile.is_open()) {
    std::cerr << "Input Rule ipSD test ERROR: " << fileName << "\n";
    exit(1);  // error
  }
  // Write extracted data to the output file
  for (const auto &rule : rule5V) {
    outFile << "Priority: " << rule.pri << "\n";
    outFile << "Source IP: " << unsigned(rule.ipS32) << "/"
            << unsigned(rule.ipSMask) << "\n";
    outFile << "Destination IP: " << unsigned(rule.ipD32) << "/"
            << unsigned(rule.ipDMask) << "\n";
    outFile << "Source Port: " << unsigned(rule.portS[0]) << " : "
            << unsigned(rule.portS[1]) << "\n";
    outFile << "Destination Port: " << unsigned(rule.portD[0]) << " : "
            << unsigned(rule.portD[1]) << "\n";
    outFile << "Protocol: 0x" << std::hex << unsigned(rule.protocol[0])
            << " / 0x" << unsigned(rule.protocol[1]) << std::dec << "\n";
    outFile << "\n";
  }

  outFile.close();
};
void InputFile5D_test::loadPacket5D_ipSD_test(
    const std::vector<Packet5D> &packet5V, const char *fileName) {
  std::ofstream outFile(fileName);
  if (!outFile.is_open()) {
    std::cerr << "Input Packet ipSD test ERROR: " << fileName << "\n";
    exit(1);  // error
  }
  // Write extracted data to the output file
  for (const auto &packet : packet5V) {
    outFile << "Source IP: " << unsigned(packet.ipS32) << "\n";
    outFile << "Destination IP: " << unsigned(packet.ipD32) << "\n";
    outFile << "Source Port: " << unsigned(packet.portS) << "\n";
    outFile << "Destination Port: " << unsigned(packet.portD) << "\n";
    outFile << "Protocol: 0x" << std::hex << unsigned(packet.protocol)
            << std::dec << "\n";
    outFile << "\n";
  }

  outFile.close();
};
