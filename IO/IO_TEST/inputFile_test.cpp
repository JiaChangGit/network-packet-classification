/*
 * @title: inputRule_test.cpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#include "inputFile_test.hpp"

bool InputFile5D_test::inputRule5D_test(std::vector<Rule_5D>& ruleV,
                                        const char* file_name) {
  std::ofstream outFile(file_name);
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file: " << file_name << std::endl;
    return true;  // error
  }
  // Timer t_inputRule5D_test;
  // Write extracted data to the output file
  for (const auto& rule : ruleV) {
    outFile << "Priority: " << rule.pri << "\n";
    outFile << "Source IP: " << unsigned(rule.ipS[0]) << "."
            << unsigned(rule.ipS[1]) << "." << unsigned(rule.ipS[2]) << "."
            << unsigned(rule.ipS[3]) << "/" << unsigned(rule.ipSMask) << "\n";
    outFile << "Destination IP: " << unsigned(rule.ipD[0]) << "."
            << unsigned(rule.ipD[1]) << "." << unsigned(rule.ipD[2]) << "."
            << unsigned(rule.ipD[3]) << "/" << unsigned(rule.ipDMask) << "\n";
    outFile << "Source Port: " << unsigned(rule.portS[0]) << " : "
            << unsigned(rule.portS[1]) << "\n";
    outFile << "Destination Port: " << unsigned(rule.portD[0]) << " : "
            << unsigned(rule.portD[1]) << "\n";
    outFile << "Protocol: 0x" << std::hex
            << static_cast<unsigned>(rule.protocol[0]) << " / 0x"
            << static_cast<unsigned>(rule.protocol[1]) << std::dec << "\n";
    outFile << "\n";
  }
  //   std::cout << "Time taken: " << t_inputRule5D_test.elapsed_ns() << " ns"
  //             << "\n";
  //   std::cout << "Time taken: " << t_inputRule5D_test.elapsed_s() << " s"
  //             << "\n";

  std::cout << "Leave inputRule_test"
            << "\n";
  outFile.close();

  return false;  // argv correct
};

bool InputFile5D_test::inputPacket5D_test(std::vector<Packet_5D>& packetV,
                                          const char* file_name,
                                          std::vector<int>& check_list) {
  std::ofstream outFile(file_name);
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file: " << file_name << std::endl;
    return true;  // error
  }
  // Timer t_inputPacket5D_test;
  int i = 0;
  // Write extracted data to the output file
  for (const auto& packet : packetV) {
    outFile << "Check list: " << check_list[i++] << "\n";
    outFile << "Source IP: " << unsigned(packet.ipS[0]) << "."
            << unsigned(packet.ipS[1]) << "." << unsigned(packet.ipS[2]) << "."
            << unsigned(packet.ipS[3]) << "\n";
    outFile << "Destination IP: " << unsigned(packet.ipD[0]) << "."
            << unsigned(packet.ipD[1]) << "." << unsigned(packet.ipD[2]) << "."
            << unsigned(packet.ipD[3]) << "\n";
    outFile << "Source Port: " << unsigned(packet.portS) << "\n";
    outFile << "Destination Port: " << unsigned(packet.portD) << "\n";
    outFile << "Protocol: 0x" << std::hex
            << static_cast<unsigned>(packet.protocol) << "\n";
    outFile << "\n";
  }
  //   std::cout << "Time taken: " << t_inputPacket5D_test.elapsed_ns() << " ns"
  //             << "\n";
  //   std::cout << "Time taken: " << t_inputPacket5D_test.elapsed_s() << " s"
  //             << "\n";

  std::cout << "Leave inputPacket_test"
            << "\n";
  outFile.close();

  return false;  // argv correct
};

bool InputFile5D_test::inputRule5D_merge_test(std::vector<Rule_5D>& ruleV,
                                              const char* file_name) {
  std::ofstream outFile(file_name);
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file: " << file_name << std::endl;
    return true;  // error
  }
  // Timer inputRule5D_merge_test;
  // Write extracted data to the output file
  for (const auto& rule : ruleV) {
    outFile << "Priority: " << rule.pri << "\n";
    outFile << "Source IP: " << unsigned(rule.ipS32) << "/"
            << unsigned(rule.ipSMask) << "\n";
    outFile << "Destination IP: " << unsigned(rule.ipD32) << "/"
            << unsigned(rule.ipDMask) << "\n";
    outFile << "Source Port: " << unsigned(rule.portS[0]) << " : "
            << unsigned(rule.portS[1]) << "\n";
    outFile << "Destination Port: " << unsigned(rule.portD[0]) << " : "
            << unsigned(rule.portD[1]) << "\n";
    outFile << "Protocol: 0x" << std::hex
            << static_cast<unsigned>(rule.protocol[0]) << " / 0x"
            << static_cast<unsigned>(rule.protocol[1]) << std::dec << "\n";
    outFile << "\n";
  }
  //   std::cout << "Time taken: " << inputRule5D_merge_test.elapsed_ns() << "
  //   ns"
  //             << "\n";
  //   std::cout << "Time taken: " << inputRule5D_merge_test.elapsed_s() << " s"
  //             << "\n";

  std::cout << "Leave inputRule5D_merge_test"
            << "\n";
  outFile.close();

  return false;  // argv correct
};

bool InputFile5D_test::inputPacket5D_merge_test(std::vector<Packet_5D>& packetV,
                                                const char* file_name,
                                                std::vector<int>& check_list) {
  std::ofstream outFile(file_name);
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file: " << file_name << std::endl;
    return true;  // error
  }
  // Timer inputPacket5D_merge_test;
  int i = 0;
  // Write extracted data to the output file
  for (const auto& packet : packetV) {
    outFile << "Check list: " << check_list[i++] << "\n";
    outFile << "Source IP: " << unsigned(packet.ipS32) << "\n";
    outFile << "Destination IP: " << unsigned(packet.ipD32) << "\n";
    outFile << "Source Port: " << unsigned(packet.portS) << "\n";
    outFile << "Destination Port: " << unsigned(packet.portD) << "\n";
    outFile << "Protocol: 0x" << std::hex
            << static_cast<unsigned>(packet.protocol) << "\n";
    outFile << "\n";
  }
  //   std::cout << "Time taken: " << inputPacket5D_merge_test.elapsed_ns() << "
  //   ns"
  //             << "\n";
  //   std::cout << "Time taken: " << inputPacket5D_merge_test.elapsed_s() << "
  //   s"
  //             << "\n";

  std::cout << "Leave inputPacket5D_merge_test"
            << "\n";
  outFile.close();

  return false;  // argv correct
};
