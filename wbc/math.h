/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Floating point comparison + some other math functions.
*/

#if !defined(__WBC_MATH_H__)
#define __WBC_MATH_H__ 1

SC_INLINE
bool XOR(bool a, bool b) { return (a || b) && !(a && b); }

SC_INLINE
int32_t WBIntSaturate(double x) {
  return x <= (double)INT32_MIN ? INT32_MIN : (double)INT32_MAX <= x ? (int32_t)INT32_MAX : (int32_t)x;
}
SC_INLINE
Fixed WBFloatToFixed(double aFloat) { return WBIntSaturate(aFloat * fixed1); }
SC_INLINE
double WBFixedToFloat(Fixed aValue) {
  if (positiveInfinity == aValue) return INFINITY;
	if (negativeInfinity == aValue) return -INFINITY;
  return (double)aValue / fixed1;
}

// 64 bits to 32 bits safe casts
SC_INLINE
int32_t WBInt64To32(int64_t value) {
  assert(value >= INT32_MIN && value <= INT32_MAX && "Integer overflow");
  return (int32_t)value;
}
SC_INLINE
uint32_t WBUInt64To32(uint64_t value) {
  assert(value <= UINT32_MAX && "Integer overflow");
  return (uint32_t)value;
}

// MARK: -
// MARK: Math Macros
#if defined(__clang__) && !defined(__cplusplus)
  // Clang use a special attribute to make a function overloadable (like C++),
  #define __SC_TG_DECL(type) static __inline__ type __attribute__((__overloadable__, __always_inline__))
#else
  // C++ support attribute averloading.
  #define __SC_TG_DECL(type) static inline type __attribute__((__always_inline__))
#endif

#if defined(__clang__)
  #define __SC_TG_FLOAT(fct)         fct
  #define __SC_TG_DOUBLE(fct)        fct
  #define __SC_TG_LONG_DOUBLE(fct)   fct
#else
  #define __SC_TG_FLOAT(fct)         fct##f
  #define __SC_TG_DOUBLE(fct)        fct
  #define __SC_TG_LONG_DOUBLE(fct)   fct##l
#endif

// MARK: Unsigned round
#define __sc_ulround(a) \
  __typeof__(a) __result = a; \
  if (__result < 0 || __result > ULONG_MAX) { feraiseexcept(FE_INVALID); return 0; } \
  return (unsigned long int)__result

#define __sc_ullround(a) \
  __typeof__(a) __result = a; \
  if (__result < 0 || __result > ULLONG_MAX) { feraiseexcept(FE_INVALID); return 0; } \
  return (unsigned long long int)__result

