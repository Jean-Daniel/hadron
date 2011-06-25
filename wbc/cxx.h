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

// MARK: C++0x Support
#if __has_extension(cxx_override_control)
  #define cxx_final final
  #define cxx_override override
#elif _MSC_VER
  #define cxx_final sealed
  #define cxx_override override
#else
  #define cxx_final
  #define cxx_override
#endif

#if __has_extension(cxx_noexcept)
  #define cxx_noexcept noexcept
#else
  #define cxx_noexcept
#endif

/* we can't use __has_extension to test for features in code, as only clang support it. */

/* rvalue references */
#if __has_extension(cxx_rvalue_references) || _MSC_VER
  #define has_cxx_rvalue_references 1
#endif

#if has_cxx_rvalue_references
  #define cxx_move(arg) std::move(arg)
#else
  #define cxx_move(arg) arg
#endif

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  private: \
    TypeName(const TypeName&) cxx_noexcept; \
    void operator=(const TypeName&) cxx_noexcept

#endif /* __WBC_CXX_H__ */
