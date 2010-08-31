/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2010 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header cxx
 @abstract C++ Specific Functions and Macros
*/

#if !defined(__WBC_CXX_H__)
#define __WBC_CXX_H__ 1

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#endif /* __WBC_CXX_H__ */
