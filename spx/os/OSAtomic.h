/*
 *  OSAtomic.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */

#if defined(__GNUC__)
  #include "atomic/gnuc.h"
#elif defined(_WIN32)
  #include "atomic/windows.h"
#endif
