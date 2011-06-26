/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */

#if !defined(__WBC_OS_GNUC_BYTEORDER_H)
#define __WBC_OS_GNUC_BYTEORDER_H 1

#define OSSwapConstInt16(x)	((uint16_t)((((uint16_t)(x) & 0xff00) >> 8) | \
                            (((uint16_t)(x) & 0x00ff) << 8)))

#define OSSwapConstInt32(x) ((uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) | \
                            (((uint32_t)(x) & 0x00ff0000) >>  8) | \
                            (((uint32_t)(x) & 0x0000ff00) <<  8) | \
                            (((uint32_t)(x) & 0x000000ff) << 24)))

#define OSSwapConstInt64(x) ((uint64_t)((((uint64_t)(x) & 0xff00000000000000ULL) >> 56) | \
                            (((uint64_t)(x) & 0x00ff000000000000ULL) >> 40) | \
                            (((uint64_t)(x) & 0x0000ff0000000000ULL) >> 24) | \
                            (((uint64_t)(x) & 0x000000ff00000000ULL) >>  8) | \
                            (((uint64_t)(x) & 0x00000000ff000000ULL) <<  8) | \
                            (((uint64_t)(x) & 0x0000000000ff0000ULL) << 24) | \
                            (((uint64_t)(x) & 0x000000000000ff00ULL) << 40) | \
                            (((uint64_t)(x) & 0x00000000000000ffULL) << 56)))

/* GCC byte swapping builtin */
OS_INLINE
int16_t OSSwapInt16(int16_t x) { return OSSwapConstInt16(x); }
#define OSSwapInt32(x)	__builtin_bswap32(x)
#define OSSwapInt64(x)	__builtin_bswap64(x)

#endif /* __WBC_OS_GNUC_BYTEORDER_H */
