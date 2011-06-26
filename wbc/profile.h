/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Profiling and debugging tools
*/

#if !defined(__WBC_PROFILE_H__)
#define __WBC_PROFILE_H__ 1

// MARK: Debugging & Profiling
#if defined(_MSC_VER)
  #define WBWaitDebugger() __debugbreak()
#elif defined(__x86_64__) || defined(__i386__)
  #define WBWaitDebugger() __asm("int3")
#elif (__ppc__) || defined(__arm__)
  #define WBWaitDebugger() __asm("trap") // TODO: check if it works
#endif
// TODO: maybe fallback to pthread_kill(pthread_self(), SIG_INT) for other archs

typedef uint64_t WBHostTime;

#if defined(__APPLE__)
  #include <mach/mach.h>
  #include <mach/mach_time.h>
#endif

SC_INLINE
WBHostTime WBHostTimeGetCurrent(void) {
#if defined(__APPLE__)
  return mach_absolute_time();
#elif defined(_WIN32)
  LARGE_INTEGER counter;
  counter.QuadPart = 0;
  QueryPerformanceCounter(&counter);
  return counter.QuadPart;
#elif defined(_POSIX_TIMERS)
  struct timespec ticks;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ticks);
  return (WBHostTime)ticks.tv_sec * 1e9 + ticks.tv_nsec;
#else
  struct timeval ticks;
  gettimeofday(&ticks, NULL);
  return (WBHostTime)ticks.tv_sec * 1e6 + ticks.tv_usec;
#endif
}

static inline
double _WBHostTimeToNanoFactor(void) {
#if defined(__APPLE__)
  static double sFactor = -1;
  if (sFactor < 0) {
    mach_timebase_info_data_t sTimebaseInfo = {0, 0};
    mach_timebase_info(&sTimebaseInfo);
    sFactor = ((double)sTimebaseInfo.numer / (double)sTimebaseInfo.denom);
  }
  return sFactor;
#elif defined(_WIN32)
  static double sFactor = -1;
  if (sFactor < 0) {
    LARGE_INTEGER frequency;
    frequency.QuadPart = 0;
    QueryPerformanceFrequency(&frequency);
    sFactor = 1e9 / frequency.QuadPart;
  }
  return sFactor;
#elif defined(_POSIX_TIMERS)
  return 1;
#else
  return 1e3;
#endif
}

SC_INLINE
uint64_t WBHostTimeToNano(WBHostTime delta) {
  return sullround(_WBHostTimeToNanoFactor() * delta);
}

SC_INLINE
WBHostTime WBHostTimeFromNano(uint64_t nano) {
  return sullround(nano / _WBHostTimeToNanoFactor());
}

SC_INLINE
uint64_t WBHostTimeToMicro(WBHostTime delta) { return sullround(_WBHostTimeToNanoFactor() * delta / 1e3); }

SC_INLINE
uint32_t WBHostTimeToMillis(WBHostTime delta) { return (uint32_t)ulround(_WBHostTimeToNanoFactor() * delta / 1e6); }

SC_INLINE
CFTimeInterval WBHostTimeToTimeInterval(WBHostTime delta) { return _WBHostTimeToNanoFactor() * delta / 1e9; }

#endif /* __WBC_PROFILE_H__ */
