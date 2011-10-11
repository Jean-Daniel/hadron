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
  #define wb_probable(x)    (x)
  #define wb_improbable(x)  (x)
#else
  #define wb_probable(x)    __builtin_expect((x), 1)
  #define wb_improbable(x)  __builtin_expect((x), 0)
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

#if __has_extension(cxx_static_assert)
  // C++11 static assert supported
  #define WBStaticAssert(test, msg)  static_assert(test, #msg)
#elif __has_extension(c_static_assert)
  // C1x _Static_assert supported
  #define WBStaticAssert(test, msg)  _Static_assert(test, #msg)
#else
  // WBStaticAssert
  // WBStaticAssert is an assert that is meant to fire at Static time if you
  // want to check things at Static instead of runtime. For example if you
  // want to check that a wchar is 4 bytes instead of 2 you would use
  // WBStaticAssert(sizeof(wchar_t) == 4, wchar_t_is_4_bytes_on_OS_X)
  // Note that the second "arg" is not in quotes, and must be a valid processor
  // symbol in it's own right (no spaces, punctuation etc).

  // Wrapping this in an #ifndef allows external groups to define their own Static time assert scheme.
  // We got this technique from here:
  // http://unixjunkie.blogspot.com/2007/10/better-compile-time-asserts_29.html
  #define _WBStaticAssertSymbolInner(line, msg) WBSTATICASSERT ## line ## __ ## msg
  #define _WBStaticAssertSymbol(line, msg) _WBStaticAssertSymbolInner(line, msg)

  #define WBStaticAssert(test, msg) typedef char _WBStaticAssertSymbol(__LINE__, msg) [ ((test) ? 1 : -1) ]
#endif

// Assert
#if DEBUG_ASSERT_PRODUCTION_CODE
  #define WBCAssert(assertion, message) do { } while (0)
#else
  #define WBCAssert(assertion, message) \
  do { \
    if (wb_improbable(!(assertion))) { \
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

// MARK: Assert
// we directly invoke the NSAssert handler so we can pass on the varargs
// (NSAssert doesn't have a macro we can use that takes varargs)
#if !defined(NS_BLOCK_ASSERTIONS)
#define WBAssert(condition, desc, args...) \
do { \
  if (wb_improbable(!(condition))) \
    [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithUTF8String:__func__] \
                                                            file:[NSString stringWithUTF8String:__FILE__ ] \
                                                      lineNumber:__LINE__ \
                                                     description:desc, ##args]; \
  } while(0)
#else // !defined(NS_BLOCK_ASSERTIONS)
  #define WBAssert(condition, ...) do { } while (0)
#endif // !defined(NS_BLOCK_ASSERTIONS)

/*!
 @defined  WBAbstractMethodException
 @abstract Raise an invalig argument exception.
 */
#define WBAbstractMethodException()    WBThrowException(NSInvalidArgumentException, \
                                                        @"-%@ only defined for abstract class. Define -[%@ %@]!", \
                                                        NSStringFromSelector(_cmd), NSStringFromClass([self class]), NSStringFromSelector(_cmd))

#define wb_abstract __attribute__((noreturn))

#endif /* __OBJC__ */

#endif /* __WBC_ASSERT_H__ */
