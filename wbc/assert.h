/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Assertion and Exception macros
*/

#if !defined(__WBC_ASSERT_H__)
#define __WBC_ASSERT_H__ 1

// WBCompileAssert
// WBCompileAssert is an assert that is meant to fire at compile time if you
// want to check things at compile instead of runtime. For example if you
// want to check that a wchar is 4 bytes instead of 2 you would use
// WBCompileAssert(sizeof(wchar_t) == 4, wchar_t_is_4_bytes_on_OS_X)
// Note that the second "arg" is not in quotes, and must be a valid processor
// symbol in it's own right (no spaces, punctuation etc).

// Wrapping this in an #ifndef allows external groups to define their own compile time assert scheme.
// We got this technique from here:
// http://unixjunkie.blogspot.com/2007/10/better-compile-time-asserts_29.html

#define _WBCompileAssertSymbolInner(line, msg) WBCOMPILEASSERT ## line ## __ ## msg
#define _WBCompileAssertSymbol(line, msg) _WBCompileAssertSymbolInner(line, msg)
#define WBCompileAssert(test, msg) \
    typedef char _WBCompileAssertSymbol(__LINE__, msg) [ ((test) ? 1 : -1) ]


// Assert
#if DEBUG_ASSERT_PRODUCTION_CODE
  #define WBCAssert(assertion, message) do { } while (0)
#else
  #define WBCAssert(assertion, message) \
  do { \
    if (__builtin_expect(!(assertion), 0)) { \
      DEBUG_ASSERT_MESSAGE( \
        DEBUG_ASSERT_COMPONENT_NAME_STRING, \
        #assertion, 0, message, __FILE__, __LINE__, 0); \
    } \
  } while (0)
#endif /* DEBUG_ASSERT_PRODUCTION_CODE */

#if defined (__OBJC__)

#pragma mark Generic Macros

WB_INLINE __attribute__((__noreturn__))
void WBThrowExceptionWithInfov(NSString *name, NSDictionary *userInfo, NSString *fmt, va_list args)  {
  NSString *str = [[NSString alloc] initWithFormat:fmt arguments:args];
  @throw [NSException exceptionWithName:name reason:[str autorelease] userInfo:userInfo];
}

//WB_INLINE __attribute__((__noreturn__))
//void WBThrowExceptionWithInfo(NSString *name, NSDictionary *userInfo, NSString *fmt, ...)
#define WBThrowExceptionWithInfo(name, info, fmt, args...) do { \
  NSString *__str = [[NSString alloc] initWithFormat:fmt, ##args]; \
  @throw [NSException exceptionWithName:name reason:[__str autorelease] userInfo:info]; \
} while (0)

//WB_INLINE __attribute__((__noreturn__))
//void WBThrowException(NSString *name, NSString *fmt, ...)
#define WBThrowException(name, fmt, args...) WBThrowExceptionWithInfo(name, nil, fmt, ##args)

#pragma mark Assert
// we directly invoke the NSAssert handler so we can pass on the varargs
// (NSAssert doesn't have a macro we can use that takes varargs)
#if !defined(NS_BLOCK_ASSERTIONS)
#define WBAssert(condition, desc, args...) \
do { \
  if (__builtin_expect(!(condition), 0)) \
    [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithUTF8String:__func__] \
                                                            file:[NSString stringWithUTF8String:__FILE__ ] \
                                                      lineNumber:__LINE__ \
                                                     description:desc, ##args]; \
  } while(0)
#else // !defined(NS_BLOCK_ASSERTIONS)
  #define WBAssert(condition, ...) do { } while (0)
#endif // !defined(NS_BLOCK_ASSERTIONS)

/*!
 @defined WBClusterException
 @abstract   Raise an invalig argument exception.
 */
#define WBClusterException()    WBThrowException(NSInvalidArgumentException, \
                                                 @"-%@ only defined for abstract class. Define -[%@ %@]!", \
                                                 NSStringFromSelector(_cmd), NSStringFromClass([self class]), NSStringFromSelector(_cmd))

#endif /* __OBJC__ */

#endif /* __WBC_ASSERT_H__ */
