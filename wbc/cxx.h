/*
 *  cxx.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract c++ utilities
*/

#if !defined(__WBC_CXX_H__)
#define _WBC_CXX_H__ 1

#if __has_include(<type_traits>) || defined(_MSC_VER)
  #include <type_traits>
#else
  // GCC with libstdc++
  #include <cstddef> // set __GLIBCXX__ if libstdc++.

  #if defined(__GLIBCXX__) && __GLIBCXX__ <= 20070719
  #include <tr1/type_traits>
  namespace std {
    // enable_if<bool, type>
    template <bool, class _Tp = void> struct SC_VISIBLE enable_if {};
    template <class _Tp> struct SC_VISIBLE enable_if<true, _Tp> {typedef _Tp type;};

    // conditional<bool, if, then>
    template <bool _B, class _If, class _Then>
    struct SC_VISIBLE conditional {typedef _If type;};
    template <class _If, class _Then>
    struct SC_VISIBLE conditional<false, _If, _Then> {typedef _Then type;};

    // include common traits
    using tr1::is_void;
    using tr1::is_integral;
    using tr1::is_floating_point;
    using tr1::is_array;
    using tr1::is_pointer;
    using tr1::is_member_object_pointer;
    using tr1::is_member_function_pointer;
    using tr1::is_enum;
    using tr1::is_union;
    using tr1::is_class;
    using tr1::is_function;

    using tr1::is_signed;
    using tr1::is_unsigned;
    using tr1::is_arithmetic;

    using tr1::is_const;
    using tr1::is_volatile;
  }
  #endif
#endif

#endif /* _WBC_CXX_H__ */
