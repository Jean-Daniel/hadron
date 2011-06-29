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

#if defined(__cplusplus) && !defined(__STDC_LIMIT_MACROS)
  #define __STDC_LIMIT_MACROS
#endif

#if !defined(SC_EXCLUDE_FRAMEWORK_HEADERS)
  #include <CoreFoundation/CoreFoundation.h>
#else

/* libc headers */
#include <sys/types.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
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

#endif

#endif /* __WBC_WIN32_CORE_H__ */
