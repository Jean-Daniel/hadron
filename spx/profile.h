/*
 *  profile.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Profiling and debugging utilities
*/

// MARK: Debugging & Profiling
#if defined(_MSC_VER) || __has_builtin(__debugbreak)
  #define SPXWaitDebugger() __debugbreak()
#elif defined(__x86_64__) || defined(__i386__)
  #define SPXWaitDebugger() __asm("int3")
#elif (__ppc__) || defined(__arm__)
  #define SPXWaitDebugger() __asm("trap") // TODO: check if it works
#endif
// TODO: maybe fallback to pthread_kill(pthread_self(), SIG_INT) for other archs

typedef uint64_t SPXHostTime;

#if defined(__APPLE__)
  #include <mach/mach.h>
  #include <mach/mach_time.h>
#endif

SPX_INLINE
SPXHostTime SPXHostTimeGetCurrent(void) {
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
  return (SPXHostTime)ticks.tv_sec * 1e9 + ticks.tv_nsec;
#else
  struct timeval ticks;
  gettimeofday(&ticks, NULL);
  return (SPXHostTime)ticks.tv_sec * 1e6 + ticks.tv_usec;
#endif
}

static inline
double _SPXHostTimeToNanoFactor(void) {
#if defined(__APPLE__)
  static double sFactor = -1;
  if (sFactor < 0) {
    mach_timebase_info_data_t sTimebaseInfo = {};
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

SPX_INLINE
uint64_t SPXHostTimeToNano(SPXHostTime delta) {
  return sullround(_SPXHostTimeToNanoFactor() * delta);
}

SPX_INLINE
SPXHostTime SPXHostTimeFromNano(uint64_t nano) {
  return sullround(nano / _SPXHostTimeToNanoFactor());
}

SPX_INLINE
uint64_t SPXHostTimeToMicro(SPXHostTime delta) { return sullround(_SPXHostTimeToNanoFactor() * delta / 1e3); }

SPX_INLINE
uint32_t SPXHostTimeToMillis(SPXHostTime delta) { return (uint32_t)ulround(_SPXHostTimeToNanoFactor() * delta / 1e6); }

SPX_INLINE
CFTimeInterval SPXHostTimeToTimeInterval(SPXHostTime delta) { return _SPXHostTimeToNanoFactor() * delta / 1e9; }
