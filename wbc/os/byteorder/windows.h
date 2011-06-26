/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */

#if !defined(__WBC_OS_WINDOWS_BYTEORDER_H)
#define __WBC_OS_WINDOWS_BYTEORDER_H 1

/* Windows byte swapping builtin */
#define OSSwapInt16(x)	_byteswap_ushort(x)
#define OSSwapInt32(x)	_byteswap_ulong(x)
#define OSSwapInt64(x)	_byteswap_uint64(x)

#define OSSwapConstInt16(x)	_byteswap_ushort(x)
#define OSSwapConstInt32(x)	_byteswap_ulong(x)
#define OSSwapConstInt64(x)	_byteswap_uint64(x)

#endif /* __WBC_OS_WINDOWS_BYTEORDER_H */