__SC_TG_DECL(unsigned long int) __SC_TG_FLOAT(__tg_ulround)(float a) { __sc_ulround(roundf(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_DOUBLE(__tg_ulround)(double a) { __sc_ulround(round(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_LONG_DOUBLE(__tg_ulround)(long double a) { __sc_ulround(roundl(a)); }

__SC_TG_DECL(unsigned long long int) __SC_TG_FLOAT(__tg_ullround)(float a) { __sc_ullround(roundf(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_DOUBLE(__tg_ullround)(double a) { __sc_ullround(round(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_LONG_DOUBLE(__tg_ullround)(long double a) { __sc_ullround(roundl(a)); }

#undef __sc_ullround
#undef __sc_ulround

#if defined(__cplusplus)
  #define ulround(__x)        __tg_ulround(__x)
  #define ullround(__x)       __tg_ullround(__x)
#elif defined(__clang__)
  #define ulround(__x)        __tg_ulround(__tg_promote1((__x))(__x))
  #define ullround(__x)       __tg_ullround(__tg_promote1((__x))(__x))
#else
  #define ulround(__x)        __TGMATH_REAL(__x, __tg_ulround)
  #define ullround(__x)       __TGMATH_REAL(__x, __tg_ullround)
#endif

// MARK: Saturate rounding
#define __sc_slround(a) \
  __typeof__(a) __result = a; \
  if (__result <= LONG_MIN) return LONG_MIN; \
  if (__result >= LONG_MAX) return LONG_MAX; \
  return (long int)__result

#define __sc_sllround(a) \
  __typeof__(a) __result = a; \
  if (__result <= LLONG_MIN) return LLONG_MIN; \
  if (__result >= LLONG_MAX) return LLONG_MAX; \
  return (long long int)__result

__SC_TG_DECL(unsigned long int) __SC_TG_FLOAT(__tg_slround)(float a) { __sc_slround(roundf(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_DOUBLE(__tg_slround)(double a) { __sc_slround(round(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_LONG_DOUBLE(__tg_slround)(long double a) { __sc_slround(roundl(a)); }

__SC_TG_DECL(unsigned long long int) __SC_TG_FLOAT(__tg_sllround)(float a) { __sc_sllround(roundf(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_DOUBLE(__tg_sllround)(double a) { __sc_sllround(round(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_LONG_DOUBLE(__tg_sllround)(long double a) { __sc_sllround(roundl(a)); }

#define __sc_sulround(a) \
  __typeof__(a) __result = a; \
  if (__result <= 0) return 0; \
  if (__result >= ULONG_MAX) return ULONG_MAX; \
  return (unsigned long int)__result

#define __sc_sullround(a) \
  __typeof__(a) __result = a; \
  if (__result <= 0) return 0; \
  if (__result >= ULLONG_MAX) return ULLONG_MAX; \
  return (unsigned long long int)__result

__SC_TG_DECL(unsigned long int) __SC_TG_FLOAT(__tg_sulround)(float a) { __sc_sulround(roundf(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_DOUBLE(__tg_sulround)(double a) { __sc_sulround(round(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_LONG_DOUBLE(__tg_sulround)(long double a) { __sc_sulround(roundl(a)); }

__SC_TG_DECL(unsigned long long int) __SC_TG_FLOAT(__tg_sullround)(float a) { __sc_sullround(roundf(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_DOUBLE(__tg_sullround)(double a) { __sc_sullround(round(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_LONG_DOUBLE(__tg_sullround)(long double a) { __sc_sullround(roundl(a)); }

#undef __sc_sullround
#undef __sc_sulround
#undef __sc_sllround
#undef __sc_slround

#if defined(__cplusplus)
  #define slround(__x)        __tg_slround(__x)
  #define sllround(__x)       __tg_sllround(__x)
  #define sulround(__x)       __tg_sulround(__x)
  #define sullround(__x)      __tg_sullround(__x)
#elif defined(__clang__)
  #define slround(__x)        __tg_slround(__tg_promote1((__x))(__x))
  #define sllround(__x)       __tg_sllround(__tg_promote1((__x))(__x))
  #define sulround(__x)       __tg_sulround(__tg_promote1((__x))(__x))
  #define sullround(__x)      __tg_sullround(__tg_promote1((__x))(__x))
#else
  #define slround(__x)        __TGMATH_REAL(__x, __tg_slround)
  #define sllround(__x)       __TGMATH_REAL(__x, __tg_sllround)
  #define sulround(__x)       __TGMATH_REAL(__x, __tg_sulround)
  #define sullround(__x)      __TGMATH_REAL(__x, __tg_sullround)
#endif

// MARK: Float comparisons
__SC_TG_DECL(bool) __SC_TG_FLOAT(__tg_fequal)(float a, float b) { float delta = a - b; return (delta <= FLT_EPSILON && delta >= -FLT_EPSILON); }
__SC_TG_DECL(bool) __SC_TG_DOUBLE(__tg_fequal)(double a, double b) { double delta = a - b; return (delta <= DBL_EPSILON && delta >= -DBL_EPSILON); }
__SC_TG_DECL(bool) __SC_TG_LONG_DOUBLE(__tg_fequal)(long double a, long double b) { long double delta = a - b; return (delta <= LDBL_EPSILON && delta >= -LDBL_EPSILON); }

__SC_TG_DECL(bool) __SC_TG_FLOAT(__tg_fnotequal)(float a, float b) { return !__SC_TG_FLOAT(__tg_fequal)(a, b); }
__SC_TG_DECL(bool) __SC_TG_DOUBLE(__tg_fnotequal)(double a, double b) { return !__SC_TG_DOUBLE(__tg_fequal)(a, b); }
__SC_TG_DECL(bool) __SC_TG_LONG_DOUBLE(__tg_fnotequal)(long double a, long double b) { return !__SC_TG_LONG_DOUBLE(__tg_fequal)(a, b); }

__SC_TG_DECL(bool) __SC_TG_FLOAT(__tg_fiszero)(float f) { return __SC_TG_FLOAT(__tg_fequal)(f, (float)0); }
__SC_TG_DECL(bool) __SC_TG_DOUBLE(__tg_fiszero)(double f) { return __SC_TG_DOUBLE(__tg_fequal)(f, (double)0); }
__SC_TG_DECL(bool) __SC_TG_LONG_DOUBLE(__tg_fiszero)(long double f) { return __SC_TG_LONG_DOUBLE(__tg_fequal)(f, (long double)0); }

__SC_TG_DECL(bool) __SC_TG_FLOAT(__tg_fnonzero)(float f) { return !__SC_TG_FLOAT(__tg_fiszero)(f); }
__SC_TG_DECL(bool) __SC_TG_DOUBLE(__tg_fnonzero)(double f) { return !__SC_TG_DOUBLE(__tg_fiszero)(f); }
__SC_TG_DECL(bool) __SC_TG_LONG_DOUBLE(__tg_fnonzero)(long double f) { return !__SC_TG_LONG_DOUBLE(__tg_fiszero)(f); }

#if defined(__cplusplus)
  #define fiszero(__x)         __tg_fiszero(__x)
  #define fnonzero(__x)        __tg_fnonzero(__x)
  #define fequal(__x, __y)     __tg_fequal(__x, __y)
  #define fnotequal(__x, __y)  __tg_fnotequal(__x, __y)
#elif defined(__clang__)
  // Clang tgmath support
  #define fiszero(__x)         __tg_fiszero(__tg_promote1((__x))(__x))
  #define fnonzero(__x)        __tg_fnonzero(__tg_promote1((__x))(__x))
  #define fequal(__x, __y)     __tg_fequal(__tg_promote2((__x), (__y))(__x), __tg_promote2((__x), (__y))(__y))
  #define fnotequal(__x, __y)  __tg_fnotequal(__tg_promote2((__x), (__y))(__x), __tg_promote2((__x), (__y))(__y))
#else
  // GCC tgmath support
  #define fiszero(__x)        __TGMATH_REAL(__x, __tg_fiszero)
  #define fnonzero(__x)       __TGMATH_REAL(__x, __tg_fnonzero)
  #define fequal(__x, __y)    __TGMATH_REAL_2(__x, __y, __tg_fequal)
  #define fnotequal(__x, __y) __TGMATH_REAL_2(__x, __y, __tg_fnotequal)
#endif // clang/gcc

#undef __SC_TG_LONG_DOUBLE
#undef __SC_TG_DOUBLE
#undef __SC_TG_FLOAT
#undef __SC_TG_DECL

#endif /* __WBC_MATH_H__ */
