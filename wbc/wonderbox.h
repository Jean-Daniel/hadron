/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
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

/* Use to avoid class name conflict when statically linking WonderBox class */
#if !defined(WB_CLASS_PREFIX)
	#define WB_CLASS_PREFIX WB
#endif

// The magie of argument prescan !
#define __WBClass(prefix, class) prefix ## class
#define _WBClass(prefix, class) __WBClass(prefix, class)

#define __WBInternalClass(prefix, class) _ ## prefix ## class
#define _WBInternalClass(prefix, class) __WBInternalClass(prefix, class)

// Public macros
#define WBClass(class) __WBClass(WB_CLASS_PREFIX, class)
#define WBInternalClass(class) _WBInternalClass(WB_CLASS_PREFIX, class)

#endif /* __WBC_WONDERBOX_H__ */
