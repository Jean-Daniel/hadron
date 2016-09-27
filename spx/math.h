/*
 *  math.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Floating point comparison + some other math functions.
*/

SPX_INLINE
bool spx_xor(bool a, bool b) { return (a || b) && !(a && b); }

// Do not rely on macros defined NSObjCRuntime because they are not safe to use with ANSI C (they do not use temp variable)
#undef MIN
#undef MAX
#undef ABS

#if defined(__cplusplus)
  #include <cmath> // define __GLIBCXX__ if needed
#endif

#if !defined(__cplusplus) || (defined(__GLIBCXX__) && !defined(_GLIBCXX_USE_C99_MATH_TR1))
#if !defined(MIN)
  #define MIN(A,B) ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#endif
#if !defined(MAX)
  #define MAX(A,B) ({ __typeof__(A) __x = (A); __typeof__(B) __y = (B); __x < __y ? __y : __x; })
#endif
#if !defined(ABS)
  #define ABS(A)   ({ __typeof__(A) __z = (A); __z < 0 ? -__z : __z; })
#endif
#else
  // FIXME: Version number is wrong. should be the first one that introduce std compliant cmath
  #if defined(__GLIBCXX__) && __GLIBCXX__ < 20080905
    #include <tr1/cmath>
    namespace std {
      using tr1::fmin;
      using tr1::fmax;
    }
  #endif

  namespace spxcfg {
    // min
    template <class T> SPX_INLINE
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    min(T a, T b) { return std::fmin(a, b); }

    // min/max: r = (x < y) ? x : y; -> r = y ^ ((x ^ y) & -(x < y))
    // Note: -(x < y) is -1 or 0, so the expression is either (y ^ x ^ y), or (y ^ 0).
    template <class T> SPX_INLINE
    typename std::enable_if<std::is_integral<T>::value, T>::type
    min(T a, T b) { return b ^ ((a ^ b) & -(a < b)); }

    template <class T> SPX_INLINE
    typename std::enable_if<!std::is_arithmetic<T>::value, T>::type
    min(T a, T b) { return (a < b) ? a : b; }

    // max
    template <class T> SPX_INLINE
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    max(T a, T b) { return std::fmax(a, b); }

    template <class T> SPX_INLINE
    typename std::enable_if<std::is_integral<T>::value, T>::type
    max(T a, T b) { return b ^ ((a ^ b) & -(a > b)); }

    template <class T> SPX_INLINE
    typename std::enable_if<!std::is_arithmetic<T>::value, T>::type
    max(T a, T b) { return (a > b) ? a : b; }

    // abs
    template <class T> SPX_INLINE
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    abs(T a) { return std::fabs(a); }

    template <class T> SPX_INLINE
    typename std::enable_if<std::is_integral<T>::value, T>::type
    abs(T a) { T mask = (a >> (sizeof(T) * CHAR_BIT - 1)); return (a + mask) ^ mask; }
  }

  #define MIN(A,B) spxcfg::min(A, B)
  #define MAX(A,B) spxcfg::max(A, B)
  #define ABS(A)   spxcfg::abs(A)
#endif

/* Windows math.h lacks a lot of standards functions */
#if defined(_WIN32)
  #include "win32/math.h"
#endif

// MARK: -
// MARK: Math Macros
#if defined(__TGMATH_H)
  #error tgmath.h must not be included at this point
#endif

#if defined(__clang__) && !defined(__cplusplus)
  // Clang use a special attribute to make a function overloadable (like C++),
  #define __SPX_TG_DECL(type) static __inline__ type __attribute__((__overloadable__, __always_inline__))
#else
  // C++ support attribute averloading.
  #if defined(_MSC_VER)
    #define __SPX_TG_DECL(type) __forceinline static type
  #else
    #define __SPX_TG_DECL(type) static inline type __attribute__((__always_inline__))
  #endif
#endif

#if defined(__clang__) || defined(__cplusplus)
  #define __SPX_TG_FLOAT(fct)         fct
  #define __SPX_TG_DOUBLE(fct)        fct
  #define __SPX_TG_LONG_DOUBLE(fct)   fct
#else
  #define __SPX_TG_FLOAT(fct)         fct##f
  #define __SPX_TG_DOUBLE(fct)        fct
  #define __SPX_TG_LONG_DOUBLE(fct)   fct##l
#endif

// MARK: Unsigned round
#define __spx_ulround(Ty, a) \
  Ty __result = a; \
  if (__result < 0 || __result > ULONG_MAX) { feraiseexcept(FE_INVALID); return 0; } \
  return (unsigned long int)__result

