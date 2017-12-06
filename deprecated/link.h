/*
 *  link.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Linker Function
 */

/* Usage:
 SPX_INITIALIZER(initialize)
 {
 // Initilization Code
 }
 */
#ifdef _MSC_VER
  /* Initializer */
#  pragma section(".CRT$XCU",long,read)
#  define SPX_INITIALIZER(f) \
    static void __cdecl f(void); \
    __declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
    static void __cdecl f(void)
  /* Terminators */
#  pragma section(".CRT$XTU",long,read)
#  define SPX_TERMINATOR(f) \
     static void __cdecl f(void); \
     __declspec(allocate(".CRT$XTU")) void (__cdecl*f##_)(void) = f; \
     static void __cdecl f(void)

#elif defined(__clang__) || defined(__GNUC__)

   /* Initializer */
#  define SPX_INITIALIZER(f) \
     static void f(void) __attribute__((constructor)); \
     static void f(void)
   /* Terminators */
#  define SPX_TERMINATOR(f) \
     static void f(void) __attribute__((destructor)); \
     static void f(void)

#else
#  error Compiler not supported
#endif

#if defined(__APPLE__)

/*
 *  Example:
 *
 *  static
 *  int
 *  my_open(const char* path, int flags, mode_t mode)
 *  {
 *    int value;
 *    // do stuff before open (including changing the arguments)
 *    value = open(path, flags, mode);
 *    // do stuff after open (including changing the return value(s))
 *    return value;
 *  }
 *  SPX_DYLD_INTERPOSE(my_open, open)
 */

#  define SPX_DYLD_INTERPOSE(_replacement,_replacee) \
     __attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
     __attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };

#endif
