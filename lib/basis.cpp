/**
 * @file basis.cpp
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
 * <tr><td>2024-02-11 <td>1.4     <td>jiachang     <td>basic data structures
 * </table>
 */

#include "basis.hpp"

void Packet5D::eightBitsGroup_ipSD() {
  this->ipS32 = ((uint32_t)this->ipS[0] << 24) |
                ((uint32_t)this->ipS[1] << 16) | ((uint32_t)this->ipS[2] << 8) |
                ((uint32_t)this->ipS[3]);
  this->ipD32 = ((uint32_t)this->ipD[0] << 24) |
                ((uint32_t)this->ipD[1] << 16) | ((uint32_t)this->ipD[2] << 8) |
                ((uint32_t)this->ipD[3]);
};

void Rule5D::eightBitsGroup_ipSD() {
  this->ipS32 = ((uint32_t)this->ipS[0] << 24) |
                ((uint32_t)this->ipS[1] << 16) | ((uint32_t)this->ipS[2] << 8) |
                ((uint32_t)this->ipS[3]);
  this->ipD32 = ((uint32_t)this->ipD[0] << 24) |
                ((uint32_t)this->ipD[1] << 16) | ((uint32_t)this->ipD[2] << 8) |
                ((uint32_t)this->ipD[3]);
};

bool Rule5D::isMatch(const Packet5D &p5D) {
  uint8_t ipNotCare = (32 - ipSMask);
  if (ipNotCare != 32) {
    if ((ipS32 >> ipNotCare) != (p5D.ipS32 >> ipNotCare)) {
      return false;
    }
    ipNotCare = (32 - ipDMask);
  } else if (ipNotCare != 32) {
    if ((ipD32 >> ipNotCare) != (p5D.ipD32 >> ipNotCare)) {
      return false;
    }
  } else if ((portD[0] > p5D.portD) || (portD[1] < p5D.portD)) {
    return false;
  } else if ((portS[0] > p5D.portS) || (portS[1] < p5D.portS)) {
    return false;
  } else if (((protocol[0] & protocol[1]) != p5D.protocol) &&
             (protocol[1] != 0x00)) {
    return false;
  }
  return true;
};

void Timer::timeReset() { m_beg = Clock::now(); };

double Timer::elapsed_s() const {
  return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
};
unsigned long long Timer::elapsed_ns() const {
  return std::chrono::milliseconds((Clock::now() - m_beg).count()).count();
};
