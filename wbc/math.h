/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
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

#if defined(_WIN32)
  #include <boost/math/special_functions/sign.hpp>
  #include <boost/math/special_functions/round.hpp>
  #include <boost/math/special_functions/fpclassify.hpp>

  typedef int32_t Fixed;
  #define fixed1 ((Fixed) 0x00010000L)
  #define positiveInfinity ((Fixed)0x7FFFFFFFL)
  #define negativeInfinity ((Fixed)(-0x7FFFFFFFL - 1))

  #if !defined(INFINITY)
    #define INFINITY std::numeric_limits<double>::infinity()
  #endif

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

__forceinline float roundf(float v) { return round<float>(v); }
__forceinline long double roundl(long double v) { return round<long double>(v); }

#define FE_INVALID 0
inline static void feraiseexcept(int code) { /* FIXME: not supported */ }

#endif

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
  #if defined(_MSC_VER)
    #define __SC_TG_DECL(type) __forceinline static type
  #else
    #define __SC_TG_DECL(type) static inline type __attribute__((__always_inline__))
  #endif
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
#define __sc_ulround(Ty, a) \
  Ty __result = a; \
  if (__result < 0 || __result > ULONG_MAX) { feraiseexcept(FE_INVALID); return 0; } \
  return (unsigned long int)__result

#define __sc_ullround(Ty, a) \
  Ty __result = a; \
  if (__result < 0 || __result > ULLONG_MAX) { feraiseexcept(FE_INVALID); return 0; } \
  return (unsigned long long int)__result