#define __spx_ullround(Ty, a) \
  Ty __result = a; \
  if (__result < 0 || __result > ULLONG_MAX) { feraiseexcept(FE_INVALID); return 0; } \
  return (unsigned long long int)__result

__SPX_TG_DECL(unsigned long int) __SPX_TG_FLOAT(__tg_ulround)(float a) { __spx_ulround(float, roundf(a)); }
__SPX_TG_DECL(unsigned long int) __SPX_TG_DOUBLE(__tg_ulround)(double a) { __spx_ulround(double, round(a)); }
__SPX_TG_DECL(unsigned long int) __SPX_TG_LONG_DOUBLE(__tg_ulround)(long double a) { __spx_ulround(long double, roundl(a)); }

__SPX_TG_DECL(unsigned long long int) __SPX_TG_FLOAT(__tg_ullround)(float a) { __spx_ullround(float, roundf(a)); }
__SPX_TG_DECL(unsigned long long int) __SPX_TG_DOUBLE(__tg_ullround)(double a) { __spx_ullround(double, round(a)); }
__SPX_TG_DECL(unsigned long long int) __SPX_TG_LONG_DOUBLE(__tg_ullround)(long double a) { __spx_ullround(long double, roundl(a)); }

#undef __spx_ullround
#undef __spx_ulround

// MARK: Saturate rounding
#define __spx_slround(Ty, a) \
  Ty __result = a; \
  if (__result <= LONG_MIN) return LONG_MIN; \
  if (__result >= LONG_MAX) return LONG_MAX; \
  return (long int)__result

#define __spx_sllround(Ty, a) \
  Ty __result = a; \
  if (__result <= LLONG_MIN) return LLONG_MIN; \
  if (__result >= LLONG_MAX) return LLONG_MAX; \
  return (long long int)__result

__SPX_TG_DECL(long int) __SPX_TG_FLOAT(__tg_slround)(float a) { __spx_slround(float, roundf(a)); }
__SPX_TG_DECL(long int) __SPX_TG_DOUBLE(__tg_slround)(double a) { __spx_slround(double, round(a)); }
__SPX_TG_DECL(long int) __SPX_TG_LONG_DOUBLE(__tg_slround)(long double a) { __spx_slround(long double, roundl(a)); }

__SPX_TG_DECL(long long int) __SPX_TG_FLOAT(__tg_sllround)(float a) { __spx_sllround(float, roundf(a)); }
__SPX_TG_DECL(long long int) __SPX_TG_DOUBLE(__tg_sllround)(double a) { __spx_sllround(double, round(a)); }
__SPX_TG_DECL(long long int) __SPX_TG_LONG_DOUBLE(__tg_sllround)(long double a) { __spx_sllround(long double, roundl(a)); }

#define __spx_sulround(Ty, a) \
  Ty __result = a; \
  if (__result <= 0) return 0; \
  if (__result >= ULONG_MAX) return ULONG_MAX; \
  return (unsigned long int)__result

#define __spx_sullround(Ty, a) \
  Ty __result = a; \
  if (__result <= 0) return 0; \
  if (__result >= ULLONG_MAX) return ULLONG_MAX; \
  return (unsigned long long int)__result

__SPX_TG_DECL(unsigned long int) __SPX_TG_FLOAT(__tg_sulround)(float a) { __spx_sulround(float, roundf(a)); }
__SPX_TG_DECL(unsigned long int) __SPX_TG_DOUBLE(__tg_sulround)(double a) { __spx_sulround(double, round(a)); }
__SPX_TG_DECL(unsigned long int) __SPX_TG_LONG_DOUBLE(__tg_sulround)(long double a) { __spx_sulround(long double, roundl(a)); }

__SPX_TG_DECL(unsigned long long int) __SPX_TG_FLOAT(__tg_sullround)(float a) { __spx_sullround(float, roundf(a)); }
__SPX_TG_DECL(unsigned long long int) __SPX_TG_DOUBLE(__tg_sullround)(double a) { __spx_sullround(double, round(a)); }
__SPX_TG_DECL(unsigned long long int) __SPX_TG_LONG_DOUBLE(__tg_sullround)(long double a) { __spx_sullround(long double, roundl(a)); }

#undef __spx_sullround
#undef __spx_sulround
#undef __spx_sllround
#undef __spx_slround

// MARK: Float comparisons
__SPX_TG_DECL(bool) __SPX_TG_FLOAT(__tg_fequal)(float a, float b) { float delta = a - b; return (delta <= FLT_EPSILON && delta >= -FLT_EPSILON); }
__SPX_TG_DECL(bool) __SPX_TG_DOUBLE(__tg_fequal)(double a, double b) { double delta = a - b; return (delta <= DBL_EPSILON && delta >= -DBL_EPSILON); }
__SPX_TG_DECL(bool) __SPX_TG_LONG_DOUBLE(__tg_fequal)(long double a, long double b) { long double delta = a - b; return (delta <= LDBL_EPSILON && delta >= -LDBL_EPSILON); }

