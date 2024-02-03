/**
 * @file basis.cpp
 * @brief
 * @author jiachang (jiachanggit@gmail.com)
 * @version 1.0
 * @date 2024-02-03
 *
 * @copyright Copyright (c) 2024  JIA-CHANG
 *
 * @par dialog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-02-03 <td>1.0     <td>jiachang     <td>basic data structures
 * </table>
 */

#include "basis.hpp"

void Rule5D::ip_merge()
{
  this->ipS32 = ((uint32_t)this->ipS[0] << 24) |
                ((uint32_t)this->ipS[1] << 16) | ((uint32_t)this->ipS[2] << 8) |
                ((uint32_t)this->ipS[3]);
  this->ipD32 = ((uint32_t)this->ipD[0] << 24) |
                ((uint32_t)this->ipD[1] << 16) | ((uint32_t)this->ipD[2] << 8) |
                ((uint32_t)this->ipD[3]);
};
void Packet5D::ip_merge()
{
  this->ipS32 = ((uint32_t)this->ipS[0] << 24) |
                ((uint32_t)this->ipS[1] << 16) | ((uint32_t)this->ipS[2] << 8) |
                ((uint32_t)this->ipS[3]);
  this->ipD32 = ((uint32_t)this->ipD[0] << 24) |
                ((uint32_t)this->ipD[1] << 16) | ((uint32_t)this->ipD[2] << 8) |
                ((uint32_t)this->ipD[3]);
};

void Timer::timeReset() { m_beg = Clock::now(); };

double Timer::elapsed_s() const
{
  return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
};
unsigned long long Timer::elapsed_ns() const
{
  return std::chrono::milliseconds((Clock::now() - m_beg).count()).count();
};

void reverseMemcpy(void *dest, const void *src, size_t size)
{
  const char *srcBytes = static_cast<const char *>(src);
  char *destBytes = static_cast<char *>(dest);

  for (size_t i = 0; i < size; ++i)
  {
    destBytes[i] = srcBytes[size - 1 - i];
  }
};
