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

/* Generate function using the following pattern:

 static inline
 CFType WBNSToCFType(NSType inValue) {
   return (__bridge CFType)inValue;
 }
 static inline
 id WBCFToNSType(CFType inValue) {
   return (__bridge NSType)inValue;
 }
 // And ARC compliant methods:
 static inline CF_RETURNS_RETAINED CFType WBCFTypeBridgingRetain(NSType X) {
   return (__bridge_retained CFType)X;
 }
 static inline NSType WBCFTypeBridgingRelease(CFType CF_CONSUMED X) {
   return (__bridge_transfer id)X;
 }
 */

#if __has_feature(__objc_arc__)
#define __WBNSCFTypeBridging(NSTy, CFTy) \
  SC_INLINE CF_RETURNS_RETAINED CF##CFTy##Ref WBCF##CFTy##BridgingRetain(NS##NSTy *X) { \
    return (__bridge_retained CF##CFTy##Ref)X; \
  } \
  SC_INLINE NS##NSTy *WBCF##CFTy##BridgingRelease(CF##CFTy##Ref CF_CONSUMED X) { \
    return (__bridge_transfer NS##NSTy *)X; \
  }
#else
#define __WBNSCFTypeBridging(NSTy, CFTy) \
  SC_INLINE CF##CFTy##Ref WBCF##CFTy##BridgingRetain(NS##NSTy *X) { \
    return (CF##CFTy##Ref)X; \
  } \
  SC_INLINE NS_RETURNS_RETAINED NS##NSTy *WBCF##CFTy##BridgingRelease(CF##CFTy##Ref CF_CONSUMED X) { \
    return (NS##NSTy *)X; \
  }
#endif

#define __WBNSCFTypeBridge2(NSTy, CFTy) \
  SC_INLINE CF##CFTy##Ref WBNSToCF##CFTy(NS##NSTy *inValue) { \
    return (__bridge CF##CFTy##Ref)inValue; \
  } \
  SC_INLINE NS##NSTy *WBCFToNS##NSTy(CF##CFTy##Ref inValue) { \
    return (__bridge NS##NSTy *)inValue; \
  } \
  __WBNSCFTypeBridging(NSTy, CFTy)

#define __WBNSCFTypeBridge(Ty) __WBNSCFTypeBridge2(Ty, Ty)

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
__WBNSCFTypeBridge(Error)
__WBNSCFTypeBridge(Locale)
__WBNSCFTypeBridge(TimeZone)
__WBNSCFTypeBridge(Calendar)

__WBNSCFTypeBridge(CharacterSet)
__WBNSCFTypeBridge(MutableCharacterSet)

// Type with ≠ names
__WBNSCFTypeBridge2(Timer, RunLoopTimer)

__WBNSCFTypeBridge2(InputStream, ReadStream)
__WBNSCFTypeBridge2(OutputStream, WriteStream)

#undef __WBNSCFTypeBridge2
#undef __WBNSCFTypeBridge

#if __has_feature(__objc_arc__)
  #define WBCFAutorelease(nstype, cfvalue) WBCFTo##nstype(cfvalue)
#else
  #define WBCFAutorelease(nstype, cfvalue) [WBCFTo##nstype(cfvalue) autorelease]
#endif

#endif /* __OBJC__ */

#endif /* __WBC_CFBRIDGE_H__ */
