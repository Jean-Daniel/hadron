//
//  SPXTests.h
//  SPXTests
//
//  Created by Jean-Daniel on 08/12/12.
//  Copyright (c) 2012 Jean-Daniel Dupas. All rights reserved.
//


static SPX_UNUSED
void test_macros(void) {
  spx_assert(true, "assertion ok");
  spx_abort("should never be called");
  spx_unreachable("should never be called");
  static_assert(true, "is static_assert defined");
}

#if defined(__OBJC__)

static SPX_UNUSED
void test_objc_macros(void) {
  SPXThrowException(@"Hello World", @"Should not append");
  SPXThrowException(@"Hello World", @"Should not append %s", "arg");
}

#endif
