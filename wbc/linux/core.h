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

#if !defined(__WBC_LINUX_CORE_H__)
#define __WBC_LINUX_CORE_H__ 1

#if defined(SC_INCLUDE_CORE_FOUNDATION_H)
  #include <CoreFoundation/CoreFoundation.h>
#else

/* libc headers */
#include <sys/types.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <fenv.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <pthread.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

/* GCC does not tell us the target endianess, so try to guess it */
#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)
  #if defined(__i386__) || defined(__x86_64__) || defined(__amd64__)
    #define __LITTLE_ENDIAN__ 1
  #elif defined(__ppc__) || defined(__ppc64__)
    #define __BIG_ENDIAN__ 1
  #endif
#endif

typedef double CFTimeInterval;
typedef double CFAbsoluteTime;

/* Rely on libbsd to include missing functions */

// .Hask to avoid bsd/md5.h inclusion. It conflicts with <openSSL/md5.h>
#define _MD5_H_ 1
#include <bsd/bsd.h>

#if defined(__cplusplus)
extern "C" {
#endif

static inline void *reallocf(void *ptr, size_t newSize) {
	void *result = realloc(ptr, newSize);
	if (!result)
		free(ptr);
	return result;
}

#if defined(__cplusplus)
}
#endif

#endif

#endif /* __WBC_WIN32_CORE_H__ */
