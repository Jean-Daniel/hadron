/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Obj-C Specifics macros
*/

#if !defined(__WBC_OBJC_H__)
#define __WBC_OBJC_H__ 1

#if defined (__OBJC__)

#if DEBUG
#define WBProperty(propName)    NSStringFromSelector(@selector(propName))
#else
#define WBProperty(propName)    @#propName
#endif

// MARK: Accessors
/* For safety we retain var before releasing ivar (ivar can contain the last reference on var). */
#define WBSetterRetain(ivar, var) _WBSetterRetain(&ivar, var)
WB_INLINE
BOOL _WBSetterRetain(id *ivar, id var) {
  if (*ivar != var) {
    [var retain];
    [*ivar release];
    *ivar = var;
    return YES;
  }
  return NO;
}

/* For safety we copy var before releasing ivar (ivar can contain the last reference on var). */
#define WBSetterCopy(ivar, var) _WBSetterCopyWithZone(&ivar, var, [self zone])
#define WBSetterCopyWithZone(ivar, var, aZone) _WBSetterCopyWithZone(&ivar, var, aZone)
WB_INLINE
BOOL _WBSetterCopyWithZone(id *ivar, id var, NSZone *aZone) {
  if (*ivar != var) {
    var = [var copyWithZone:aZone];
    [*ivar release];
    *ivar = var;
    return YES;
  }
  return NO;
}

#define WBSetterMutableCopy(ivar, var) _WBSetterMutableCopyWithZone(&ivar, var, [self zone])
#define WBSetterMutableCopyWithZone(ivar, var, aZone) _WBSetterMutableCopyWithZone(&ivar, var, aZone)
WB_INLINE
BOOL _WBSetterMutableCopyWithZone(id *ivar, id var, NSZone *aZone) {
  if (*ivar != var) {
    var = [var mutableCopyWithZone:aZone];
    [*ivar release];
    *ivar = var;
    return YES;
  }
  return NO;
}

// MARK: Atomic Variants
//extern id objc_getProperty(id self, SEL _cmd, ptrdiff_t offset, BOOL atomic);
//extern void objc_copyStruct(void *dest, const void *src, ptrdiff_t size, BOOL atomic, BOOL hasStrong);
WB_EXTERN void objc_setProperty(id self, SEL _cmd, ptrdiff_t offset, id newValue, BOOL atomic, BOOL shouldCopy);

#define WBSetterCopyAtomic(ivar, var) do { \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, 1); \
} while (0)

// Hack, see runtime source (use OBJC_PROPERTY_MUTABLECOPY as shouldCopy arg)
#define WBSetterMutableCopyAtomic(ivar, var) do { \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, 2); \
} while (0)

#define WBSetterRetainAtomic(ivar, var) do { \
  objc_setProperty(self, _cmd, (ptrdiff_t)(&ivar) - (ptrdiff_t)(self), var, YES, NO); \
} while (0)

// MARK: Delegate
/*!
 @defined WBDelegateHandle
 @abstract Check if delegate implements a method
 @param delegate The Delegate to register.
 @param method	method name
 */
WB_INLINE bool __WBDelegateHandle(id delegate, SEL method) { return delegate && [delegate respondsToSelector:method]; }
#define WBDelegateHandle(delegate, method) __WBDelegateHandle(delegate, @selector(method))

/*!
 @defined WBDelegateRegisterNotification
 @abstract   Used to register a delegate.
 @param		obj	The Delegate to register.
 @param		sel	The selector the notification need called.
 @param		notif The notification name.
 */
#define WBDelegateRegisterNotification(obj, sel, notif)		if ([obj respondsToSelector:sel]) {	\
  																[[NSNotificationCenter defaultCenter] addObserver:obj selector:sel name:notif object:self]; }

#define WBDelegateUnregisterNotification(obj, sel, notif)	if ([obj respondsToSelector:sel]) {	\
  																[[NSNotificationCenter defaultCenter] removeObserver:obj name:notif object:self];	}


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
/*
 Usage: 
 WBIndexesIterator(idx, (NSIndexSet *)indexes) {
 }
 */
#define WBIndexesIterator(var, indexes) for (NSUInteger var = [indexes firstIndex]; indexes != nil && var != NSNotFound; var = [indexes indexGreaterThanIndex:var])

