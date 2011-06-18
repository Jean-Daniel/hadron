/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @header SharedPrefix
 @abstract Linker Function
 */

#if !defined(__WBC_LINK_H__)
#define __WBC_LINK_H__ 1

/* Usage:
 INITIALIZER(initialize)
 {
 // Initilization Code
 // atexit(finalize); // If destructor needed
 }
 */
#ifdef _MSC_VER
  /* Initializer */
  #pragma section(".CRT$XCU",read)
  #define INITIALIZER(f) \
    static void __cdecl f(void); \
    __declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
    static void __cdecl f(void)

  /* Terminators */
  #pragma section(".CRT$XTU",read)
  #define TERMINATOR(f) \
  static void __cdecl f(void); \
  __declspec(allocate(".CRT$XTU")) void (__cdecl*f##_)(void) = f; \
  static void __cdecl f(void)

#elif defined(__clang__) || defined(__GNUC__)
  /* Initializer */
  #define INITIALIZER(f) \
    static void f(void) __attribute__((constructor)); \
    static void f(void)
  /* Terminators */
  #define TERMINATOR(f) \
    static void f(void) __attribute__((destructor)); \
    static void f(void)
#else
  #error Compiler not supported
#endif

#endif /* __WBC_LINK_H__ */
