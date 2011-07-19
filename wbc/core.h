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

#if defined(__clang__) || defined(__GNUC__)
  #include <tgmath.h> // MUST be first
#endif

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


#if !defined(MAC_OS_X_VERSION_10_5)
  #define MAC_OS_X_VERSION_10_5 1050
#endif

#if !defined(MAC_OS_X_VERSION_10_6)
  #define MAC_OS_X_VERSION_10_6 1060
#endif

#if !defined(MAC_OS_X_VERSION_10_7)
  #define MAC_OS_X_VERSION_10_7 1070
#endif

#else

/* Mac OS Compatibility */
#include "os/macerrors.h"

#include "os/OSAtomic.h"
#include "os/OSByteOrder.h"

#endif // Apple

/* Compilation on older SDK */
#if !defined (kCFCoreFoundationVersionNumber10_5)
  #define kCFCoreFoundationVersionNumber10_5 476.00
#endif

#if !defined (kCFCoreFoundationVersionNumber10_6)
  #define kCFCoreFoundationVersionNumber10_6 550.0
#endif

#if !defined (kCFCoreFoundationVersionNumber10_7)
  #define kCFCoreFoundationVersionNumber10_7 635.0
#endif

// MARK: Attributes
#if !defined(SC_UNUSED)
  #if defined(_MSC_VER)
    #define SC_UNUSED
  #else
    #define SC_UNUSED __attribute__((unused))
  #endif
#endif

#if !defined(SC_REQUIRES_NIL_TERMINATION)
  #if defined(_MSC_VER)
    #define SC_REQUIRES_NIL_TERMINATION
  #else
    #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
      #define SC_REQUIRES_NIL_TERMINATION __attribute__((sentinel(0,1)))
    #else
      #define SC_REQUIRES_NIL_TERMINATION __attribute__((sentinel))
    #endif
  #endif
#endif

#if !defined(SC_REQUIRED_ARGS)
  #if defined(_MSC_VER)
    #define SC_REQUIRED_ARGS(idx, ...)
  #else
    #define SC_REQUIRED_ARGS(idx, args...) __attribute__((nonnull(idx, ##args)))
  #endif
#endif

#if !defined(SC_EXTERN)
  #if defined(__cplusplus)
    #define SC_EXTERN extern "C"
  #else
    #define SC_EXTERN extern
  #endif
#endif

#if defined(__cplusplus)
  #define __inline__ inline
#endif

#if !defined(SC_INLINE)
  #if !defined(__NO_INLINE__)
    #if defined(_MSC_VER)
      #define SC_INLINE __forceinline static
    #else
      #define SC_INLINE __inline__ __attribute__((always_inline)) static
    #endif
  #else
    #define SC_INLINE __inline__ static
  #endif /* No inline */
#endif

/* Misc attributes */
#if !defined(wb_noreturn)
  #if defined(_MSC_VER)
    #define wb_noreturn __declspec(noreturn)
  #else
    #define wb_noreturn __attribute__((noreturn))
  #endif
#endif

// MARK: Clang
#ifndef __has_builtin
  #define __has_builtin(x) 0
#endif

#ifndef __has_feature
  #define __has_feature(x) 0
#endif

#ifndef __has_extension
  #define __has_extension(x) __has_feature(x)
#endif

#ifndef __has_attribute
  #define __has_attribute(x) 0
#endif

#ifndef __has_include
  #define __has_include(x) 0
#endif

#ifndef __has_include_next
  #define __has_include_next(x) 0
#endif

// MARK: Static Analyzer
#if defined(__OBJC__)

  #ifndef NS_UNUSED_IVAR
    #if __has_extension(attribute_objc_ivar_unused)
      #define NS_UNUSED_IVAR __attribute__((unused))
    #else
      #define NS_UNUSED_IVAR
    #endif
  #endif

  #ifndef NS_CONSUMED
    #if __has_attribute(ns_consumed)
      #define NS_CONSUMED __attribute__((ns_consumed))
    #else
      #define NS_CONSUMED
    #endif
  #endif

  #ifndef NS_CONSUMES_SELF
    #if __has_attribute(ns_consumes_self)
      #define NS_CONSUMES_SELF __attribute__((ns_consumes_self))
    #else
      #define NS_CONSUMES_SELF
    #endif
  #endif

  #ifndef NS_RETURNS_RETAINED
    #if __has_attribute(ns_returns_retained)
      #define NS_RETURNS_RETAINED __attribute__((ns_returns_retained))
    #else
      #define NS_RETURNS_RETAINED
    #endif
  #endif

  #ifndef NS_RETURNS_NOT_RETAINED
    #if __has_attribute(ns_returns_not_retained)
      #define NS_RETURNS_NOT_RETAINED __attribute__((ns_returns_not_retained))
    #else
      #define NS_RETURNS_NOT_RETAINED
    #endif
  #endif

  #ifndef NS_RETURNS_AUTORELEASED
    #if __has_attribute(ns_returns_autoreleased)
      #define NS_RETURNS_AUTORELEASED __attribute__((ns_returns_autoreleased))
    #else
      #define NS_RETURNS_AUTORELEASED
    #endif
  #endif

  /* Method Family */
  #ifndef NS_METHOD_FAMILY
    /* supported families are: none, alloc, copy, init, mutableCopy, and new. */
    #if __has_attribute(ns_returns_autoreleased)
      #define NS_METHOD_FAMILY(family) __attribute__((objc_method_family(family)))
    #else
      #define NS_METHOD_FAMILY(arg)
    #endif
  #endif

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

// MARK: Convenient types
#if !defined(__OBJC__) || (defined(__APPLE__) && (MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_5)) // for C and C++
  typedef long NSInteger;
  #define NSIntegerMax LONG_MAX
  #define NSIntegerMin LONG_MIN

  typedef unsigned long NSUInteger;
  #define NSUIntegerMAX ULONG_MAX
#endif

#if !defined(CGFLOAT_DEFINED)
  #if defined(__LP64__) && __LP64__
    typedef double CGFloat;
    #define CGFLOAT_MIN DBL_MIN
    #define CGFLOAT_MAX DBL_MAX
    #define CGFLOAT_IS_DOUBLE 1
  #else	/* !defined(__LP64__) || !__LP64__ */
    typedef float CGFloat;
    #define CGFLOAT_MIN FLT_MIN
    #define CGFLOAT_MAX FLT_MAX
    #define CGFLOAT_IS_DOUBLE 0
  #endif	/* !defined(__LP64__) || !__LP64__ */
  #define CGFLOAT_DEFINED 1
#endif

#endif /* __WBC_CORE_H__ */
