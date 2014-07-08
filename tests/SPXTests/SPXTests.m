//
//  SPXTests.m
//  SPXTests
//
//  Created by Jean-Daniel on 08/12/12.
//  Copyright (c) 2012 Jean-Daniel Dupas. All rights reserved.
//

#import "SPXTests.h"

#import <XCTest/XCTest.h>

@interface SPXTests : XCTestCase

@end

@implementation SPXTests

SPX_INITIALIZER(__InitializeTests) {
  // should be run before main

}

SPX_TERMINATOR(__FinalizeTests) {
  // should be run at exit

}

- (void)setUp {
  [super setUp];
}

- (void)tearDown {
  [super tearDown];
}


- (void)testCore {
  SPXTrace();
  spx_trace();

  spx_debug("Hello %s", "World");
  spx_log_error("Hello %s", "World");
  spx_log_warning("Hello %s", "World");
  spx_log(NULL, NULL, ASL_LEVEL_CRIT, "Hello %s", "World");

  SPXDebug(@"Hello %@", @"World");
  SPXLogError(@"Hello %@", @"World");
  SPXLogWarning(@"Hello %@", @"World");
  SPXLog(NULL, NULL, ASL_LEVEL_CRIT, @"Hello %@", @"World");
}

- (void)testBitFields {
//  uint64_t SPXBitfieldMask64(uint64_t n1, uint64_t n2);
//  uint64_t SPXBitfieldMask32(uint32_t n1, uint32_t n2);
//  uint64_t SPXBitfieldGetValue64(uint64_t bitfield, uint32_t n1, uint32_t n2);
//  uint32_t SPXBitfieldGetValue32(uint32_t bitfield, uint32_t n1, uint32_t n2);
//  uint64_t SPXBitfieldGetMaxValue64(uint32_t n1, uint32_t n2);
//  uint32_t SPXBitfieldGetMaxValue32(uint32_t n1, uint32_t n2);
//  uint64_t SPXBitfieldSetMaxValue64(uint64_t *bitfield, uint64_t value, uint32_t n1, uint32_t n2);
//  uint32_t SPXBitfieldSetMaxValue32(uint32_t *bitfield, uint32_t value, uint32_t n1, uint32_t n2);
//  void SPXBitSet64(uint64_t *value, uint32_t n);
//  void SPXBitSet32(uint32_t *value, uint32_t n);
//  void SPXBitClear64(uint64_t *value, uint32_t n);
//  void SPXBitClear32(uint32_t *value, uint32_t n);
//  bool SPXBitIsSet64(uint64_t value, uint32_t n);
//  bool SPXBitIsSet32(uint32_t value, uint32_t n);
//
//  SPXFlagSet(field, value);
//  SPXFlagTestAndSet(field, value);
}

- (void)testBitOps {
  // Population count
//  SPX_INLINE int spx_popcount32(uint32_t value) { return __builtin_popcount(value); }
//  SPX_INLINE int spx_popcount64(uint64_t value) { return __builtin_popcountll(value); }
//
//  // Count Leading Zeros (left)
//  // returns 0 based index. If value zero, result is undefined.
//  SPX_INLINE int spx_clz32(uint32_t value) { return __builtin_clz(value); }
//  SPX_INLINE int spx_clz64(uint64_t value) { return __builtin_clzll(value); }
//  // returns 1 based index. If value is 0, returns 0.
//  SPX_INLINE int spx_fls32(uint32_t value) { return value ? __builtin_clz(value) + 1 : 0; }
//  SPX_INLINE int spx_fls64(uint64_t value) { return value ? __builtin_clzll(value) + 1 : 0; }
//
//  // Count Trailing Zeros (right)
//  // returns 0 based index. If value zero, result is undefined.
//  SPX_INLINE int spx_ctz32(uint32_t value) { return __builtin_ctz(value); }
//  SPX_INLINE int spx_ctz64(uint64_t value) { return __builtin_ctzll(value); }
//  // returns 1 based index. If value is 0, returns 0.
//  SPX_INLINE int spx_ffs32(uint32_t value) { return __builtin_ffs(value); }
//  SPX_INLINE int spx_ffs64(uint64_t value) { return __builtin_ffsll(value); }
}

- (void)objcMacros {
  SPXAbstractMethodException();
}

@end
