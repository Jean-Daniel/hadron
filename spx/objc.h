/*
 *  objc.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Obj-C Specifics macros
*/

#if !defined(__OBJC__)
  #error This file requires Objective-C
#endif

#if !__has_feature(objc_arc)
/* Objective-C ARC keywords */
  #if !defined(__bridge)
    #define __bridge
  #endif
  #if !defined(__bridge_retain)
    #define __bridge_retain
  #endif
  #if !defined(__bridge_retained)
    #define __bridge_retained
  #endif
  #if !defined(__bridge_transfer)
    #define __bridge_transfer
  #endif
  #if !defined(__autoreleased)
    #define __autoreleased
  #endif
  #if !defined(__unsafe_unretained)
    #define __unsafe_unretained
  #endif
#endif

#if defined(__cplusplus)

#include <memory>

template<class Ty, class X>
SPX_INLINE Ty bridge_cast(X value) {
    return (__bridge Ty)value;
}

namespace spx {

  struct hash {
    template<class T>
    inline
    size_t operator()(T __v) const noexcept
    {
      std::hash<void *> _hasher;
      return _hasher(bridge_cast<void *>(__v));
    }
  };
}

#endif

/* Hybrid mode */
#if __has_feature(objc_arc)
  #define spx_retain(arg) arg
  #define spx_release(arg) do {} while(0)
  #define spx_autorelease(arg) arg
#else
  #define spx_retain(arg) [arg retain]
  #define spx_release(arg) [arg release]
  #define spx_autorelease(arg) [arg autorelease]
#endif

// Define this when using string in KVC to make the compiler generating
// warning if the property does not exists. This macro does not works for BOOL property
// does not check for setter, and may find a selector with the same name in an other class,
// but sometimes it helps catching typo in property names.
#if DEBUG
  #define SPXProperty(propName)    NSStringFromSelector(@selector(propName))
#else
  #define SPXProperty(propName)    @#propName
#endif

// MARK: Accessors
/* For safety we retain var before releasing ivar (ivar can contain the last reference on var). */
#if !__has_feature(objc_arc)
#define SPXSetterRetainAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    [__var retain]; \
    [ivar release]; \
    ivar = __var; \
    statement; \
  } \
} while (0)

/* For safety we copy var before releasing ivar (ivar can contain the last reference on var). */
#define SPXSetterCopyAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    __var = [__var copyWithZone:nil]; \
    [ivar release]; \
    ivar = __var; \
    statement; \
  } \
} while (0)

#define SPXSetterMutableCopyAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    __var = [__var mutableCopyWithZone:nil]; \
    [ivar release]; \
    ivar = __var; \
    statement; \
  } \
} while (0)

#else

/* ARC Compliant macros */
#define SPXSetterRetainAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    ivar = __var; \
    statement; \
  } \
} while (0)

#define SPXSetterCopyAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    ivar = [__var copyWithZone:nil]; \
    statement; \
  } \
} while (0)

#define SPXSetterMutableCopyAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    ivar = [__var mutableCopyWithZone:nil]; \
    statement; \
  } \
} while (0)

#endif

#define SPXSetterCopy(ivar, var) SPXSetterCopyAndDo(ivar, var, do {} while(0))
#define SPXSetterRetain(ivar, var) SPXSetterRetainAndDo(ivar, var, do {} while(0))
#define SPXSetterMutableCopy(ivar, var) SPXSetterMutableCopyAndDo(ivar, var, do {} while(0))

#if 0 // .Hack relying on implementation details.
// MARK: Atomic Variants
//extern id objc_getProperty(id self, SEL _cmd, ptrdiff_t offset, BOOL atomic);
//extern void objc_copyStruct(void *dest, const void *src, ptrdiff_t size, BOOL atomic, BOOL hasStrong);
SPX_EXTERN void objc_setProperty(id self, SEL _cmd, ptrdiff_t offset, id newValue, BOOL atomic, BOOL shouldCopy);

#define SPXSetterCopyAtomic(ivar, var) \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, 1)

// Hack, see runtime source (use OBJC_PROPERTY_MUTABLECOPY as shouldCopy arg)
#define SPXSetterMutableCopyAtomic(ivar, var) \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, 2)

#define SPXSetterRetainAtomic(ivar, var) \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, NO)

#endif //.Hack

// MARK: Key Value Observing Helper
#define SPXKeyValueObserverContext(name) \
	static void * const name = (void *)&name;

// MARK: Delegate
SPX_INLINE bool __SPXDelegateHandle(id<NSObject> delegate, SEL method) { return delegate && [delegate respondsToSelector:method]; }
/*!
 @defined SPXDelegateHandle
 @abstract Check if delegate implements a method
 @param delegate The Delegate to register.
 @param method	method name
 */
#define SPXDelegateHandle(delegate, method) __SPXDelegateHandle(delegate, @selector(method))

/*!
 @defined SPXDelegateRegisterNotification
 @abstract   Used to register a delegate.
 @param		obj	The Delegate to register.
 @param		sel	The selector the notification need called.
 @param		notif The notification name.
 */
#define SPXDelegateRegisterNotification(obj, sel, notif) do { \
  if ([obj respondsToSelector:sel])	\
    [[NSNotificationCenter defaultCenter] addObserver:obj selector:sel name:notif object:self]; \
} while (0)

#define SPXDelegateUnregisterNotification(obj, sel, notif)	do { \
  if ([obj respondsToSelector:sel]) \
    [[NSNotificationCenter defaultCenter] removeObserver:obj name:notif object:self]; \
} while (0)

// MARK: NSBundle
/*!
 @result   Returns the bundle for the caller class.
 */
#define SPXCurrentBundle()         [NSBundle bundleForClass:[self class]]
/*!
 @param	aClass wrapper on bundleForClass:
 @result Returns the bundle for aClass.
 */
#define SPXBundleForClass(aClass)  [NSBundle bundleForClass:[aClass class]]

// MARK: NSIndexSet
SPX_INLINE
NSIndexSet *SPXIndexesForCount(NSUInteger count) { return [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, count)]; }
SPX_INLINE
NSIndexSet *SPXIndexesForArray(NSArray *anArray) { return SPXIndexesForCount([anArray count]); }
