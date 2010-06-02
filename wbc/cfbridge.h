/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Cocoa To CoreFoundation safe type cast
*/

#if !defined(__WBC_CFBRIDGE_H__)
#define __WBC_CFBRIDGE_H__ 1

// MARK: Cocoa To CoreFoundation

#if defined(__OBJC__)

#define WBCFAutorelease(cftype) [WBMakeCollectable(cftype) autorelease]

WB_INLINE
NSRange NSRangeFromCFRange(CFRange range) {
  return NSMakeRange((NSUInteger)range.location, (NSUInteger)range.length);
}

WB_INLINE
CFRange NSRangeToCFRange(NSRange range) {
  return CFRangeMake((CFIndex)range.location, (CFIndex)range.length);
}

//
//  UKTypecastMacros.h
//
//  Created by Uli Kusterer on 11.04.2010
//  Copyright 2010 Uli Kusterer.
//
//	This software is provided 'as-is', without any express or implied
//	warranty. In no event will the authors be held liable for any damages
//	arising from the use of this software.
//
//	Permission is granted to anyone to use this software for any purpose,
//	including commercial applications, and to alter it and redistribute it
//	freely, subject to the following restrictions:
//
//	   1. The origin of this software must not be misrepresented; you must not
//	   claim that you wrote the original software. If you use this software
//	   in a product, an acknowledgment in the product documentation would be
//	   appreciated but is not required.
//
//	   2. Altered source versions must be plainly marked as such, and must not be
//	   misrepresented as being the original software.
//
//	   3. This notice may not be removed or altered from any source
//	   distribution.
//

/*
 This file contains inline functions that make typecasts between toll-free
 bridged types type-safe. This works by simply wrapping them in a function,
 which then performs type-checking, so when you give it an NSURL* instead
 of an NSString* it will complain, not silently cast it away.

 You'd generally #import this file in your project's prefix header.
 */

// NSNumber:
WB_INLINE CFNumberRef WBNSToCFNumber(NSNumber *inNumber) {
  return (CFNumberRef)inNumber;
}
WB_INLINE NSNumber *WBCFToNSNumber(CFNumberRef inNumber) {
  return (NSNumber*)inNumber;
}

// MARK: NSData
WB_INLINE CFDataRef WBNSToCFData(NSData * inData) {
  return (CFDataRef)inData;
}
WB_INLINE NSData *WBCFToNSData(CFDataRef inData) {
  return (NSData *)inData;
}

// MARK: NSMutableData
WB_INLINE CFMutableDataRef WBNSToCFMutableData(NSMutableData *inMutableData) {
  return (CFMutableDataRef)inMutableData;
}
WB_INLINE NSMutableData *WBCFToNSMutableData(CFMutableDataRef inMutableData) {
  return (NSMutableData*)inMutableData;
}

// MARK: NSString
WB_INLINE CFStringRef WBNSToCFString(NSString *inString) {
  return (CFStringRef)inString;
}
WB_INLINE NSString *WBCFToNSString(CFStringRef inString) {
  return (NSString *)inString;
}

// MARK: NSMutableString
WB_INLINE CFMutableStringRef WBNSToCFMutableString(NSMutableString *inMutableString) {
  return (CFMutableStringRef)inMutableString;
}
WB_INLINE NSMutableString *WBCFToNSMutableString(CFMutableStringRef inMutableString) {
  return (NSMutableString *)inMutableString;
}

// MARK: NSAttributedString
WB_INLINE CFAttributedStringRef WBNSToCFAttributedString(NSAttributedString *inAttributedString) {
  return (CFAttributedStringRef)inAttributedString;
}
WB_INLINE NSAttributedString *WBCFToNSAttributedString(CFAttributedStringRef inAttributedString) {
  return (NSAttributedString *)inAttributedString;
}

// MARK: NSMutableAttributedString
WB_INLINE CFMutableAttributedStringRef WBNSToCFMutableAttributedString(NSMutableAttributedString *inMutableAttributedString) {
  return (CFMutableAttributedStringRef)inMutableAttributedString;
}
WB_INLINE NSMutableAttributedString *WBCFToNSMutableAttributedString(CFMutableAttributedStringRef inMutableAttributedString) {
  return (NSMutableAttributedString *)inMutableAttributedString;
}

// MARK: NSURL
WB_INLINE CFURLRef WBNSToCFURL(NSURL *inURL) {
  return (CFURLRef)inURL;
}
WB_INLINE NSURL *WBCFToNSURL(CFURLRef inURL) {
  return (NSURL *)inURL;
}

// MARK: NSDate
WB_INLINE CFDateRef WBNSToCFDate(NSDate *inDate) {
  return (CFDateRef)inDate;
}
WB_INLINE NSDate *WBCFToNSDate(CFDateRef inDate) {
  return (NSDate *)inDate;
}


// MARK: NSDictionary
WB_INLINE CFDictionaryRef WBNSToCFDictionary(NSDictionary *inDictionary) {
  return (CFDictionaryRef)inDictionary;
}
WB_INLINE NSDictionary *WBCFToNSDictionary(CFDictionaryRef inDictionary) {
  return (NSDictionary *)inDictionary;
}

// MARK: NSMutableDictionary
WB_INLINE CFMutableDictionaryRef WBNSToCFMutableDictionary(NSMutableDictionary *inMutableDictionary) {
  return (CFMutableDictionaryRef)inMutableDictionary;
}
WB_INLINE NSMutableDictionary *WBCFToNSMutableDictionary(CFMutableDictionaryRef inMutableDictionary) {
  return (NSMutableDictionary *)inMutableDictionary;
}

// MARK: NSArray
WB_INLINE CFArrayRef WBNSToCFArray(NSArray *inArray) {
  return (CFArrayRef)inArray;
}
WB_INLINE NSArray *WBCFToNSArray(CFArrayRef inArray) {
  return (NSArray *)inArray;
}

// MARK: NSMutableArray
WB_INLINE CFMutableArrayRef WBNSToCFMutableArray(NSMutableArray *inMutableArray) {
  return (CFMutableArrayRef)inMutableArray;
}
WB_INLINE NSMutableArray *WBCFToNSMutableArray(CFMutableArrayRef inMutableArray) {
  return (NSMutableArray *)inMutableArray;
}

// MARK: NSSet
WB_INLINE CFSetRef WBNSToCFSet(NSSet *inSet) {
  return (CFSetRef)inSet;
}
WB_INLINE NSSet *WBCFToNSSet(CFSetRef inSet) {
  return (NSSet *)inSet;
}

// MARK: NSMutableSet
WB_INLINE CFMutableSetRef WBNSToCFMutableSet(NSMutableSet *inMutableSet) {
  return (CFMutableSetRef)inMutableSet;
}
WB_INLINE NSMutableSet *WBCFToNSMutableSet(CFMutableSetRef inMutableSet) {
  return (NSMutableSet *)inMutableSet;
}

/* other type:
 - CFErrorRef
 - CFLocaleRef
 - CFTimeZoneRef
 - CFCalendarRef
 - CFReadStreamRef
 - CFWriteStreamRef
 - CFRunLoopTimerRef
 - CFCharacterSetRef
 - CFMutableCharacterSetRef
 */

#endif /* __OBJC__ */

#endif /* __WBC_CFBRIDGE_H__ */
