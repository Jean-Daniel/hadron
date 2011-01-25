/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Visibility macros + basics functions
*/

#if !defined(__WBC_CORE_H__)
#define __WBC_CORE_H__ 1

#include <tgmath.h> // MUST be first

#if defined(__OBJC__)
  #import <Cocoa/Cocoa.h>
#else
  #include <CoreServices/CoreServices.h>
#endif

// Misc useful includes
#include <asl.h>
#include <libgen.h>
#include <uuid/uuid.h> // already included in 10.6 but not in 10.5
#include <libkern/OSAtomic.h>

#if !defined(MAC_OS_X_VERSION_10_5)
  #define MAC_OS_X_VERSION_10_5 1050
#endif

#if !defined(MAC_OS_X_VERSION_10_6)
	#define MAC_OS_X_VERSION_10_6 1060
#endif

// MARK: Attributes
#if !defined(SC_OBSOLETE)
  #define SC_OBSOLETE __attribute__((deprecated))
#endif

#if !defined(SC_REQUIRES_NIL_TERMINATION)
  #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
    #define SC_REQUIRES_NIL_TERMINATION __attribute__((sentinel(0,1)))
  #else
    #define SC_REQUIRES_NIL_TERMINATION __attribute__((sentinel))
  #endif
#endif

#if !defined(SC_REQUIRED_ARGS)
  #define SC_REQUIRED_ARGS(idx, args...) __attribute__((nonnull(idx, ##args)))
#endif

#pragma mark Visibility

#if !defined(SC_VISIBLE)
  #define SC_VISIBLE __attribute__((visibility("default")))
#endif

#if !defined(SC_HIDDEN)
  #define SC_HIDDEN __attribute__((visibility("hidden")))
#endif

#if !defined(SC_EXTERN)
  #if defined(__cplusplus)
    #define SC_EXTERN extern "C"
  #else
    #define SC_EXTERN extern
  #endif
#endif

/*!
 @defined SC_PRIVATE
 @abstract Private extern symbol.
 */
/*!
 @defined SC_EXPORT
 @abstract Exported Wonderbox Function.
 */

#if defined(__cplusplus)
  #define __inline__ inline
#endif

#define SC_PRIVATE SC_EXTERN SC_HIDDEN
#define SC_EXPORT SC_EXTERN SC_VISIBLE

#if !defined(SC_INLINE)
  #if !defined(__NO_INLINE__)
    #define SC_INLINE static __inline__ __attribute__((always_inline))
  #else
    #define SC_INLINE static __inline__
  #endif /* No inline */
#endif

// MARK: Clang
#ifndef __has_builtin         // Optional of course.
  #define __has_builtin(x) 0  // Compatibility with non-clang compilers.
#endif

#ifndef __has_feature         // Optional of course.
  #define __has_feature(x) 0  // Compatibility with non-clang compilers.
#endif

#ifndef __has_attribute         // Optional of course.
  #define __has_attribute(x) 0  // Compatibility with non-clang compilers.
#endif

#ifndef UNUSED_IVAR
  #if __has_feature(attribute_objc_ivar_unused)
    #define UNUSED_IVAR __attribute__((unused))
  #else
    #define UNUSED_IVAR
  #endif
#endif

#ifndef NS_RETURNS_RETAINED
  #if __has_attribute(ns_returns_retained)
    #define NS_RETURNS_RETAINED __attribute__((ns_returns_retained))
  #else
    #define NS_RETURNS_RETAINED
  #endif
#endif

#ifndef CF_RETURNS_RETAINED
  #if __has_attribute(cf_returns_retained)
    #define CF_RETURNS_RETAINED __attribute__((cf_returns_retained))
  #else
    #define CF_RETURNS_RETAINED
  #endif
#endif

#ifndef NS_RETURNS_NOT_RETAINED
	#if __has_attribute(ns_returns_not_retained)
		#define NS_RETURNS_NOT_RETAINED __attribute__((ns_returns_not_retained))
	#else
		#define NS_RETURNS_NOT_RETAINED
	#endif
#endif

#ifndef CF_RETURNS_NOT_RETAINED
	#if __has_attribute(cf_returns_not_retained)
		#define CF_RETURNS_NOT_RETAINED __attribute__((cf_returns_not_retained))
	#else
		#define CF_RETURNS_NOT_RETAINED
	#endif
#endif

#ifndef NS_CONSUMED
  #if __has_attribute(ns_consumed)
    #define NS_CONSUMED __attribute__((ns_consumed))
  #else
    #define NS_CONSUMED
  #endif
#endif

#ifndef CF_CONSUMED
  #if __has_attribute(cf_consumed)
    #define CF_CONSUMED __attribute__((cf_consumed))
  #else
    #define CF_CONSUMED
  #endif
#endif

#ifndef NS_CONSUMES_SELF
  #if __has_attribute(ns_consumes_self)
    #define NS_CONSUMED_SELF __attribute__((ns_consumes_self))
  #else
    #define NS_CONSUMED_SELF
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
#if !defined(__OBJC__) // for C and C++
	typedef long NSInteger;
  #define NSIntegerMax LONG_MAX
  #define NSIntegerMin LONG_MIN

	typedef unsigned long NSUInteger;
  #define NSUIntegerMAX ULONG_MAX
#endif

// MARK: -
// MARK: Core Foundation
#if !defined(CFIndexMax)
  #define CFIndexMax LONG_MAX
#endif

#if !defined(CFIndexMin)
  #define CFIndexMin LONG_MIN
#endif

#if defined(__cplusplus)
  template<typename T> // CF_RETURNS_RETAINED (buggy with template)
  inline T WBCFRetain(T aValue) { return aValue ? (T)CFRetain(aValue) : (T)NULL; }
  template<typename T>
  inline T WBCFMakeCollectable(T aValue) { return aValue ? (T)CFMakeCollectable(aValue) : (T)NULL; }
#else
  SC_INLINE CF_RETURNS_RETAINED
  CFTypeRef WBCFRetain(CFTypeRef aValue) { return aValue ? CFRetain(aValue) : NULL; }
#endif

SC_INLINE
void WBCFRelease(CF_CONSUMED CFTypeRef aValue) { if (aValue) CFRelease(aValue); }

#endif /* __WBC_CORE_H__ */
