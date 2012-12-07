/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Visibility macros + basics functions
*/

#if !defined(__WBC_CORE_H__)
#define __WBC_CORE_H__ 1

/* We want to be able to use std C macros in C++ */
#if defined(__cplusplus) && !defined(__STDC_LIMIT_MACROS)
  #define __STDC_LIMIT_MACROS 1
#endif

/* Required to use some advanced feature (program_invocation_short_name) */
#if defined(__linux__) && !defined(_GNU_SOURCE)
  #define _GNU_SOURCE 1
#endif

// MARK: Common definitions
#include "scdefine.h"

#if defined(__WIN32__) || defined(_WIN32)
  #include "win32\core.h"
#elif defined(__linux__)
  #include "linux/core.h"
#endif

#if defined(__APPLE__)

#if defined(__OBJC__)
  #import <Cocoa/Cocoa.h>
#else
  #include <CoreServices/CoreServices.h>
#endif

// Misc useful includes
#include <asl.h>
#include <unistd.h>
#include <libgen.h>
#include <uuid/uuid.h> // already included in 10.6 but not in 10.5
#include <libkern/OSAtomic.h>

#if !defined(MAC_OS_X_VERSION_10_6)
  #define MAC_OS_X_VERSION_10_6 1060
#endif

#if !defined(MAC_OS_X_VERSION_10_7)
  #define MAC_OS_X_VERSION_10_7 1070
#endif

#if !defined(MAC_OS_X_VERSION_10_8)
  #define MAC_OS_X_VERSION_10_8 1080
#endif

#else

/* Mac OS Compatibility */
#include "os/macerrors.h"

#include "os/OSAtomic.h"
#include "os/OSByteOrder.h"

#endif // Apple

#if defined(__cplusplus) && __has_feature(__cxx_rvalue_references__)
  /* declaration for move, swap, forward, ... */
  #include <utility>
#endif

/* Compilation on older SDK */
#if !defined (kCFCoreFoundationVersionNumber10_6)
  #define kCFCoreFoundationVersionNumber10_6 550.0
#endif

#if !defined (kCFCoreFoundationVersionNumber10_7)
  #define kCFCoreFoundationVersionNumber10_7 635.0
#endif

// MARK: -
// We need a compile time constant for byte order
enum {
#if defined(__LITTLE_ENDIAN__)
  kOSHostByteOrder = OSLittleEndian
#elif defined(__BIG_ENDIAN__)
  kOSHostByteOrder = OSBigEndian,
#else
  #error undefined byte order
#endif
};

#endif /* __WBC_CORE_H__ */
