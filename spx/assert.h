/*
 *  assert.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Assertion and Exception macros
*/

#if defined(_MSC_VER)
  #define spx_likely(x)    (x)
  #define spx_unlikely(x)  (x)
#else
  #define spx_likely(x)    __builtin_expect((x), 1)
  #define spx_unlikely(x)  __builtin_expect((x), 0)
#endif

static SPX_NORETURN inline
void _spx_abort(const char *msg, const char *file, uint32_t line) {
	printf("%s:%u: failed assertion `%s'\n", __FILE__, __LINE__, msg);
	abort();
#if defined(_WIN32)
	_exit(3); // abort is not marked as no return in Windows.
#endif
}
/*!
 @defined spx_abort(str)
 @abstract An abort() like function that prints a message before aborting.
 */
#define spx_abort(msg) _spx_abort(msg, __FILE__, __LINE__)

/*!
 @defined static_assert(test, str)
 @abstract define a static_assert() replacement in case the compiler does not support it.
 */
#if __has_extension(c_static_assert)
// We are in C11 mode, or something compatible. static_assert may already be defined.
  #if !__has_extension(cxx_static_assert) && !defined(static_assert)
    #define static_assert(test, msg)  _Static_assert(test, msg)
  #endif
#elif !defined(__cplusplus) || !__has_extension(cxx_static_assert)
  // We got this technique from here:
  // http://unixjunkie.blogspot.com/2007/10/better-compile-time-asserts_29.html
  #define _spx_static_assert_symbol_inner(line) __spx_STATIC_ASSERT ## line
  #define _spx_static_assert_symbol(line) _spx_static_assert_symbol_inner(line)

  #define static_assert(test, msg) typedef char _spx_static_assert_symbol(__LINE__) [ ((test) ? 1 : -1) ]
#endif

// MARK: Assertion

#define spx_unreachable(msg) spx_abort(msg)

/*!
 @define spx_assert(test, message)
 @abstract an assert() like macro, but that require a message string argument.
 */
#ifdef NDEBUG
#  define spx_assert(assertion, message) ((void)0)
#else
#  define spx_assert(assertion, message) \
    do { \
     if (spx_unlikely(!(assertion))) \
      spx_abort("assertion failed (" #assertion ") : " message); \
    } while (0)
#endif

#if defined (__OBJC__)

// Workaround bug in NSAssert which ignored varidiacs macros in c++
#if !defined(__STDC_VERSION__) && !defined(NS_BLOCK_ASSERTIONS) && defined(NSAssert)
#  undef NSAssert
#  define NSAssert(condition, desc, ...) \
  do { \
    if (spx_unlikely(!(condition))) { \
      [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd \
            object:self file:[NSString stringWithUTF8String:__FILE__] \
              lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
    } \
  } while(0)

#  undef NSParameterAssert
#  define NSParameterAssert(condition) NSAssert((condition), @"Invalid parameter not satisfying: %s", #condition)

#  undef NSCAssert
#  define NSCAssert(condition, desc, ...) \
  do { \
    if (spx_unlikely(!(condition))) { \
      [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                                                              file:[NSString stringWithUTF8String:__FILE__] \
                                                        lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
    } \
  } while(0)

#  undef NSCParameterAssert
#  define NSCParameterAssert(condition) NSCAssert((condition), @"Invalid parameter not satisfying: %s", #condition)
#endif

// Workaround bug in SDK. NSAssert is defined variadic when assertion enabled, and not variadic when disabled.
#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_7 && defined(NS_BLOCK_ASSERTIONS)
#  if defined(NSAssert)
#    undef NSAssert
#    define NSAssert(...)
#  endif

#  if defined(NSCAssert)
#    undef NSCAssert
#    define NSCAssert(...)
#  endif
#endif

// MARK: Objective-C Exceptions
SPX_INLINE SPX_NORETURN SPX_NS_FORMAT(3, 0)
void SPXThrowExceptionWithInfov(NSString *name, NSDictionary *userInfo, NSString *fmt, va_list args)  {
  NSString *str = [[NSString alloc] initWithFormat:fmt arguments:args];
  @throw [NSException exceptionWithName:name reason:spx_autorelease(str) userInfo:userInfo];
}

//SPX_INLINE __attribute__((__noreturn__))
//void SPXThrowExceptionWithInfo(NSString *name, NSDictionary *userInfo, NSString *fmt, ...)
#define SPXThrowExceptionWithInfo(name, info, fmt, ...) \
  @throw [NSException exceptionWithName:name reason:[NSString stringWithFormat:fmt, ##__VA_ARGS__] userInfo:info]

//SPX_INLINE __attribute__((__noreturn__))
//void SPXThrowException(NSString *name, NSString *fmt, ...)
#define SPXThrowException(name, fmt, ...) SPXThrowExceptionWithInfo(name, nil, fmt, ##__VA_ARGS__)

/*!
 @defined  SPXAbstractMethodException
 @abstract Raise an invalig argument exception.
 */
#define SPXAbstractMethodException()    SPXThrowException(NSInvalidArgumentException, \
                                                          @"-%@ only defined for abstract class. Define -[%@ %@]!", \
                                                          NSStringFromSelector(_cmd), NSStringFromClass([self class]), NSStringFromSelector(_cmd))

#endif /* __OBJC__ */
