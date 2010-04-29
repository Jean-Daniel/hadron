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

#include <tgmath.h>

#if defined(__OBJC__)
#import <Cocoa/Cocoa.h>
#else
#include <CoreServices/CoreServices.h>
#endif

// Misc useful includes
#include <asl.h>
#include <libgen.h>
#include <libkern/OSAtomic.h>

#if !defined(MAC_OS_X_VERSION_10_5)
  #define MAC_OS_X_VERSION_10_5 1050
#endif

#if !defined(MAC_OS_X_VERSION_10_6)
	#define MAC_OS_X_VERSION_10_6 1060
#endif

// MARK: Attributes
#if !defined(WB_OBSOLETE)
  #define WB_OBSOLETE __attribute__((deprecated))
#endif

#if !defined(WB_REQUIRES_NIL_TERMINATION)
  #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
    #define WB_REQUIRES_NIL_TERMINATION __attribute__((sentinel(0,1)))
  #else
    #define WB_REQUIRES_NIL_TERMINATION __attribute__((sentinel))
  #endif
#endif

#if !defined(WB_REQUIRED_ARGS)
  #define WB_REQUIRED_ARGS(idx, args...) __attribute__((nonnull(idx, ##args)))
#endif

#pragma mark Visibility

#if !defined(WB_VISIBLE)
  #define WB_VISIBLE __attribute__((visibility("default")))
#endif

#if !defined(WB_HIDDEN)
  #define WB_HIDDEN __attribute__((visibility("hidden")))
#endif

#if !defined(WB_EXTERN)
  #if defined(__cplusplus)
    #define WB_EXTERN extern "C" 
  #else
    #define WB_EXTERN extern
  #endif
#endif

/*!
 @defined WB_PRIVATE
 @abstract Private extern symbol.
 */
/*!
 @defined WB_EXPORT
 @abstract Exported Wonderbox Function.
 @discussion If WONDERBOX_FRAMEWORK is not defined, WB_EXPORT is the same than WB_PRIVATE
 */
/*!
 @defined WB_PLUGIN_EXPORT
 @abstract Use for plugin entry point. Always export even if WONDERBOX_FRAMEWORK is not defined.
 */

#if defined(__cplusplus)
  #define __inline__ inline
#endif

#define WB_PRIVATE WB_EXTERN WB_HIDDEN
#define WB_PLUGIN_EXPORT WB_EXTERN WB_VISIBLE

#if defined(WONDERBOX_FRAMEWORK)
  #define WB_EXPORT WB_EXTERN WB_VISIBLE
#else
  #define WB_EXPORT WB_EXTERN WB_HIDDEN
#endif

/*!
 @defined WB_CLASS_EXPORT
 @abstract Public class. (64 bits only)
 @discussion If WONDERBOX_FRAMEWORK is not defined, WB_CLASS_EXPORT is the same than WB_CLASS_PRIVATE
 */
/*!
 @defined WB_CLASS_PRIVATE
 @abstract Internal class. (64 bits only)
 */
#if !defined(WB_CLASS_EXPORT)
  #if __LP64__
    #define WB_CLASS_PRIVATE WB_HIDDEN

    #if defined(WONDERBOX_FRAMEWORK)
      #define WB_CLASS_EXPORT WB_VISIBLE
    #else
      #define WB_CLASS_EXPORT WB_CLASS_PRIVATE      
    #endif
  #else
    #define WB_CLASS_EXPORT
    #define WB_CLASS_PRIVATE    
  #endif /* Framework && 64 bits runtime */
#endif

#if !defined(WB_INLINE)
  #if !defined(__NO_INLINE__)
    #define WB_INLINE static __inline__ __attribute__((always_inline))
  #else
    #define WB_INLINE static __inline__
  #endif /* No inline */
#endif

// MARK: Clang
#ifndef __has_builtin         // Optional of course.
  #define __has_builtin(x) 0  // Compatibility with non-clang compilers.
#endif

#ifndef __has_feature         // Optional of course.
  #define __has_feature(x) 0  // Compatibility with non-clang compilers.
#endif

#ifndef UNUSED_IVAR
  #if __has_feature(attribute_objc_ivar_unused)
    #define UNUSED_IVAR __attribute__((unused))
  #else
    #define UNUSED_IVAR
  #endif
#endif

#ifndef NS_RETURNS_RETAINED
  #if __has_feature(attribute_ns_returns_retained)
    #define NS_RETURNS_RETAINED __attribute__((ns_returns_retained))
  #else
    #define NS_RETURNS_RETAINED
  #endif
#endif

#ifndef CF_RETURNS_RETAINED
  #if __has_feature(attribute_cf_returns_retained)
    #define CF_RETURNS_RETAINED __attribute__((cf_returns_retained))
  #else
    #define CF_RETURNS_RETAINED
  #endif
#endif

// MARK: -
// MARK: Tiger Compatibility
#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
	#define NSIntegerHashCallBacks NSIntHashCallBacks
	#define NSIntegerMapKeyCallBacks NSIntMapKeyCallBacks
	#define NSIntegerMapValueCallBacks NSIntMapValueCallBacks

	#define WBMakeCollectable(ptr) (id)ptr
	#define WBAutoreleasePoolDrain(pool) [pool release]
#else
	#define WBMakeCollectable(ptr) NSMakeCollectable(ptr)
	#define WBAutoreleasePoolDrain(pool) [pool drain]
#endif

// MARK: Convenient types
#if !defined(__OBJC__) // for C and C++
	typedef long NSInteger;
	typedef unsigned long NSUInteger;
#endif

// MARK: -
// MARK: Core Foundation
#if defined(__cplusplus)
template<typename T>
inline T WBCFRetain(T aValue) { return aValue ? (T)CFRetain(aValue) : (T)NULL; }
template<typename T>
inline T WBCFMakeCollectable(T aValue) { return aValue ? (T)CFMakeCollectable(aValue) : (T)NULL; }
#else
WB_INLINE
CFTypeRef WBCFRetain(CFTypeRef aValue) { return aValue ? CFRetain(aValue) : NULL; }
#endif

WB_INLINE
void WBCFRelease(CFTypeRef aValue) { if (aValue) CFRelease(aValue); }

#endif /* __WBC_CORE_H__ */
