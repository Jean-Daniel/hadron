/*
 *  cfutils.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header cfutils
 @abstract CoreFoundation Specifics macros
*/

#if !defined(__WBC_CFUTILS_H__)
#define __WBC_CFUTILS_H__ 1

#ifndef CF_CONSUMED
  #if __has_attribute(cf_consumed)
    #define CF_CONSUMED __attribute__((cf_consumed))
  #else
    #define CF_CONSUMED
  #endif
#endif

#ifndef CF_RETURNS_RETAINED
  #if __has_attribute(cf_returns_retained)
    #define CF_RETURNS_RETAINED __attribute__((cf_returns_retained))
  #else
    #define CF_RETURNS_RETAINED
  #endif
#endif

#ifndef CF_RETURNS_NOT_RETAINED
  #if __has_attribute(cf_returns_not_retained)
    #define CF_RETURNS_NOT_RETAINED __attribute__((cf_returns_not_retained))
  #else
    #define CF_RETURNS_NOT_RETAINED
  #endif
#endif

#if !defined(CFIndexMax)
  #define CFIndexMax LONG_MAX
#endif

#if !defined(CFIndexMin)
  #define CFIndexMin LONG_MIN
#endif

#if defined(__cplusplus)
  template<typename T> // CF_RETURNS_RETAINED // (buggy with template)
  inline T WBCFRetain(T aValue) { return aValue ? (T)CFRetain(aValue) : (T)NULL; }
#else
  SC_INLINE CF_RETURNS_RETAINED
  CFTypeRef __WBCFRetain(CFTypeRef aValue) { return aValue ? CFRetain(aValue) : NULL; }
  #define WBCFRetain(typeref) ((__typeof__(typeref))__WBCFRetain(typeref))
#endif

SC_INLINE
void WBCFRelease(CF_CONSUMED CFTypeRef aValue) { if (aValue) CFRelease(aValue); }

SC_INLINE
Boolean WBCFEqual(CFTypeRef obj1, CFTypeRef obj2) {
  if (!obj1) return !obj2;
  if (obj2)
    return CFEqual(obj1, obj2);
  return false;
}

#endif /* __WBC_CFUTILS_H__ */
