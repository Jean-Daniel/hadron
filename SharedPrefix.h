/*
 *  SharedPrefix.h
 *  hadron
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Shared Prefix Header.
*/

#if !defined(SHARED_PREFIX_H__)
#define SHARED_PREFIX_H__ 1

#include "spx/core.h" // must be before all others

#if defined(__cplusplus)
  #include "spx/cxx.h" // must come soon
#endif

#include "spx/math.h"

#if defined(__COREFOUNDATION__)
  #include "spx/cfutils.h"
#endif

#if defined(__OBJC__)
  #include "spx/objc.h"
  #include "spx/cfbridge.h"
#endif

#include "spx/link.h"
#include "spx/assert.h"
#include "spx/profile.h"
#include "spx/logging.h"
#include "spx/bitfield.h"

#endif /* SHARED_PREFIX_H__ */
