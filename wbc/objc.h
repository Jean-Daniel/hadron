/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Obj-C Specifics macros
*/

#if !defined(__WBC_OBJC_H__)
#define __WBC_OBJC_H__ 1

#if defined (__OBJC__)

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
#if !__has_feature(objc_arc) || __has_feature(objc_arc_weak)
  #define wb_weak __weak
#else
  #define wb_weak __unsafe_unretained
#endif

#if __has_feature(objc_arc)
  #define wb_dealloc() do {} while(0)
  #define wb_retain(arg) arg
  #define wb_release(arg) do {} while(0)
  #define wb_autorelease(arg) arg
#else
  #define wb_dealloc() [super dealloc]
  #define wb_retain(arg) [arg retain]
  #define wb_release(arg) [arg release]
  #define wb_autorelease(arg) [arg autorelease]
#endif

#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
  #define NSIntegerHashCallBacks NSIntHashCallBacks
  #define NSIntegerMapKeyCallBacks NSIntMapKeyCallBacks
  #define NSIntegerMapValueCallBacks NSIntMapValueCallBacks

  #define WBAutoreleasePoolDrain(pool) [pool release]
#else
  #define WBAutoreleasePoolDrain(pool) [pool drain]
#endif

#if DEBUG
  #define WBProperty(propName)    NSStringFromSelector(@selector(propName))
#else
  #define WBProperty(propName)    @#propName
#endif

// MARK: Accessors
/* For safety we retain var before releasing ivar (ivar can contain the last reference on var). */
#if !__has_feature(objc_arc)
#define WBSetterRetainAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    [__var retain]; \
    [ivar release]; \
    ivar = __var; \
    statement; \
  } \
} while (0)

/* For safety we copy var before releasing ivar (ivar can contain the last reference on var). */
#define WBSetterCopyAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    __var = [__var copyWithZone:nil]; \
    [ivar release]; \
    ivar = __var; \
    statement; \
  } \
} while (0)

#define WBSetterMutableCopyAndDo(ivar, var, statement) do { \
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
#define WBSetterRetainAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    ivar = __var; \
    statement; \
  } \
} while (0)

#define WBSetterCopyAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    ivar = [__var copyWithZone:nil]; \
    statement; \
  } \
} while (0)

#define WBSetterMutableCopyAndDo(ivar, var, statement) do { \
  id __var = var; \
  if (ivar != __var) { \
    ivar = [__var mutableCopyWithZone:nil]; \
    statement; \
  } \
} while (0)

#endif

#define WBSetterCopy(ivar, var) WBSetterCopyAndDo(ivar, var, do {} while(0))
#define WBSetterRetain(ivar, var) WBSetterRetainAndDo(ivar, var, do {} while(0))
#define WBSetterMutableCopy(ivar, var) WBSetterMutableCopyAndDo(ivar, var, do {} while(0))

// MARK: Atomic Variants
//extern id objc_getProperty(id self, SEL _cmd, ptrdiff_t offset, BOOL atomic);
//extern void objc_copyStruct(void *dest, const void *src, ptrdiff_t size, BOOL atomic, BOOL hasStrong);
SC_EXTERN void objc_setProperty(id self, SEL _cmd, ptrdiff_t offset, id newValue, BOOL atomic, BOOL shouldCopy);

#define WBSetterCopyAtomic(ivar, var) \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, 1)

// Hack, see runtime source (use OBJC_PROPERTY_MUTABLECOPY as shouldCopy arg)
#define WBSetterMutableCopyAtomic(ivar, var) \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, 2)

#define WBSetterRetainAtomic(ivar, var) \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, NO)

// MARK: Delegate
/*!
 @defined WBDelegateHandle
 @abstract Check if delegate implements a method
 @param delegate The Delegate to register.
 @param method	method name
 */
SC_INLINE bool __WBDelegateHandle(id<NSObject> delegate, SEL method) { return delegate && [delegate respondsToSelector:method]; }
#define WBDelegateHandle(delegate, method) __WBDelegateHandle(delegate, @selector(method))

/*!
 @defined WBDelegateRegisterNotification
 @abstract   Used to register a delegate.
 @param		obj	The Delegate to register.
 @param		sel	The selector the notification need called.
 @param		notif The notification name.
 */
#define WBDelegateRegisterNotification(obj, sel, notif) do { \
  if ([obj respondsToSelector:sel])	\
    [[NSNotificationCenter defaultCenter] addObserver:obj selector:sel name:notif object:self]; \
} while (0)

#define WBDelegateUnregisterNotification(obj, sel, notif)	do { \
  if ([obj respondsToSelector:sel]) \
    [[NSNotificationCenter defaultCenter] removeObserver:obj name:notif object:self]; \
} while (0)

