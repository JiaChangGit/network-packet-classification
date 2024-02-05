/**
 * @file inputFile_test.cpp
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
 * <tr><td>2024-02-03 <td>1.1     <td>jiachang     <td>test loading rule-set and loading trace-set
 * </table>
 */

#include "inputFile_test.hpp"

bool InputFile5D_test::loadRule5D_test(const std::vector<Rule5D> &rule5V,
                                       const char *fileName)
{
        std::ofstream outFile(fileName);
        if (!outFile.is_open())
        {
                std::cerr << "Error opening output file: " << fileName << std::endl;
                return true; // error
        }
        // Timer t_loadRule5D_test;
        // Write extracted data to the output file
        for (const auto &rule : rule5V)
        {
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
        //   std::cout << "Time taken: " << t_loadRule5D_test.elapsed_ns() << " ns"
        //             << "\n";
        //   std::cout << "Time taken: " << t_loadRule5D_test.elapsed_s() << " s"
        //             << "\n";

        std::cout << "Leave inputRule_test"
                  << "\n";
        outFile.close();

        return false; // argv correct
};

bool InputFile5D_test::loadPacket5D_test(const std::vector<Packet5D> &packet5V,
                                         const char *fileName)
{
        std::ofstream outFile(fileName);
        if (!outFile.is_open())
        {
                std::cerr << "Error opening output file: " << fileName << std::endl;
                return true; // error
        }
        // Timer t_loadPacket5D_test;

        // Write extracted data to the output file
        for (const auto &packet : packet5V)
        {
                outFile << "Source IP: " << unsigned(packet.ipS[0]) << "."
                        << unsigned(packet.ipS[1]) << "." << unsigned(packet.ipS[2]) << "."
                        << unsigned(packet.ipS[3]) << "\n";
                outFile << "Destination IP: " << unsigned(packet.ipD[0]) << "."
                        << unsigned(packet.ipD[1]) << "." << unsigned(packet.ipD[2]) << "."
                        << unsigned(packet.ipD[3]) << "\n";
                outFile << "Source Port: " << unsigned(packet.portS) << "\n";
                outFile << "Destination Port: " << unsigned(packet.portD) << "\n";
                outFile << "Protocol: 0x" << std::hex
                        << static_cast<unsigned>(packet.protocol) << std::dec << "\n";
                outFile << "\n";
        }
        //   std::cout << "Time taken: " << t_loadPacket5D_test.elapsed_ns() << " ns"
        //             << "\n";
        //   std::cout << "Time taken: " << t_loadPacket5D_test.elapsed_s() << " s"
        //             << "\n";

        std::cout << "Leave inputPacket_test"
                  << "\n";
        outFile.close();

        return false; // argv correct
};
bool InputFile5D_test::loadRule5D_ip_merge_test(const std::vector<Rule5D> &rule5V, const char *fileName)
{
        std::ofstream outFile(fileName);
        if (!outFile.is_open())
        {
                std::cerr << "Input Rule merge test ERROR: " << fileName << "\n";
                return false; // error
        }
        // Write extracted data to the output file
        for (const auto &rule : rule5V)
        {
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

        outFile.close();
        return true; // argv correct
};
bool InputFile5D_test::loadPacket5D_ip_merge_test(const std::vector<Packet5D> &packet5V, const char *fileName)
{
        std::ofstream outFile(fileName);
        if (!outFile.is_open())
        {
                std::cerr << "Input Packet merge test ERROR: " << fileName << "\n";
                return false; // error
        }
        // Write extracted data to the output file
        for (const auto &packet : packet5V)
        {
                outFile << "Source IP: " << unsigned(packet.ipS32) << "\n";
                outFile << "Destination IP: " << unsigned(packet.ipD32) << "\n";
                outFile << "Source Port: " << unsigned(packet.portS) << "\n";
                outFile << "Destination Port: " << unsigned(packet.portD) << "\n";
                outFile << "Protocol: 0x" << std::hex
                        << static_cast<unsigned>(packet.protocol) << std::dec << "\n";
                outFile << "\n";
        }

        outFile.close();
        return true; // argv correct
};
