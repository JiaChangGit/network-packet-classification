/*
 * @title: basis.cpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#include "basis.hpp"
uint64_t Dialog::getMemSize() { return this->memSize; };
void Dialog::memReset() { this->memSize = 0; };
void Dialog::timeReset() { m_beg = Clock::now(); };

double Dialog::elapsed_s() const {
  return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
};
unsigned long long Dialog::elapsed_ns() const {
  return std::chrono::milliseconds((Clock::now() - m_beg).count()).count();
};
