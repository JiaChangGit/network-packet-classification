/*
 * @title: input_v1.cpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#include "input_v1.hpp"
bool InputFile5D::inputRule5D(std::vector<Rule_5D>& ruleV,
                              const char* file_name) {
  FILE* fp = NULL;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "error - can not open rules file\n");
    return true;  // error
  }
  // Dialog t_inputRule5D;
  unsigned int ipS_fscan[5];
  unsigned int ipD_fscan[5];
  unsigned int portS_fscan[2];
  unsigned int portD_fscan[2];
  unsigned int protocol[2];
  Rule_5D r;
  while (fscanf(fp,
                "@%u.%u.%u.%u/%u\t%u.%u.%u.%u/%u\t%u : %u\t%u : "
                "%u\t%x/%x\t%*x/%*x\t\n",
                &ipS_fscan[0], &ipS_fscan[1], &ipS_fscan[2], &ipS_fscan[3],
                &ipS_fscan[4], &ipD_fscan[0], &ipD_fscan[1], &ipD_fscan[2],
                &ipD_fscan[3], &ipD_fscan[4], &portS_fscan[0], &portS_fscan[1],
                &portD_fscan[0], &portD_fscan[1], &protocol[0],
                &protocol[1]) != EOF) {
    r.pri++;
    r.protocol[0] = (uint8_t)protocol[0];
    r.protocol[1] = (uint8_t)protocol[1];
    r.ipSMask = (uint8_t)ipS_fscan[4];
    r.ipDMask = (uint8_t)ipD_fscan[4];

    for (int j = 0; j < 4; j++) {
      r.ipS[j] = (uint8_t)ipS_fscan[j];
      r.ipD[j] = (uint8_t)ipD_fscan[j];
    }
    r.portS[0] = (uint16_t)portS_fscan[0];
    r.portS[1] = (uint16_t)portS_fscan[1];
    r.portD[0] = (uint16_t)portD_fscan[0];
    r.portD[1] = (uint16_t)portD_fscan[1];
    ruleV.emplace_back(r);
  }
  // std::cout << "Time taken: " << t_inputRule5D.elapsed_ns() << " ns"
  //           << "\n";
  // std::cout << "Time taken: " << t_inputRule5D.elapsed_s() << " s"
  //           << "\n";
  std::cout << "Leave inputRule5D"
            << "\n";
  fclose(fp);

  return false;  // argv correct
};

bool InputFile5D::inputPacket5D(std::vector<Packet_5D>& packetV,
                                const char* file_name,
                                std::vector<int>& check_list) {
  FILE* fp = NULL;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "error - can not open trace file\n");
    return true;  // error
  }
  // Dialog t_inputPacket5D;
  Packet_5D p;
  unsigned int ip_src, ip_des;
  int result;
  while (fscanf(fp, "%u\t%u\t%hu\t%hu\t%u\t%*u\t%d\n", &ip_src, &ip_des,
                &p.portS, &p.portD, &p.protocol, &result) != EOF) {
    memcpy(p.ipS, &ip_src, 4);
    memcpy(p.ipD, &ip_des, 4);
    check_list.emplace_back(result);
    packetV.emplace_back(p);
  }
  // std::cout << "Time taken: " << t_inputPacket5D.elapsed_ns() << " ns"
  //           << "\n";
  // std::cout << "Time taken: " << t_inputPacket5D.elapsed_s() << " s"
  //           << "\n";
  std::cout << "Leave inputPacket5D"
            << "\n";
  fclose(fp);

  return false;  // argv correct
};

void InputFile5D::rule_5D_ip_merge(std::vector<Rule_5D>& ruleV) {
  for (auto& rule : ruleV) {
    rule.ip_merge();
  }
};
void InputFile5D::packet_5D_ip_merge(std::vector<Packet_5D>& packetV) {
  for (auto& packet : packetV) {
    packet.ip_merge();
  }
};

// <Source Address>	<Destination Address>	<Source Port>	<Destination
// Port>	<Protocol>	<Filter Number>

// The Filter Number simply records the filter used to generate the header.
// This may NOT be the best-matching (or first-matching) filter for the packet
// header.
