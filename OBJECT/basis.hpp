/*
 * @title: basis.hpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-09
 */

#ifndef __OBJECT_BASIS_HPP__
#define __OBJECT_BASIS_HPP__
#include <getopt.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

class Rule_5D {
 public:
  unsigned int pri = 0;
  union {
    uint8_t ipS[4];
    uint32_t ipS32;
  };
  union {
    uint8_t ipD[4];
    uint32_t ipD32;
  };
  uint16_t portS[2];
  uint16_t portD[2];
  uint8_t ipSMask;
  uint8_t ipDMask;
  uint8_t protocol[2];

  void ip_merge();
};

class Packet_5D {
 public:
  uint16_t portS;
  uint16_t portD;
  union {
    uint8_t ipS[4];
    uint32_t ipS32;
  };
  uint8_t protocol;
  union {
    uint8_t ipD[4];
    uint32_t ipD32;
  };

  void ip_merge();
};

class Timer {
 private:
  // Type aliases to make accessing nested type easier
  using Clock = std::chrono::steady_clock;
  using Second = std::chrono::duration<double, std::ratio<1> >;

  std::chrono::time_point<Clock> m_beg{Clock::now()};

 public:
  void timeReset();
  double elapsed_s() const;
  unsigned long long elapsed_ns() const;
};

// https://www.learncpp.com/cpp-tutorial/timing-your-code/
// Timer using ex:
// int main()
// {
//     std::array<int, g_arrayElements> array;
//     std::iota(array.rbegin(), array.rend(), 1);
//     Timer t;
//     sortArray(array);
//     std::cout << "Time taken: " << t.elapsed_s() << " seconds\n";
//     return 0;
// }

uint64_t inline GetCPUCycle() {
#ifdef __x86_64__
  unsigned int lo, hi;
  // __asm__ 指示編譯器在此插入彙編語句, 聲明一個內聯彙編表達式
  // __volatile__ 嚴禁將此處的彙編語句與其它的語句重組合優化
  // memory
  // gcc編譯器假設RAM所有記憶體單元均被彙編指令修改，這樣cpu中的registers和cache中已快取的記憶體單元中的數據將作廢,
  // cpu將不得不在需要的時候重新讀取記憶體中的數據 lfence
  // 在lfence指令前的讀操作當必須在lfence指令后的讀操作前完成
  __asm__ __volatile__("lfence" : : : "memory");  // 記憶體屏障
  // rdtsc: ReaD TimeStamp Counter, it reads a 64-bit counter that counts up at
  // every clock cycle of your processor.
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
#elif __aarch64__
  uint64_t v = 0;
  //  Instruction Synchronization Barrier (ISB) flushes the pipeline in the
  //  processor, so that all instructions following the ISB are fetched from
  //  cache or memory, after the ISB has been completed.
  asm volatile("isb" : : : "memory");
  asm volatile(
      "mrs %0, cntvct_el0"
      : "=r"(v));  // 虛擬計時器計數暫存器 CNTPCT_EL0物理計時器計數暫存器
  // asm volatile("mrs %0, pmccntr_el0" : "=r" (v)); // Performance Monitors
  // Cycle Count Register
  return v;
#else
  printf("unknown arch\n");
  return 0;
#endif
}

struct ACL_rules {
  int size;
  int capacity;
  Rule_5D* list;
  ACL_rules() : size(0), capacity(0), list(nullptr) {}
};
#endif
