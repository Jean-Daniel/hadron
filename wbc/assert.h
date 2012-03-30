/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Assertion and Exception macros
*/

#if !defined(__WBC_ASSERT_H__)
#define __WBC_ASSERT_H__ 1

#if defined(_MSC_VER)
  #define wb_likely(x)    (x)
  #define wb_unlikely(x)  (x)
#else
  #define wb_likely(x)    __builtin_expect((x), 1)
  #define wb_unlikely(x)  __builtin_expect((x), 0)
#endif

static SC_NORETURN inline
void _wb_abort(const char *msg, const char *file, uint32_t line) {
	printf("%s:%u: failed assertion `%s'\n", __FILE__, __LINE__, msg);
	abort();
#if defined(_WIN32)
	_exit(3); // abort is not marked as no return in Windows.
#endif
}
#define wb_abort(msg) _wb_abort(msg, __FILE__, __LINE__)

#if __has_extension(__c_static_assert__)
// We are in C11 mode, or something compatible. static_assert may already be defined.
  #if !defined(static_assert)
    #define static_assert(test, msg)  _Static_assert(test, msg)
  #endif
#elif !defined(__cplusplus) || !__has_extension(__cxx_static_assert__)
  // We got this technique from here:
  // http://unixjunkie.blogspot.com/2007/10/better-compile-time-asserts_29.html
  #define _SCStaticAssertSymbolInner(line) __SC_STATIC_ASSERT ## line
  #define _SCStaticAssertSymbol(line) _SCStaticAssertSymbolInner(line)

  #define static_assert(test, msg) typedef char _SCStaticAssertSymbol(__LINE__) [ ((test) ? 1 : -1) ]
#endif

// Assert
#if DEBUG_ASSERT_PRODUCTION_CODE || defined(_WIN32)
  #define WBCAssert(assertion, message) do { } while (0)
#else
  #define WBCAssert(assertion, message) \
  do { \
    if (wb_unlikely(!(assertion))) { \
      DEBUG_ASSERT_MESSAGE( \
        DEBUG_ASSERT_COMPONENT_NAME_STRING, \
        #assertion, 0, message, __FILE__, __LINE__, 0); \
    } \
  } while (0)
#endif /* DEBUG_ASSERT_PRODUCTION_CODE */

#if DEBUG_ASSERT_PRODUCTION_CODE
  #define WBUnreachable(msg) do { } while (0)
#else
  #define WBUnreachable(msg) WBCAssert(false, msg)
#endif

#if defined (__OBJC__)

// Workaround bug in NSAssert which ignored varidiacs macros in c++
#if !defined(__STDC_VERSION__) && !defined(NS_BLOCK_ASSERTIONS) && defined(NSAssert)
#undef NSAssert
#define NSAssert(condition, desc, ...) \
do { \
  if (!(condition)) { \
    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd \
          object:self file:[NSString stringWithUTF8String:__FILE__] \
            lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
  } \
} while(0)

#undef NSParameterAssert
#define NSParameterAssert(condition) NSAssert((condition), @"Invalid parameter not satisfying: %s", #condition)

#undef NSCAssert
#define NSCAssert(condition, desc, ...) \
do { \
  if (!(condition)) { \
    [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                                                            file:[NSString stringWithUTF8String:__FILE__] \
                                                      lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
  } \
} while(0)

#undef NSCParameterAssert
#define NSCParameterAssert(condition) NSCAssert((condition), @"Invalid parameter not satisfying: %s", #condition)
#endif

// Workaround bug in SDK. NSAssert is defined variadic when assertion enabled, and not variadic when disabled.
#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_7 && defined(NS_BLOCK_ASSERTIONS) && defined(NSAssert)
  #undef NSAssert
  #define NSAssert(...)
#endif

// MARK: Generic Macros
SC_INLINE SC_NORETURN
void WBThrowExceptionWithInfov(NSString *name, NSDictionary *userInfo, NSString *fmt, va_list args)  {
  NSString *str = [[NSString alloc] initWithFormat:fmt arguments:args];
  NSException *except = [NSException exceptionWithName:name reason:wb_autorelease(str) userInfo:userInfo];
#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5
  @throw except;
#else
  [except raise];
  abort(); // workaround lack of noreturn attribute in raise.
#endif
}

//SC_INLINE __attribute__((__noreturn__))
//void WBThrowExceptionWithInfo(NSString *name, NSDictionary *userInfo, NSString *fmt, ...)
#define WBThrowExceptionWithInfo(name, info, fmt, args...) \
  @throw [NSException exceptionWithName:name reason:[NSString stringWithFormat:fmt, ##args] userInfo:info]

//SC_INLINE __attribute__((__noreturn__))
//void WBThrowException(NSString *name, NSString *fmt, ...)
#define WBThrowException(name, fmt, args...) WBThrowExceptionWithInfo(name, nil, fmt, ##args)

/*!
 @defined  WBAbstractMethodException
 @abstract Raise an invalig argument exception.
 */
#define WBAbstractMethodException()    WBThrowException(NSInvalidArgumentException, \
                                                        @"-%@ only defined for abstract class. Define -[%@ %@]!", \
                                                        NSStringFromSelector(_cmd), NSStringFromClass([self class]), NSStringFromSelector(_cmd))

#endif /* __OBJC__ */

#endif /* __WBC_ASSERT_H__ */
