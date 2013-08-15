/*
 *  SPXTest.h
 *  hadron
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2013 Jean-Daniel Dupas. All rights reserved.
 */

#if !defined(__SPX_TEST_H)
#define __SPX_TEST_H

/* Simple bridge to abstract the underlying Test framework implementation
 actually design to support gtests and XCTest
 */

#if __has_include(<XCTest/XCTest.h>)

#import <XCTest/XCTest.h>

#define SPX_TEST_CLASS(cls) \
@interface cls##Tests : XCTestCase \
@end \
@implementation cls##Tests

#define SPX_TEST(cls, name) - (void)test_##name

#define SPX_TEST_CLASS_END(cls) @end

#define SPXTFail(format...) XCTFail(format)

#define SPXTAssertNil(a1, format...) XCTAssertNil(a1, format)
#define SPXTAssertNotNil(a1, format...) XCTAssertNotNil(a1, format)

#define SPXTAssert(expression, format...) XCTAssert(expression, format)

#define SPXTAssertTrue(expression, format...) XCTAssertTrue(expression, format)
#define SPXTAssertFalse(expression, format...) XCTAssertFalse(expression, format)

/* XCTAssertThrows only catch id exception, which is not what we want for SPXTest framework */
#define SPXTAssertThrows(expression, format...) ({ \
  BOOL __caughtException = NO; \
    @try { \
      (expression); \
    } @catch (...) { \
      __caughtException = YES; \
    }\
    if (!__caughtException) { \
      _XCTRegisterFailure(_XCTFailureDescription(_XCTAssertion_Throws, 0, @#expression),format); \
    } \
  })

#define SPXTAssertNoThrow(expression, format...) XCTAssertNoThrow(expression, format)

#else

#include <gtest/gtest.h>

static char _spx_buffer[256];

#define SPX_TEST_CLASS(cls)
#define SPX_TEST_CLASS_END(cls)

#define SPX_TEST(cls, name) TEST(cls, name)

#define _SPXTFormat(format...) ({ \
  snprintf(_spx_buffer, 256, "" format); \
  _spx_buffer; \
})

#define SPXTAssertTrue(expression, format...) ASSERT_TRUE(expression) << _SPXTFormat(format)
#define SPXTAssertFalse(expression, format...) ASSERT_FALSE(expression) << _SPXTFormat(format)

#define SPXTAssertThrows(expression, format...) ASSERT_ANY_THROW(expression) << _SPXTFormat(format)
#define SPXTAssertNoThrow(expression, format...) ASSERT_NO_THROW(expression) << _SPXTFormat(format)

#endif /* __has_include */

#endif /* __SPX_TEST_H */