// MARK: NSBundle
/*!
 @defined WBCurrentBundle
 @result   Returns the bundle for the caller class.
 */
#define WBCurrentBundle()         [NSBundle bundleForClass:[self class]]
/*!
 @defined WBBundleForClass
 @param	aClass wrapper on bundleForClass:
 @result Returns the bundle for aClass.
 */
#define WBBundleForClass(aClass)  [NSBundle bundleForClass:[aClass class]]

// MARK: NSIndexSet
SC_INLINE
NSIndexSet *WBIndexesForCount(NSUInteger count) { return [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, count)]; }
SC_INLINE
NSIndexSet *WBIndexesForArray(NSArray *anArray) { return WBIndexesForCount([anArray count]); }

// MARK: NSNumber
SC_INLINE
NSNumber* WBBool(BOOL value) { return [NSNumber numberWithBool:value]; }

#define WBChar WBInt8
#define WBUChar WBUInt8
#define WBShort WBInt16
#define WBUShort WBUInt16

SC_INLINE
NSNumber* WBInt8(int8_t value) { return [NSNumber numberWithChar:value]; }
SC_INLINE
NSNumber* WBUInt8(uint8_t value) { return [NSNumber numberWithUnsignedChar:value]; }

SC_INLINE
NSNumber* WBInt16(int16_t value) { return [NSNumber numberWithShort:value]; }
SC_INLINE
NSNumber* WBUInt16(uint16_t value) { return [NSNumber numberWithUnsignedShort:value]; }

SC_INLINE
NSNumber* WBInt32(int32_t value) { return [NSNumber numberWithInt:value]; }
SC_INLINE
NSNumber* WBUInt32(uint32_t value) { return [NSNumber numberWithUnsignedInt:value]; }

#if __LP64__
SC_INLINE
NSNumber* WBInt64(int64_t value) { return [NSNumber numberWithLong:value]; }
SC_INLINE
NSNumber* WBUInt64(uint64_t value) { return [NSNumber numberWithUnsignedLong:value]; }
#else
SC_INLINE
NSNumber* WBInt64(int64_t value) { return [NSNumber numberWithLongLong:value]; }
SC_INLINE
NSNumber* WBUInt64(uint64_t value) { return [NSNumber numberWithUnsignedLongLong:value]; }
#endif

#if __LP64__
SC_INLINE
CGFloat WBCGFloatValue(id value) { return value ? [value doubleValue] : 0; }
SC_INLINE
NSNumber* WBCGFloat(CGFloat value) { return [NSNumber numberWithDouble:value]; }
#else
SC_INLINE
CGFloat WBCGFloatValue(id value) { return value ? [value floatValue] : 0; }
SC_INLINE
NSNumber* WBCGFloat(CGFloat value) { return [NSNumber numberWithFloat:value]; }
#endif

SC_INLINE
NSNumber* WBFloat(float value) { return [NSNumber numberWithFloat:value]; }
SC_INLINE
NSNumber* WBDouble(double value) { return [NSNumber numberWithDouble:value]; }

#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
SC_INLINE
NSNumber* WBInteger(NSInteger value) { return [NSNumber numberWithInt:value]; }
SC_INLINE
NSNumber* WBUInteger(NSUInteger value) { return [NSNumber numberWithUnsignedInt:value]; }
#else
SC_INLINE
NSNumber* WBInteger(NSInteger value) { return [NSNumber numberWithInteger:value]; }
SC_INLINE
NSNumber* WBUInteger(NSUInteger value) { return [NSNumber numberWithUnsignedInteger:value]; }
#endif

/* Integer value compatibility */
#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
SC_INLINE
NSInteger WBIntegerValue(id object) { return [object intValue]; }
SC_INLINE
NSUInteger WBUIntegerValue(NSNumber *object) { return [object unsignedIntValue]; }
SC_INLINE
void WBEncodeInteger(NSCoder *coder, NSInteger value, NSString *key) { [coder encodeInt:value forKey:key]; }
SC_INLINE
NSInteger WBDecodeInteger(NSCoder *coder, NSString *key) { return [coder decodeIntForKey:key]; }
#else
SC_INLINE
NSInteger WBIntegerValue(id object) { return [object integerValue]; }
SC_INLINE
NSUInteger WBUIntegerValue(NSNumber *object) { return [object unsignedIntegerValue]; }
SC_INLINE
void WBEncodeInteger(NSCoder *coder, NSInteger value, NSString *key) { [coder encodeInteger:value forKey:key]; }
SC_INLINE
NSInteger WBDecodeInteger(NSCoder *coder, NSString *key) { return [coder decodeIntegerForKey:key]; }
#endif

#endif /* __OBJC__ */

#endif /* __WBC_OBJC_H__ */
