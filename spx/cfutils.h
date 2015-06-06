/*
 *  cfutils.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract CoreFoundation Utilities
*/

#if !defined(CFIndexMax)
  #define CFIndexMax LONG_MAX
#endif

#if !defined(CFIndexMin)
  #define CFIndexMin LONG_MIN
#endif

#if defined(__cplusplus) && __cplusplus >= 201103

#include <memory>

namespace spx {
  template<typename Ty>
  struct cftype_delete {
    constexpr cftype_delete() noexcept = default;
    cftype_delete(const cftype_delete<Ty>&) noexcept = default;
    void operator()(CF_CONSUMED Ty obj) { if (obj) CFRelease(obj); }
  };

  // unique_ptr alias used to autorelease CFTypeRef
  template<typename Ty>
  using unique_cfptr = std::unique_ptr<typename std::remove_pointer<Ty>::type, cftype_delete<Ty>>;
}

#endif

#if defined(__cplusplus)
  template<typename T> CF_RETURNS_RETAINED
  inline T SPXCFRetain(T aValue) { return aValue ? (T)CFRetain(aValue) : (T)NULL; }
#else
  SPX_INLINE CF_RETURNS_RETAINED
  CFTypeRef __SPXCFRetain(CFTypeRef aValue) { return aValue ? CFRetain(aValue) : NULL; }
  #define SPXCFRetain(typeref) ((__typeof__(typeref))__SPXCFRetain(typeref))
#endif

SPX_INLINE
void SPXCFRelease(CF_CONSUMED CFTypeRef aValue) { if (aValue) CFRelease(aValue); }

SPX_INLINE
Boolean SPXCFEqual(CFTypeRef obj1, CFTypeRef obj2) {
  if (!obj1) return !obj2;
  return obj2 ? CFEqual(obj1, obj2) : false;
}