__SPX_TG_DECL(bool) __SPX_TG_FLOAT(__tg_fnotequal)(float a, float b) { return !__SPX_TG_FLOAT(__tg_fequal)(a, b); }
__SPX_TG_DECL(bool) __SPX_TG_DOUBLE(__tg_fnotequal)(double a, double b) { return !__SPX_TG_DOUBLE(__tg_fequal)(a, b); }
__SPX_TG_DECL(bool) __SPX_TG_LONG_DOUBLE(__tg_fnotequal)(long double a, long double b) { return !__SPX_TG_LONG_DOUBLE(__tg_fequal)(a, b); }

__SPX_TG_DECL(bool) __SPX_TG_FLOAT(__tg_fiszero)(float f) { return __SPX_TG_FLOAT(__tg_fequal)(f, (float)0); }
__SPX_TG_DECL(bool) __SPX_TG_DOUBLE(__tg_fiszero)(double f) { return __SPX_TG_DOUBLE(__tg_fequal)(f, (double)0); }
__SPX_TG_DECL(bool) __SPX_TG_LONG_DOUBLE(__tg_fiszero)(long double f) { return __SPX_TG_LONG_DOUBLE(__tg_fequal)(f, (long double)0); }

__SPX_TG_DECL(bool) __SPX_TG_FLOAT(__tg_fnonzero)(float f) { return !__SPX_TG_FLOAT(__tg_fiszero)(f); }
__SPX_TG_DECL(bool) __SPX_TG_DOUBLE(__tg_fnonzero)(double f) { return !__SPX_TG_DOUBLE(__tg_fiszero)(f); }
__SPX_TG_DECL(bool) __SPX_TG_LONG_DOUBLE(__tg_fnonzero)(long double f) { return !__SPX_TG_LONG_DOUBLE(__tg_fiszero)(f); }

#undef __SPX_TG_LONG_DOUBLE
#undef __SPX_TG_DOUBLE
#undef __SPX_TG_FLOAT
#undef __SPX_TG_DECL

// We have to include tgmath after defining our functions to be able to use
// math functions directly (for instance, round() must not be expanded to tgmath equivalent)
#if !defined(__cplusplus)
  #include <tgmath.h>
#endif

#if defined(__cplusplus)
  #define spx_tg_unary_fct(__x, fct)        fct(__x)
  #define spx_tg_binary_fct(__x, __y, fct)  fct(__x, __y)
#elif defined(__clang__)
  #define spx_tg_unary_fct(__x, fct)        fct(__tg_promote1((__x))(__x))
  #define spx_tg_binary_fct(__x, __y, fct)  fct(__tg_promote2((__x), (__y))(__x), __tg_promote2((__x), (__y))(__y))
#elif defined(__TGMATH_REAL)
  #define spx_tg_unary_fct(__x, fct)        __TGMATH_REAL(__x, fct)
  #define spx_tg_binary_fct(__x, __y, fct)  __TGMATH_REAL_2(__x, __y, fct)
#elif defined(__TGMATH_UNARY_REAL_ONLY)
  #define spx_tg_unary_fct(__x, fct)        __TGMATH_UNARY_REAL_ONLY(__x, fct)
  #define spx_tg_binary_fct(__x, __y, fct)  __TGMATH_BINARY_REAL_ONLY(__x, __y, fct)
#else
  #error tgmath implmentation not supported
#endif

// Unsigned round
#define ulround(__x)        spx_tg_unary_fct(__x, __tg_ulround)
#define ullround(__x)       spx_tg_unary_fct(__x, __tg_ullround)

// Saturate round
#define slround(__x)        spx_tg_unary_fct(__x, __tg_slround)
#define sllround(__x)       spx_tg_unary_fct(__x, __tg_sllround)
#define sulround(__x)       spx_tg_unary_fct(__x, __tg_sulround)
#define sullround(__x)      spx_tg_unary_fct(__x, __tg_sullround)

// Floating point compare
#define fiszero(__x)        spx_tg_unary_fct(__x, __tg_fiszero)
#define fnonzero(__x)       spx_tg_unary_fct(__x, __tg_fnonzero)
#define fequal(__x, __y)    spx_tg_binary_fct(__x, __y, __tg_fequal)
#define fnotequal(__x, __y) spx_tg_binary_fct(__x, __y, __tg_fnotequal)

