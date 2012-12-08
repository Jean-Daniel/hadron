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

/* Hybrid mode */
#if __has_feature(objc_arc)
  #define spx_dealloc() do {} while(0)
  #define spx_retain(arg) arg
  #define spx_release(arg) do {} while(0)
  #define spx_autorelease(arg) arg
#else
  #define spx_dealloc() [super dealloc]
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

// MARK: Delegate
/*!
 @defined SPXDelegateHandle
 @abstract Check if delegate implements a method
 @param delegate The Delegate to register.
 @param method	method name
 */
SPX_INLINE bool __SPXDelegateHandle(id<NSObject> delegate, SEL method) { return delegate && [delegate respondsToSelector:method]; }
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

// MARK: NSNumber
SPX_INLINE
NSNumber* SPXBool(BOOL value) { return [NSNumber numberWithBool:value]; }

#define SPXChar SPXInt8
#define SPXUChar SPXUInt8
#define SPXShort SPXInt16
#define SPXUShort SPXUInt16

SPX_INLINE
NSNumber* SPXInt8(int8_t value) { return [NSNumber numberWithChar:value]; }
SPX_INLINE
NSNumber* SPXUInt8(uint8_t value) { return [NSNumber numberWithUnsignedChar:value]; }

SPX_INLINE
NSNumber* SPXInt16(int16_t value) { return [NSNumber numberWithShort:value]; }
SPX_INLINE
NSNumber* SPXUInt16(uint16_t value) { return [NSNumber numberWithUnsignedShort:value]; }

SPX_INLINE
NSNumber* SPXInt32(int32_t value) { return [NSNumber numberWithInt:value]; }
SPX_INLINE
NSNumber* SPXUInt32(uint32_t value) { return [NSNumber numberWithUnsignedInt:value]; }

#if __LP64__
SPX_INLINE
NSNumber* SPXInt64(int64_t value) { return [NSNumber numberWithLong:value]; }
SPX_INLINE
NSNumber* SPXUInt64(uint64_t value) { return [NSNumber numberWithUnsignedLong:value]; }
#else
SPX_INLINE
NSNumber* SPXInt64(int64_t value) { return [NSNumber numberWithLongLong:value]; }
SPX_INLINE
NSNumber* SPXUInt64(uint64_t value) { return [NSNumber numberWithUnsignedLongLong:value]; }
#endif

#if __LP64__
SPX_INLINE
CGFloat SPXCGFloatValue(id value) { return value ? [value doubleValue] : 0; }
SPX_INLINE
NSNumber* SPXCGFloat(CGFloat value) { return [NSNumber numberWithDouble:value]; }
#else
SPX_INLINE
CGFloat SPXCGFloatValue(id value) { return value ? [value floatValue] : 0; }
SPX_INLINE
NSNumber* SPXCGFloat(CGFloat value) { return [NSNumber numberWithFloat:value]; }
#endif

SPX_INLINE
NSNumber* SPXFloat(float value) { return [NSNumber numberWithFloat:value]; }
SPX_INLINE
NSNumber* SPXDouble(double value) { return [NSNumber numberWithDouble:value]; }

SPX_INLINE
NSNumber* SPXInteger(NSInteger value) { return [NSNumber numberWithInteger:value]; }
SPX_INLINE
NSNumber* SPXUInteger(NSUInteger value) { return [NSNumber numberWithUnsignedInteger:value]; }

