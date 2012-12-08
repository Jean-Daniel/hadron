/*
 *  core.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */

#if defined(__cplusplus) && !defined(__STDC_LIMIT_MACROS)
  #define __STDC_LIMIT_MACROS
#endif

#ifdef _MSC_VER
  #if !defined(__cplusplus)
    // C support in MSVC is badly broken
    #error Broken C Compiler. Use C++ if you want to use it.
  #endif

  #if defined(_M_IX86) && !defined(__i386__)
    #define __i386__ 1
  #endif

  #if (defined(_M_AMD64) || defined(_M_X64)) && !defined(__x86_64__)
    #define __x86_64__ 1
  #endif

  // Symbols visibilities
  #pragma warning(disable:4251)

  #define __PRETTY_FUNCTION__ __FUNCSIG__

  #if !defined(__thread)
    #define __thread declspec(thread)
  #endif
#endif

#define NOMINMAX // avoid declaration of min() max() macros which conflicts with c++ functions

#ifndef SC_WIN32_FULL
  #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#endif

// MARK: System Include
// If you wish to build your application for a previous Windows platform,
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#ifndef _WIN32_WINNT
  #define _WIN32_WINNT 0x501 // Target WinXP by default
#endif
#include <SDKDDKVer.h>

#include <tchar.h>
#include <windows.h>

#if defined(SC_INCLUDE_CORE_FOUNDATION_H)
  #include <CoreFoundation\CoreFoundation.h>
#else

#include <assert.h>

// FIXME: Windows headers
#include <sys/types.h>
#include <stdarg.h>
#include <conio.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)
  #if defined(__i386__) || defined(__x86_64__) || defined(_M_AMD64) || defined(_M_IX86) || defined(_M_X64)
    #define __LITTLE_ENDIAN__ 1
  #elif defined(__ppc__) || defined(_M_PPC)
    #define __BIG_ENDIAN__ 1
  #endif
#endif

typedef double CFTimeInterval;
typedef double CFAbsoluteTime;

#endif

// Missing types
#include "libc.h"
#include "stdbool.h"
