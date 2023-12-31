/*
 * @title: basis.cpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#include "basis.hpp"

void Rule_5D::ip_merge() {
  this->ipS32 = ((uint32_t)this->ipS[0] << 24) |
                ((uint32_t)this->ipS[1] << 16) | ((uint32_t)this->ipS[2] << 8) |
                ((uint32_t)this->ipS[3]);
  this->ipD32 = ((uint32_t)this->ipD[0] << 24) |
                ((uint32_t)this->ipD[1] << 16) | ((uint32_t)this->ipD[2] << 8) |
                ((uint32_t)this->ipD[3]);
};
void Packet_5D::ip_merge() {
  this->ipS32 = ((uint32_t)this->ipS[0] << 24) |
                ((uint32_t)this->ipS[1] << 16) | ((uint32_t)this->ipS[2] << 8) |
                ((uint32_t)this->ipS[3]);
  this->ipD32 = ((uint32_t)this->ipD[0] << 24) |
                ((uint32_t)this->ipD[1] << 16) | ((uint32_t)this->ipD[2] << 8) |
                ((uint32_t)this->ipD[3]);
};

void Timer::timeReset() { m_beg = Clock::now(); };

double Timer::elapsed_s() const {
  return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
};
unsigned long long Timer::elapsed_ns() const {
  return std::chrono::milliseconds((Clock::now() - m_beg).count()).count();
};
