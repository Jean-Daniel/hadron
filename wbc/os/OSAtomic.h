/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */

#if !defined(__WBC_OS_ATOMIC_H)
#define __WBC_OS_ATOMIC_H 1

#if defined(__GNUC__)
  #include "atomic/gnuc.h"
#elif defined(_WIN32)
  #include "atomic/windows.h"
#endif

#endif /* __WBC_OS_ATOMIC_H */