#define WBIndexesReverseIterator(var, indexes) for (NSUInteger var = [indexes lastIndex]; indexes != nil && var != NSNotFound; var = [indexes indexLessThanIndex:var])

WB_INLINE
NSIndexSet *WBIndexesForCount(NSUInteger count) { return [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, count)]; }
WB_INLINE
NSIndexSet *WBIndexesForArray(NSArray *anArray) { return WBIndexesForCount([anArray count]); }

// MARK: NSNumber
WB_INLINE
NSNumber* WBBool(BOOL value) { return [NSNumber numberWithBool:value]; }

#define WBChar WBInt8
#define WBUChar WBUInt8
#define WBShort WBInt16
#define WBUShort WBUInt16

WB_INLINE
NSNumber* WBInt8(int8_t value) { return [NSNumber numberWithChar:value]; }
WB_INLINE
NSNumber* WBUInt8(uint8_t value) { return [NSNumber numberWithUnsignedChar:value]; }

WB_INLINE
NSNumber* WBInt16(int16_t value) { return [NSNumber numberWithShort:value]; }
WB_INLINE
NSNumber* WBUInt16(uint16_t value) { return [NSNumber numberWithUnsignedShort:value]; }

WB_INLINE
NSNumber* WBInt32(int32_t value) { return [NSNumber numberWithInt:value]; }
WB_INLINE
NSNumber* WBUInt32(uint32_t value) { return [NSNumber numberWithUnsignedInt:value]; }

#if __LP64__
WB_INLINE
NSNumber* WBInt64(int64_t value) { return [NSNumber numberWithLong:value]; }
WB_INLINE
NSNumber* WBUInt64(uint64_t value) { return [NSNumber numberWithUnsignedLong:value]; }
#else
WB_INLINE
NSNumber* WBInt64(int64_t value) { return [NSNumber numberWithLongLong:value]; }
WB_INLINE
NSNumber* WBUInt64(uint64_t value) { return [NSNumber numberWithUnsignedLongLong:value]; }
#endif

#if __LP64__
WB_INLINE
CGFloat WBCGFloatValue(id value) { return value ? [value doubleValue] : 0; }
WB_INLINE
NSNumber* WBCGFloat(CGFloat value) { return [NSNumber numberWithDouble:value]; }
#else
WB_INLINE
CGFloat WBCGFloatValue(id value) { return value ? [value floatValue] : 0; }
WB_INLINE
NSNumber* WBCGFloat(CGFloat value) { return [NSNumber numberWithFloat:value]; }
#endif

WB_INLINE
NSNumber* WBFloat(float value) { return [NSNumber numberWithFloat:value]; }
WB_INLINE
NSNumber* WBDouble(double value) { return [NSNumber numberWithDouble:value]; }

#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
WB_INLINE
NSNumber* WBInteger(NSInteger value) { return [NSNumber numberWithInt:value]; }
WB_INLINE
NSNumber* WBUInteger(NSUInteger value) { return [NSNumber numberWithUnsignedInt:value]; }
#else
WB_INLINE
NSNumber* WBInteger(NSInteger value) { return [NSNumber numberWithInteger:value]; }
WB_INLINE
NSNumber* WBUInteger(NSUInteger value) { return [NSNumber numberWithUnsignedInteger:value]; }
#endif

/* Integer value compatibility */
#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
WB_INLINE
NSInteger WBIntegerValue(id object) { return [object intValue]; }
WB_INLINE
NSUInteger WBUIntegerValue(NSNumber *object) { return [object unsignedIntValue]; }
WB_INLINE
void WBEncodeInteger(NSCoder *coder, NSInteger value, NSString *key) { [coder encodeInt:value forKey:key]; }
WB_INLINE
NSUInteger WBDecodeInteger(NSCoder *coder, NSString *key) { return [coder decodeIntForKey:key]; }
#else
WB_INLINE
NSInteger WBIntegerValue(id object) { return [object integerValue]; }
WB_INLINE
NSUInteger WBUIntegerValue(NSNumber *object) { return [object unsignedIntegerValue]; }
WB_INLINE
void WBEncodeInteger(NSCoder *coder, NSInteger value, NSString *key) { [coder encodeInteger:value forKey:key]; }
WB_INLINE
NSUInteger WBDecodeInteger(NSCoder *coder, NSString *key) { return [coder decodeIntegerForKey:key]; }
#endif

#endif /* __OBJC__ */

#endif /* __WBC_OBJC_H__ */
