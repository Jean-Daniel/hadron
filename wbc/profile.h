/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Profiling and debugging tools
*/

#if !defined(__WBC_PROFILE_H__)
#define __WBC_PROFILE_H__ 1

#pragma mark Debugging & Profiling

#define WBWaitDebugger() raise(SIGSTOP)

#include <mach/mach.h>
#include <mach/mach_time.h>

typedef uint64_t WBHostTime;

WB_INLINE
WBHostTime WBHostTimeGetCurrent(void) { return mach_absolute_time(); }

WB_INLINE
WBHostTime WBNanoToHostTime(UInt64 nano) {
  return UnsignedWideToUInt64(NanosecondsToAbsolute(UInt64ToUnsignedWide(nano)));
}

WB_INLINE
UInt64 WBHostTimeToNano(WBHostTime delta) {
  // Convert to nanoseconds.
  return UnsignedWideToUInt64(AbsoluteToNanoseconds(UInt64ToUnsignedWide(delta)));
}

WB_INLINE
UInt64 WBHostTimeToMicro(WBHostTime delta) { return llround((double)WBHostTimeToNano(delta) / 1e3); }

WB_INLINE
UInt32 WBHostTimeToMillis(WBHostTime delta) { return (UInt32)lround((double)WBHostTimeToNano(delta) / 1e6); }

WB_INLINE
CFTimeInterval WBHostTimeToTimeInterval(WBHostTime delta) { return (CFTimeInterval)WBHostTimeToNano(delta) / 1e9; }

#endif /* __WBC_PROFILE_H__ */
