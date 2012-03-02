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
  #define wb_final final
  #define wb_override override
#elif _MSC_VER
  #define wb_final sealed
  #define wb_override override
#else
  #define wb_final
  #define wb_override
#endif

#if __has_extension(cxx_noexcept)
  #define wb_noexcept noexcept
  #define wb_noexcept_(arg) noexcept(arg)
#else
  #define wb_noexcept
  #define wb_noexcept_(arg)
#endif

/* we can't use __has_extension to test for features in code, as only clang support it. */

/* rvalue references */
#if __has_extension(cxx_rvalue_references)
  #if __has_include(<mutex>) // make sure this is a c++11 compliant std library
    #define has_cxx_rvalue_references 1
  #endif
#elif defined(_MSC_VER)
  #define has_cxx_rvalue_references 1
#endif

#if has_cxx_rvalue_references
  /* declaration for move, swap, forward, ... */
  #include <utility>
  #define wb_move(arg) std::move(arg)
  #define wb_forward(Ty, arg) std::forward<Ty>(arg)
#else
  #define wb_move(arg) arg
  #define wb_forward(Ty, arg) arg
#endif

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  private:                                 \
    TypeName(const TypeName&) wb_noexcept; \
    void operator=(const TypeName&) wb_noexcept

#if has_cxx_rvalue_references
  #define DISALLOW_MOVE(TypeName)       \
    private:                            \
      TypeName(TypeName&&) wb_noexcept; \
      void operator=(TypeName&&) wb_noexcept
#else
  #define DISALLOW_MOVE(TypeName)
#endif

#define DISALLOW_COPY_ASSIGN_MOVE(TypeName) \
  DISALLOW_MOVE(TypeName);                  \
  DISALLOW_COPY_AND_ASSIGN(TypeName)


#endif /* __WBC_CXX_H__ */
