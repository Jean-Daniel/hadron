/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
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
    private: \
      TypeName(const TypeName&); \
      void operator=(const TypeName&)

// MARK: C++0x Support
#if __has_feature(cxx_override_control)
  #define cxx_final final
  #define cxx_override override
#elif _MSC_VER
  #define cxx_final sealed
  #define cxx_override override
#else
  #define cxx_final
  #define cxx_override
#endif

#endif /* __WBC_CXX_H__ */
