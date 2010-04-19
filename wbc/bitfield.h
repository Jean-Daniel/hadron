/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Bitfield manipulation functions.
*/

#if !defined(__WBC_BITFIELDS_H__)
#define __WBC_BITFIELDS_H__ 1

#pragma mark Bitfields
/* Bit manipulation macros */
/* Bits are numbered from 31/63 on left to 0 on right */
/* May or may not work if you use them on bitfields in types other than NSUInteger, bitfields the full width of a NSUInteger, or anything else for which they were not designed. */
/* In the following, N1 and N2 specify an inclusive range N2..N1 with N1 >= N2 */
WB_INLINE
uint64_t WBBitfieldMask64(uint64_t n1, uint64_t n2) {
  assert(n1 < 64 && n2 < 64);
  return (((uint64_t)~0) << ((uint64_t)63 - n1 + n2)) >> (63 - n1);
}
WB_INLINE
uint64_t WBBitfieldMask32(uint32_t n1, uint32_t n2) {
  assert(n1 < 32 && n2 < 32);
  return (((uint32_t)~0) << ((uint32_t)31 - n1 + n2)) >> (31 - n1);
}

WB_INLINE
uint64_t WBBitfieldGetValue64(uint64_t bitfield, uint32_t n1, uint32_t n2) {
  return (bitfield & WBBitfieldMask64(n1, n2)) >> n2;
}
WB_INLINE
uint32_t WBBitfieldGetValue32(uint32_t bitfield, uint32_t n1, uint32_t n2) {
  return (uint32_t)((bitfield & WBBitfieldMask32(n1, n2)) >> n2);
}

WB_INLINE
uint64_t WBBitfieldGetMaxValue64(uint32_t n1, uint32_t n2) {
  return WBBitfieldGetValue64(UINT64_MAX, n1, n2);
}
WB_INLINE
uint32_t WBBitfieldGetMaxValue32(uint32_t n1, uint32_t n2) {
  return WBBitfieldGetValue32(UINT32_MAX, n1, n2);
}

WB_INLINE
uint64_t WBBitfieldSetMaxValue64(uint64_t *bitfield, uint64_t value, uint32_t n1, uint32_t n2) {
  return *bitfield = (*bitfield & ~WBBitfieldMask64(n1, n2)) | ((value << n2) & WBBitfieldMask64(n1, n2));
}
WB_INLINE
uint32_t WBBitfieldSetMaxValue32(uint32_t *bitfield, uint32_t value, uint32_t n1, uint32_t n2) {
  return *bitfield = (uint32_t)((*bitfield & ~WBBitfieldMask32(n1, n2)) | ((value << n2) & WBBitfieldMask32(n1, n2)));
}

WB_INLINE
void WBBitSet64(uint64_t *value, uint32_t n) {
  assert(value && n < 64);
  *value |= ((uint64_t)1 << n);
}
WB_INLINE
void WBBitSet32(uint32_t *value, uint32_t n) {
  assert(value && n < 32);
  *value |= ((uint32_t)1 << n);
}

WB_INLINE
void WBBitClear64(uint64_t *value, uint32_t n) {
  assert(value && n < 64);
  *value &= ~((uint64_t)1 << n);
}
WB_INLINE
void WBBitClear32(uint32_t *value, uint32_t n) {
  assert(value && n < 32);
  *value &= ~((uint32_t)1 << n);
}

WB_INLINE
bool WBBitIsSet64(uint64_t value, uint32_t n) {
  assert(n < 64);
  return (value & ((uint64_t)1 << n)) != 0;
}
WB_INLINE
bool WBBitIsSet32(uint32_t value, uint32_t n) {
  assert(n < 32);
  return (value & ((uint32_t)1 << n)) != 0;
}

/* Use to set a boolean value in a bitfield */
#define WBFlagSet(field, value)	do { field = ((value) != 0) ? 1 : 0; } while (0)
#define WBFlagTestAndSet(field, value) ({ bool __old = field; field = ((value) != 0) ? 1 : 0; __old; })

#endif /* __WBC_BITFIELDS_H__ */
