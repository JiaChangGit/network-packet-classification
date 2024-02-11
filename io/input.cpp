/**
 * @file input.cpp
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
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>load rule-set and trace-set
 * </table>
 */
/*
 * @title: input_v1.cpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#include "input.hpp"

void InputFile5D::loadRule5D(std::vector<Rule5D> &rule5V,
                             const char *fileName)
{
  FILE *fp = NULL;
  fp = fopen(fileName, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "error - can not open rules file\n");
    exit(1); // error
  }
  // Timer t_loadRule5D;
  unsigned int ipS_fscan[4];
  unsigned int ipSmask_fscan;
  unsigned int ipD_fscan[4];
  unsigned int ipDmask_fscan;
  unsigned int portS_fscan[2];
  unsigned int portD_fscan[2];
  unsigned int protocol[2];
  Rule5D r;
  while (fscanf(fp,
                "@%u.%u.%u.%u/%u\t%u.%u.%u.%u/%u\t%u : %u\t%u : "
                "%u\t%x/%x\t%*x/%*x\t\n",
                &ipS_fscan[3], &ipS_fscan[2], &ipS_fscan[1], &ipS_fscan[0],
                &ipSmask_fscan, &ipD_fscan[3], &ipD_fscan[2], &ipD_fscan[1],
                &ipD_fscan[0], &ipDmask_fscan, &portS_fscan[0], &portS_fscan[1],
                &portD_fscan[0], &portD_fscan[1], &protocol[0],
                &protocol[1]) != EOF)
  {
    r.pri++;
    r.protocol[0] = (uint8_t)protocol[0];
    r.protocol[1] = (uint8_t)protocol[1];
    r.ipSMask = (uint8_t)ipSmask_fscan;
    r.ipDMask = (uint8_t)ipDmask_fscan;

    for (int j = 0; j < 4; j++)
    {
      r.ipS[j] = (uint8_t)ipS_fscan[j];
      r.ipD[j] = (uint8_t)ipD_fscan[j];
    }
    r.portS[0] = (uint16_t)portS_fscan[0];
    r.portS[1] = (uint16_t)portS_fscan[1];
    r.portD[0] = (uint16_t)portD_fscan[0];
    r.portD[1] = (uint16_t)portD_fscan[1];
    rule5V.emplace_back(r);
  }
  // std::cout << "Time taken: " << t_loadRule5D.elapsed_ns() << " ns"
  //           << "\n";
  // std::cout << "Time taken: " << t_loadRule5D.elapsed_s() << " s"
  //           << "\n";
  std::cout << "Leave loadRule5D"
            << "\n";
  fclose(fp);
};

void InputFile5D::loadPacket5D(std::vector<Packet5D> &packet5V,
                               const char *fileName)
{
  FILE *fp = NULL;
  fp = fopen(fileName, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "error - can not open trace file\n");
    exit(1); // error
  }
  // Timer t_loadPacket5D;
  Packet5D p5D;
  unsigned int ip_src, ip_des;
  while (fscanf(fp, "%u\t%u\t%hu\t%hu\t%hhu\t%*u\t%*d\n", &ip_src, &ip_des,
                &p5D.portS, &p5D.portD, &p5D.protocol) != EOF)
  {
    memcpy(p5D.ipS, &ip_src, 4);
    memcpy(p5D.ipD, &ip_des, 4);

    packet5V.emplace_back(p5D);
  }
  // std::cout << "Time taken: " << t_loadPacket5D.elapsed_ns() << " ns"
  //           << "\n";
  // std::cout << "Time taken: " << t_loadPacket5D.elapsed_s() << " s"
  //           << "\n";
  std::cout << "Leave loadPacket5D"
            << "\n";
  fclose(fp);
};

// <Source Address>	<Destination Address>	<Source Port>	<Destination
// Port>	<Protocol>	<Filter Number>

// The Filter Number simply records the filter used to generate the header.
// This may NOT be the best-matching (or first-matching) filter for the packet
// header.
