/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Bitfield manipulation functions.
*/

#if !defined(__WBC_BITFIELDS_H__)
#define __WBC_BITFIELDS_H__ 1

// MARK: Bitfields
/* Bit manipulation macros */
/* Bits are numbered from 31/63 on left to 0 on right */
/* May or may not work if you use them on bitfields in types other than NSUInteger, bitfields the full width of a NSUInteger, or anything else for which they were not designed. */
/* In the following, N1 and N2 specify an inclusive range N2..N1 with N1 >= N2 */
SC_INLINE
uint64_t WBBitfieldMask64(uint64_t n1, uint64_t n2) {
  assert(n1 < 64 && n2 < 64);
  return (((uint64_t)~0) << ((uint64_t)63 - n1 + n2)) >> (63 - n1);
}
SC_INLINE
uint64_t WBBitfieldMask32(uint32_t n1, uint32_t n2) {
  assert(n1 < 32 && n2 < 32);
  return (((uint32_t)~0) << ((uint32_t)31 - n1 + n2)) >> (31 - n1);
}

SC_INLINE
uint64_t WBBitfieldGetValue64(uint64_t bitfield, uint32_t n1, uint32_t n2) {
  return (bitfield & WBBitfieldMask64(n1, n2)) >> n2;
}
SC_INLINE
uint32_t WBBitfieldGetValue32(uint32_t bitfield, uint32_t n1, uint32_t n2) {
  return (uint32_t)((bitfield & WBBitfieldMask32(n1, n2)) >> n2);
}

SC_INLINE
uint64_t WBBitfieldGetMaxValue64(uint32_t n1, uint32_t n2) {
  return WBBitfieldGetValue64(UINT64_MAX, n1, n2);
}
SC_INLINE
uint32_t WBBitfieldGetMaxValue32(uint32_t n1, uint32_t n2) {
  return WBBitfieldGetValue32(UINT32_MAX, n1, n2);
}

SC_INLINE
uint64_t WBBitfieldSetMaxValue64(uint64_t *bitfield, uint64_t value, uint32_t n1, uint32_t n2) {
  return *bitfield = (*bitfield & ~WBBitfieldMask64(n1, n2)) | ((value << n2) & WBBitfieldMask64(n1, n2));
}
SC_INLINE
uint32_t WBBitfieldSetMaxValue32(uint32_t *bitfield, uint32_t value, uint32_t n1, uint32_t n2) {
  return *bitfield = (uint32_t)((*bitfield & ~WBBitfieldMask32(n1, n2)) | ((value << n2) & WBBitfieldMask32(n1, n2)));
}

SC_INLINE
void WBBitSet64(uint64_t *value, uint32_t n) {
  assert(value && n < 64);
  *value |= ((uint64_t)1 << n);
}
SC_INLINE
void WBBitSet32(uint32_t *value, uint32_t n) {
  assert(value && n < 32);
  *value |= ((uint32_t)1 << n);
}

SC_INLINE
void WBBitClear64(uint64_t *value, uint32_t n) {
  assert(value && n < 64);
  *value &= ~((uint64_t)1 << n);
}
SC_INLINE
void WBBitClear32(uint32_t *value, uint32_t n) {
  assert(value && n < 32);
  *value &= ~((uint32_t)1 << n);
}

SC_INLINE
bool WBBitIsSet64(uint64_t value, uint32_t n) {
  assert(n < 64);
  return (value & ((uint64_t)1 << n)) != 0;
}
SC_INLINE
bool WBBitIsSet32(uint32_t value, uint32_t n) {
  assert(n < 32);
  return (value & ((uint32_t)1 << n)) != 0;
}

/* Use to set a boolean value in a bitfield */
#define WBFlagSet(field, value)	field = ((value) != 0) ? 1 : 0
#define WBFlagTestAndSet(field, value) ({ bool __old = field; field = ((value) != 0) ? 1 : 0; __old; })

// MARK: -
// MARK: Bit maths
#if defined(_MSC_VER)

// FIXME: unsafe on hardware that do not support it.
// SC_INLINE int popcnt32(uint32_t value) { return __popcnt(value); }
// SC_INLINE int popcnt64(uint64_t value) { return __popcnt64(value); }

