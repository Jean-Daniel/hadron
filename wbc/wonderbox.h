/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract WonderBox Prefix Header.
*/

#if !defined(__WBC_WONDERBOX_H__)
#define __WBC_WONDERBOX_H__ 1

/* Wonderbox build support */
#if defined(WONDERBOX_FRAMEWORK)
  #if !defined(WONDERBOX_NAME)
    #define WONDERBOX_NAME WonderBox
  #endif
  #define WBHEADER(header) <WONDERBOX_NAME/header>
#else
  #define WBHEADER(header) #header
#endif

#endif /* __WBC_WONDERBOX_H__ */
