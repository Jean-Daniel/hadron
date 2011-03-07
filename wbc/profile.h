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

#if defined(__MACH__)

#include <mach/mach.h>
#include <mach/mach_time.h>

SC_INLINE
WBHostTime WBHostTimeGetCurrent(void) { return mach_absolute_time(); }

SC_INLINE
WBHostTime WBNanoToHostTime(UInt64 nano) {
  return UnsignedWideToUInt64(NanosecondsToAbsolute(UInt64ToUnsignedWide(nano)));
}

SC_INLINE
UInt64 WBHostTimeToNano(WBHostTime delta) {
  // Convert to nanoseconds.
  return UnsignedWideToUInt64(AbsoluteToNanoseconds(UInt64ToUnsignedWide(delta)));
}

#elif defined(_WIN32)

static inline
WBHostTime WBHostTimeGetCurrent(void) {
  LARGE_INTEGER counter;
  counter.QuadPart = 0;
  QueryPerformanceCounter(&counter);
  return counter.QuadPart;
}

static inline
uint64_t WBHostTimeToNano(WBHostTime delta) {
  // Convert to nanoseconds.
  LARGE_INTEGER frequency;
  frequency.QuadPart = 0;
  QueryPerformanceFrequency(&frequency);
  return sullround((double)delta * 1e9 / frequency.QuadPart);
}

#endif

SC_INLINE
UInt64 WBHostTimeToMicro(WBHostTime delta) { return ullround((double)WBHostTimeToNano(delta) / 1e3); }

SC_INLINE
UInt32 WBHostTimeToMillis(WBHostTime delta) { return (UInt32)ulround((double)WBHostTimeToNano(delta) / 1e6); }

SC_INLINE
CFTimeInterval WBHostTimeToTimeInterval(WBHostTime delta) { return (CFTimeInterval)WBHostTimeToNano(delta) / 1e9; }

#endif /* __WBC_PROFILE_H__ */
