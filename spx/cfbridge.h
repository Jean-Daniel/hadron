/*
 *  cfbridge.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Cocoa To CoreFoundation safe and ARC compliant cast.
*/

// MARK: Cocoa To CoreFoundation

#if !defined(__OBJC__)
#  error This header require Objective-C
#endif

SPX_INLINE
NSRange NSRangeFromCFRange(CFRange range) {
  return NSMakeRange((NSUInteger)range.location, (NSUInteger)range.length);
}

SPX_INLINE
CFRange NSRangeToCFRange(NSRange range) {
  return CFRangeMake((CFIndex)range.location, (CFIndex)range.length);
}

// MARK: Safe casts

SPX_INLINE CFTypeRef SPXNSToCFType(id obj) {
  return (__bridge CFTypeRef)obj;
}
SPX_INLINE id SPXCFToNSType(CFTypeRef cfref) {
  return (__bridge id)cfref;
}

#if __has_feature(objc_arc)
SPX_INLINE CFTypeRef SPXCFTypeBridgingRetain(id obj) {
  return (__bridge_retained CFTypeRef)obj;
}
SPX_INLINE id SPXCFTypeBridgingRelease(CFTypeRef CF_CONSUMED cfref) {
  return (__bridge_transfer id)cfref;
}
#else
SPX_INLINE CFTypeRef SPXCFTypeBridgingRetain(id obj) {
  return (__bridge_retained CFTypeRef)obj;
}
SPX_INLINE NS_RETURNS_RETAINED id SPXCFTypeBridgingRelease(CFTypeRef CF_CONSUMED cfref) {
  return (__bridge_transfer id)cfref;
}
#endif

/* Generate function using the following pattern:

 static inline
 CFType SPXNSToCFType(NSType inValue) {
   return (__bridge CFType)inValue;
 }
 static inline
 id SPXCFToNSType(CFType inValue) {
   return (__bridge NSType)inValue;
 }
 // And ARC compliant methods:
 static inline CF_RETURNS_RETAINED CFType SPXCFTypeBridgingRetain(NSType X) {
   return (__bridge_retained CFType)X;
 }
 static inline NSType SPXCFTypeBridgingRelease(CFType CF_CONSUMED X) {
   return (__bridge_transfer id)X;
 }
 */

#if __has_feature(objc_arc)
#define __SPXNSCFTypeBridging(NSTy, CFTy) \
  SPX_INLINE CF_RETURNS_RETAINED CF##CFTy##Ref SPXCF##CFTy##BridgingRetain(NS##NSTy *X) { \
    return (__bridge_retained CF##CFTy##Ref)X; \
  } \
  SPX_INLINE NS##NSTy *SPXCF##CFTy##BridgingRelease(CF##CFTy##Ref CF_CONSUMED X) { \
    return (__bridge_transfer NS##NSTy *)X; \
  }
#else
#define __SPXNSCFTypeBridging(NSTy, CFTy) \
  SPX_INLINE CF_RETURNS_RETAINED CF##CFTy##Ref SPXCF##CFTy##BridgingRetain(NS##NSTy *X) { \
    return X ? (CF##CFTy##Ref)CFRetain((CF##CFTy##Ref)X) : NULL; \
  } \
  SPX_INLINE NS##NSTy *SPXCF##CFTy##BridgingRelease(CF##CFTy##Ref CF_CONSUMED X) { \
		return [(id)X autorelease]; \
  }
#endif

#define __SPXNSCFTypeBridge2(NSTy, CFTy) \
  SPX_INLINE CF##CFTy##Ref SPXNSToCF##CFTy(NS##NSTy *inValue) { \
    return (__bridge CF##CFTy##Ref)inValue; \
  } \
  SPX_INLINE NS##NSTy *SPXCFToNS##NSTy(CF##CFTy##Ref inValue) { \
    return (__bridge NS##NSTy *)inValue; \
  } \
  __SPXNSCFTypeBridging(NSTy, CFTy)

#define __SPXNSCFTypeBridge(Ty) __SPXNSCFTypeBridge2(Ty, Ty)

__SPXNSCFTypeBridge(URL)
__SPXNSCFTypeBridge(Date)
__SPXNSCFTypeBridge(Number)

__SPXNSCFTypeBridge(Data)
__SPXNSCFTypeBridge(MutableData)

__SPXNSCFTypeBridge(String)
__SPXNSCFTypeBridge(MutableString)

__SPXNSCFTypeBridge(AttributedString)
__SPXNSCFTypeBridge(MutableAttributedString)

// Collections
__SPXNSCFTypeBridge(Set)
__SPXNSCFTypeBridge(MutableSet)

__SPXNSCFTypeBridge(Array)
__SPXNSCFTypeBridge(MutableArray)

__SPXNSCFTypeBridge(Dictionary)
__SPXNSCFTypeBridge(MutableDictionary)

// Other Types
__SPXNSCFTypeBridge(Error)
__SPXNSCFTypeBridge(Locale)
__SPXNSCFTypeBridge(TimeZone)
__SPXNSCFTypeBridge(Calendar)

__SPXNSCFTypeBridge(CharacterSet)
__SPXNSCFTypeBridge(MutableCharacterSet)

// Type with ≠ names
__SPXNSCFTypeBridge2(Timer, RunLoopTimer)

__SPXNSCFTypeBridge2(InputStream, ReadStream)
__SPXNSCFTypeBridge2(OutputStream, WriteStream)

#undef __SPXNSCFTypeBridge2
#undef __SPXNSCFTypeBridge

#if __has_feature(objc_arc)
  #define SPXCFAutorelease(nstype, cfvalue) SPXCFTo##nstype(cfvalue)
#else
  #define SPXCFAutorelease(nstype, cfvalue) [SPXCFTo##nstype(cfvalue) autorelease]
#endif
