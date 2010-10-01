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
  return x <= -0x1p31f ? (int32_t)-0x80000000 : 0x1p31f <= x ? (int32_t)0x7fffffff : (int32_t)x;
}
SC_INLINE
Fixed WBFloatToFixed(double aFloat) { return WBIntSaturate(aFloat * fixed1); }
SC_INLINE
double WBFixedToFloat(Fixed aValue) { return (double)aValue / fixed1; }

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

// MARK: Math Macros
#if defined(__clang__) || defined(__cplusplus)
// Clang use a special attribute to make a function overloadable (like C++),
// so we can merge C++ definitions with clang C definitions.

#if defined(__cplusplus)
  #define __SC_CLANG_TG_DECL(type) static inline type __attribute__((__always_inline__))
#else
  #define __SC_CLANG_TG_DECL(type) static __inline__ type __attribute__((__overloadable__, __always_inline__))
#endif

// Clang TG Math support
__SC_CLANG_TG_DECL(bool) __tg_fequal(float a, float b);
__SC_CLANG_TG_DECL(bool) __tg_fequal(double a, double b);
__SC_CLANG_TG_DECL(bool) __tg_fequal(long double a, long double b);

__SC_CLANG_TG_DECL(bool) __tg_fequal(float a, float b) { float delta = a - b; return (delta <= FLT_EPSILON && delta >= -FLT_EPSILON); }
__SC_CLANG_TG_DECL(bool) __tg_fequal(double a, double b) { double delta = a - b; return (delta <= DBL_EPSILON && delta >= -DBL_EPSILON); }
__SC_CLANG_TG_DECL(bool) __tg_fequal(long double a, long double b) { long double delta = a - b; return (delta <= LDBL_EPSILON && delta >= -LDBL_EPSILON); }

__SC_CLANG_TG_DECL(bool) __tg_fnotequal(float a, float b);
__SC_CLANG_TG_DECL(bool) __tg_fnotequal(double a, double b);
__SC_CLANG_TG_DECL(bool) __tg_fnotequal(long double a, long double b);

__SC_CLANG_TG_DECL(bool) __tg_fnotequal(float a, float b) { return !__tg_fequal(a, b); }
__SC_CLANG_TG_DECL(bool) __tg_fnotequal(double a, double b) { return !__tg_fequal(a, b); }
__SC_CLANG_TG_DECL(bool) __tg_fnotequal(long double a, long double b) { return !__tg_fequal(a, b); }

__SC_CLANG_TG_DECL(bool) __tg_fiszero(float f);
__SC_CLANG_TG_DECL(bool) __tg_fiszero(double f);
__SC_CLANG_TG_DECL(bool) __tg_fiszero(long double f);

__SC_CLANG_TG_DECL(bool) __tg_fiszero(float f) { return __tg_fequal(f, (float)0); }
__SC_CLANG_TG_DECL(bool) __tg_fiszero(double f) { return __tg_fequal(f, (double)0); }
__SC_CLANG_TG_DECL(bool) __tg_fiszero(long double f) { return __tg_fequal(f, (long double)0); }

__SC_CLANG_TG_DECL(bool) __tg_fnonzero(float f);
__SC_CLANG_TG_DECL(bool) __tg_fnonzero(double f);
__SC_CLANG_TG_DECL(bool) __tg_fnonzero(long double f);

__SC_CLANG_TG_DECL(bool) __tg_fnonzero(float f) { return !__tg_fiszero(f); }
__SC_CLANG_TG_DECL(bool) __tg_fnonzero(double f) { return !__tg_fiszero(f); }
__SC_CLANG_TG_DECL(bool) __tg_fnonzero(long double f) { return !__tg_fiszero(f); }

#if defined(__cplusplus)
  #define fiszero(__x)         __tg_fiszero(__x)
  #define fnonzero(__x)        __tg_fnonzero(__x)
  #define fequal(__x, __y)     __tg_fequal(__x, __y)
  #define fnotequal(__x, __y)  __tg_fnotequal(__x, __y)
#else
  #define fiszero(__x)         __tg_fiszero(__tg_promote1((__x))(__x))
  #define fnonzero(__x)        __tg_fnonzero(__tg_promote1((__x))(__x))
  #define fequal(__x, __y)     __tg_fequal(__tg_promote2((__x), (__y))(__x), __tg_promote2((__x), (__y))(__y))
  #define fnotequal(__x, __y)  __tg_fnotequal(__tg_promote2((__x), (__y))(__x), __tg_promote2((__x), (__y))(__y))
#endif

#undef __SC_CLANG_TG_DECL
#else
// GCC TG Math support
SC_INLINE bool __tg_fequalf(float a, float b) { float delta = a - b; return (delta <= FLT_EPSILON && delta >= -FLT_EPSILON); }
SC_INLINE bool __tg_fequal(double a, double b) { double delta = a - b; return (delta <= DBL_EPSILON && delta >= -DBL_EPSILON); }
SC_INLINE bool __tg_fequall(long double a, long double b) { long double delta = a - b; return (delta <= LDBL_EPSILON && delta >= -LDBL_EPSILON); }

SC_INLINE bool __tg_fnotequalf(float a, float b) { return !__tg_fequalf(a, b); }
SC_INLINE bool __tg_fnotequal(double a, double b) { return !__tg_fequal(a, b); }
SC_INLINE bool __tg_fnotequall(long double a, long double b) { return !__tg_fequall(a, b); }

SC_INLINE bool __tg_fiszerof(float f) { return __tg_fequalf(f, 0.f); }
SC_INLINE bool __tg_fiszero(double f) { return __tg_fequal(f, 0.); }
SC_INLINE bool __tg_fiszerol(long double f) { return __tg_fequall(f, 0.); }

SC_INLINE bool __tg_fnonzerof(float f) { return !__tg_fiszerof(f); }
SC_INLINE bool __tg_fnonzero(double f) { return !__tg_fiszero(f); }
SC_INLINE bool __tg_fnonzerol(long double f) { return !__tg_fiszerol(f); }

#define fiszero(x)        __TGMATH_REAL(x, __tg_fiszero)
#define fnonzero(x)       __TGMATH_REAL(x, __tg_fnonzero)
#define fequal(x, y)      __TGMATH_REAL_2(x, y, __tg_fequal)
#define fnotequal(x, y)   __TGMATH_REAL_2(x, y, __tg_fnotequal)

#endif // clang/gcc

#endif /* __WBC_MATH_H__ */
