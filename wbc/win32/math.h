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

#if !defined(__WBC_WIN32_MATH_H__)
#define __WBC_WIN32_MATH_H__ 1

typedef int32_t Fixed;
#define fixed1 ((Fixed) 0x00010000L)
#define positiveInfinity ((Fixed)0x7FFFFFFFL)
#define negativeInfinity ((Fixed)(-0x7FFFFFFFL - 1))

#if !defined(INFINITY)
  #define INFINITY std::numeric_limits<double>::infinity()
#endif

#if HAS_BOOST

#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

// libc maths
namespace std {
	// TR1 Compatibility
	template<typename Ty>
	inline int isnan(Ty value) { return boost::math::isnan(value); }
	template<typename Ty>
	inline int isinf(Ty value) { return boost::math::isinf(value); }
	template<typename Ty>
	inline int signbit(Ty value) { return boost::math::signbit(value); }
}

template <class Ty>
inline Ty round(Ty v) { return boost::math::round(v); }

template <class Ty>
inline long lround(Ty v) { return boost::math::lround(v); }

template <class Ty>
inline long long llround(Ty v) { return boost::math::llround(v); }

#else
template <typename Ty>
Ty round(Ty r) {
  return (r > (Ty)0.0) ? floor(r + (Ty)0.5) : ceil(r - (Ty)0.5);
}
#endif

static __forceinline float roundf(float v) { return round<float>(v); }
static __forceinline long double roundl(long double v) { return round<long double>(v); }

#define FE_INVALID 0
inline static void feraiseexcept(int code) { /* FIXME: not supported */ }

#endif /* __WBC_WIN32_MATH_H__ */