static inline int popcount32(uint32_t x) {
	static const uint32_t m1 = 0x55555555; //binary: 0101...
	static const uint32_t m2 = 0x33333333; //binary: 00110011..
	static const uint32_t m4 = 0x0f0f0f0f; //binary:  4 zeros,  4 ones ...
	static const uint32_t h01= 0x01010101; //the sum of 256 to the power of 0,1,2,3...
	x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
  x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
  x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits
  return (x * h01) >> 24;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24)
}

static inline int popcount64(uint64_t x) {
	static const uint64_t m1  = 0x5555555555555555; //binary: 0101...
	static const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
	static const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
	static const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...
	x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
  x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
  x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits
  return (x * h01)>>56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
}

#if !defined(_WIN64)
static inline int _BitScanForward64(unsigned long *idx, uint64_t value) {
	if (_BitScanForward(idx, value & 0xffffffff))
		return 1;
	if (_BitScanForward(idx, value >> 32)) {
		*idx += 32;
		return 1;
	}
	return 0;
}

static inline int _BitScanReverse64(unsigned long *idx, uint64_t value) {
	if (_BitScanReverse(idx, value >> 32))
		return 1;
	if (_BitScanReverse(idx, value & 0xffffffff)) {
		*idx += 32;
		return 1;
	}
	return 0;
}
#endif

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

static __inline int ctz32(uint32_t value) {
  unsigned long idx; // do not init to match undefined behavior of GCC
  _BitScanForward(&idx, value);
  return idx;
}
static __inline int ctz64(uint64_t value) {
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
SC_INLINE int popcount32(uint32_t value) { return __builtin_popcount(value); }
SC_INLINE int popcount64(uint64_t value) { return __builtin_popcountll(value); }

// Count Leading Zeros (left)
// returns 0 based index. If value zero, result is undefined.
SC_INLINE int clz32(uint32_t value) { return __builtin_clz(value); }
SC_INLINE int clz64(uint64_t value) { return __builtin_clzll(value); }
// returns 1 based index. If value is 0, returns 0.
SC_INLINE int fls32(uint32_t value) { return value ? __builtin_clz(value) + 1 : 0; }
SC_INLINE int fls64(uint64_t value) { return value ? __builtin_clzll(value) + 1 : 0; }

// Count Trailing Zeros (right)
// returns 0 based index. If value zero, result is undefined.
SC_INLINE int ctz32(uint32_t value) { return __builtin_ctz(value); }
SC_INLINE int ctz64(uint64_t value) { return __builtin_ctzll(value); }
// returns 1 based index. If value is 0, returns 0.
SC_INLINE int ffs32(uint32_t value) { return __builtin_ffs(value); }
SC_INLINE int ffs64(uint64_t value) { return __builtin_ffsll(value); }

// Returns the parity of value, i.e. the number of 1-bits in x modulo 2.
//SC_INLINE int parity32(uint32_t value) { return __builtin_parity(value); }
//SC_INLINE int parity64(uint64_t value) { return __builtin_parityll(value); }

#endif

// MARK: Bit Hacks
/*
 min/max: r = (x < y) ? x : y; -> r = y ^ ((x ^ y) & -(x < y))
 Note: -(x < y) is -1 or 0, so the expression is either (y ^ x ^ y), or (y ^ 0).

 (x + y) mod n when 0 <= x < n and 0 <= y < n:
 t = x + y
 r = t - (n & -(t >= n))

 // Bit set
 bool f;         // conditional flag
 unsigned int m; // the bit mask
 unsigned int w; // the word to modify:  if (f) w |= m; else w &= ~m;
 w ^= (-f ^ w) & m;
 // OR, for superscalar CPUs:
 w = (w & ~m) | (-f & m);

 // round n to next power of 2.
 n--; // 001xxxxxxxxxxxxx
 n |= n >> 1;  // 0011xxxxxxxxxxxx
 n |= n >> 2;  // 001111xxxxxxxxxx
 n |= n >> 4;  // 0011111111xxxxxx
 n |= n >> 8;  // …
 n |= n >> 16; // …
 n |= n >> 32;  (for 64 bits only)
 n++; // 0100000000000000
 */

#endif /* __WBC_BITFIELDS_H__ */