__SC_TG_DECL(unsigned long int) __SC_TG_FLOAT(__tg_ulround)(float a) { __sc_ulround(float, roundf(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_DOUBLE(__tg_ulround)(double a) { __sc_ulround(double, round(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_LONG_DOUBLE(__tg_ulround)(long double a) { __sc_ulround(long double, roundl(a)); }

__SC_TG_DECL(unsigned long long int) __SC_TG_FLOAT(__tg_ullround)(float a) { __sc_ullround(float, roundf(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_DOUBLE(__tg_ullround)(double a) { __sc_ullround(double, round(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_LONG_DOUBLE(__tg_ullround)(long double a) { __sc_ullround(long double, roundl(a)); }

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
#define __sc_slround(Ty, a) \
  Ty __result = a; \
  if (__result <= LONG_MIN) return LONG_MIN; \
  if (__result >= LONG_MAX) return LONG_MAX; \
  return (long int)__result

#define __sc_sllround(Ty, a) \
  Ty __result = a; \
  if (__result <= LLONG_MIN) return LLONG_MIN; \
  if (__result >= LLONG_MAX) return LLONG_MAX; \
  return (long long int)__result

__SC_TG_DECL(long int) __SC_TG_FLOAT(__tg_slround)(float a) { __sc_slround(float, roundf(a)); }
__SC_TG_DECL(long int) __SC_TG_DOUBLE(__tg_slround)(double a) { __sc_slround(double, round(a)); }
__SC_TG_DECL(long int) __SC_TG_LONG_DOUBLE(__tg_slround)(long double a) { __sc_slround(long double, roundl(a)); }

__SC_TG_DECL(long long int) __SC_TG_FLOAT(__tg_sllround)(float a) { __sc_sllround(float, roundf(a)); }
__SC_TG_DECL(long long int) __SC_TG_DOUBLE(__tg_sllround)(double a) { __sc_sllround(double, round(a)); }
__SC_TG_DECL(long long int) __SC_TG_LONG_DOUBLE(__tg_sllround)(long double a) { __sc_sllround(long double, roundl(a)); }

#define __sc_sulround(Ty, a) \
  Ty __result = a; \
  if (__result <= 0) return 0; \
  if (__result >= ULONG_MAX) return ULONG_MAX; \
  return (unsigned long int)__result

#define __sc_sullround(Ty, a) \
  Ty __result = a; \
  if (__result <= 0) return 0; \
  if (__result >= ULLONG_MAX) return ULLONG_MAX; \
  return (unsigned long long int)__result

__SC_TG_DECL(unsigned long int) __SC_TG_FLOAT(__tg_sulround)(float a) { __sc_sulround(float, roundf(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_DOUBLE(__tg_sulround)(double a) { __sc_sulround(double, round(a)); }
__SC_TG_DECL(unsigned long int) __SC_TG_LONG_DOUBLE(__tg_sulround)(long double a) { __sc_sulround(long double, roundl(a)); }

__SC_TG_DECL(unsigned long long int) __SC_TG_FLOAT(__tg_sullround)(float a) { __sc_sullround(float, roundf(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_DOUBLE(__tg_sullround)(double a) { __sc_sullround(double, round(a)); }
__SC_TG_DECL(unsigned long long int) __SC_TG_LONG_DOUBLE(__tg_sullround)(long double a) { __sc_sullround(long double, roundl(a)); }

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

// MARK: bit maths
#if defined(_MSC_VER)
SC_INLINE int popcnt32(uint32_t value) { return __popcnt(value); }
SC_INLINE int popcnt64(uint64_t value) { return __popcnt64(value); }

static __inline int clz32(uint32_t value) {
  unsigned long idx;
  _BitScanReverse(&idx, value);
  return idx;
}
static __inline int clz64(uint64_t value) {
  unsigned long idx;
  _BitScanReverse64(&idx, value);
  return idx;
}

static __inline int fls32(uint32_t value) {
  unsigned long idx = 0;
  if (_BitScanReverse(&idx, value))
    return idx + 1; // [1; 32] with 1 least significant bit
  return 0;
}
static __inline int fls64(uint64_t value) {
  unsigned long idx = 0;
  if (_BitScanReverse64(&idx, value))
    return idx + 1; // [1; 64] with 1 least significant bit
  return 0;
}

int ctz32(uint32_t value) {
  unsigned long idx; // do not init to match undefined behavior of GCC
  _BitScanForward(&idx, value);
  return idx;
}
int ctz64(uint64_t value) {
  unsigned long idx;
  _BitScanForward64(&idx, value);
  return idx;
}
static __inline int ffs32(uint32_t value) {
  unsigned long idx = 0;
  if (_BitScanForward(&idx, value))
    return idx + 1; // [1; 32] with 1 least significant bit
  return 0;
}
static __inline int ffs64(uint64_t value) {
  unsigned long idx = 0;
  if (_BitScanForward64(&idx, value))
    return idx + 1; // [1; 64] with 1 least significant bit
  return 0;
}
#else
// Population count
SC_INLINE int popcnt32(uint32_t value) { return __builtin_popcount(value); }
SC_INLINE int popcnt64(uint64_t value) { return __builtin_popcountll(value); }

// Count Leading Zeros (left)
// returns 0 based index. If value zero, result is undefined.
SC_INLINE int clz32(uint32_t value) { return __builtin_clz(value); }
SC_INLINE int clz64(uint64_t value) { return __builtin_clzll(value); }
// returns 1 based index. If vlaue is 0, returns 0.
SC_INLINE int fls32(uint32_t value) { return value ? __builtin_clz(value) + 1 : 0; }
SC_INLINE int fls64(uint64_t value) { return value ? __builtin_clzll(value) + 1 : 0; }

// Count Trailing Zeros (right)
// returns 0 based index. If value zero, result is undefined.
SC_INLINE int ctz32(uint32_t value) { return __builtin_ctz(value); }
SC_INLINE int ctz64(uint64_t value) { return __builtin_ctzll(value); }
// returns 1 based index. If vlaue is 0, returns 0.
SC_INLINE int ffs32(uint32_t value) { return __builtin_ffs(value); }
SC_INLINE int ffs64(uint64_t value) { return __builtin_ffsll(value); }

// Returns the parity of value, i.e. the number of 1-bits in x modulo 2.
//SC_INLINE int parity32(uint32_t value) { return __builtin_parity(value); }
//SC_INLINE int parity64(uint64_t value) { return __builtin_parityll(value); }

#endif

#endif /* __WBC_MATH_H__ */
