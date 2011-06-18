/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header unix
 @abstract Unix specifics utilities
*/

#if !defined(__WBC_UNIX_H__)
#define __WBC_UNIX_H__ 1

#if !defined(_WIN32)
#include <sys/errno.h>
#endif

/* Returns errno if result < 0 */
SC_INLINE
int WBErrno(int result) {
  if (result >= 0) return 0;
#if !defined(_WIN32)
  int err = errno;
#else
  int err = GetLastError();
#endif
  assert(err != 0);
  return err;
}

#endif /* __WBC_UNIX_H__ */
