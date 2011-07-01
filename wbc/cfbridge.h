/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Cocoa To CoreFoundation safe type cast
*/

#if !defined(__WBC_CFBRIDGE_H__)
#define __WBC_CFBRIDGE_H__ 1

// MARK: Cocoa To CoreFoundation

#if defined(__OBJC__)

SC_INLINE
NSRange NSRangeFromCFRange(CFRange range) {
  return NSMakeRange((NSUInteger)range.location, (NSUInteger)range.length);
}

SC_INLINE
CFRange NSRangeToCFRange(NSRange range) {
  return CFRangeMake((CFIndex)range.location, (CFIndex)range.length);
}

// MARK: Safe casts

SC_INLINE CFTypeRef WBNSToCFType(id inValue) {
  return (__bridge CFTypeRef)inValue;
}
SC_INLINE id WBCFToNSType(CFTypeRef inValue) {
  return (__bridge id)inValue;
}

#define __WBNSCFTypeBridge(Ty) \
  SC_INLINE CF##Ty##Ref WBNSToCF##Ty(NS##Ty *inValue) { \
    return (__bridge CF##Ty##Ref)inValue; \
  } \
  SC_INLINE NS##Ty *WBCFToNS##Ty(CF##Ty##Ref inValue) { \
    return (__bridge NS##Ty *)inValue; \
  } \

__WBNSCFTypeBridge(URL)
__WBNSCFTypeBridge(Date)
__WBNSCFTypeBridge(Number)

__WBNSCFTypeBridge(Data)
__WBNSCFTypeBridge(MutableData)

__WBNSCFTypeBridge(String)
__WBNSCFTypeBridge(MutableString)

__WBNSCFTypeBridge(AttributedString)
__WBNSCFTypeBridge(MutableAttributedString)

// Collections
__WBNSCFTypeBridge(Set)
__WBNSCFTypeBridge(MutableSet)

__WBNSCFTypeBridge(Array)
__WBNSCFTypeBridge(MutableArray)

__WBNSCFTypeBridge(Dictionary)
__WBNSCFTypeBridge(MutableDictionary)

// Other Types
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
__WBNSCFTypeBridge(Error)
#endif
__WBNSCFTypeBridge(Locale)
__WBNSCFTypeBridge(TimeZone)
__WBNSCFTypeBridge(Calendar)

#undef __WBNSCFTypeBridge

/* other type:
 - CFReadStreamRef
 - CFWriteStreamRef
 - CFRunLoopTimerRef
 - CFCharacterSetRef
 - CFMutableCharacterSetRef
 */
#if __has_feature(objc_arc)
  #define WBCFAutorelease(nstype, cfvalue) WBCFTo##nstype(cfvalue)
#else
  #define WBCFAutorelease(nstype, cfvalue) [WBCFTo##nstype(cfvalue) autorelease]
#endif

#endif /* __OBJC__ */

#endif /* __WBC_CFBRIDGE_H__ */
