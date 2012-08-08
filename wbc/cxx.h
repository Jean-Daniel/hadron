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

#include <cstddef> // set __GLIBCXX__ if libstdc++. Also define nullptr_t

// FIXME: is there a libstdc++ version that provide <type_traits> ?
#if __has_include(<type_traits>) || defined(_MSC_VER)
  #include <type_traits>

  #if defined(_MSC_VER)
  namespace std {
    using tr1::add_lvalue_reference;
  }
  #endif

#else
  // Clang/GCC with libstdc++
//  #if !defined(__GLIBCXX__) || __GLIBCXX__ <= 20101114
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

      /// @brief  helper classes [4.3].
      using tr1::integral_constant;
      using tr1::true_type;
      using tr1::false_type;

      /// @brief  primary type categories [4.5.1].
      using tr1::is_void;
      using tr1::is_integral;
      using tr1::is_floating_point;
      using tr1::is_array;
      using tr1::is_pointer;
      using tr1::is_reference;
      using tr1::is_member_object_pointer;
      using tr1::is_member_function_pointer;
      using tr1::is_enum;
      using tr1::is_union;
      using tr1::is_class;
      using tr1::is_function;

      /// @brief  composite type traits [4.5.2].
      using tr1::is_arithmetic;
      using tr1::is_fundamental;
      using tr1::is_object;
      using tr1::is_scalar;
      using tr1::is_compound;
      using tr1::is_member_pointer;

      /// @brief  type properties [4.5.3].
      using tr1::is_const;
      using tr1::is_volatile;
      using tr1::is_pod;
      using tr1::is_empty;
      using tr1::is_polymorphic;
      using tr1::is_abstract;
      using tr1::has_trivial_constructor;
      using tr1::has_trivial_copy;
      using tr1::has_trivial_assign;
      using tr1::has_trivial_destructor;
      using tr1::has_nothrow_constructor;
      using tr1::has_nothrow_copy;
      using tr1::has_nothrow_assign;
      using tr1::has_virtual_destructor;
      using tr1::is_signed;
      using tr1::is_unsigned;
      using tr1::alignment_of;
      using tr1::rank;
      using tr1::extent;

      /// @brief  relationships between types [4.6].
      using tr1::is_same;
      using tr1::is_convertible;
      using tr1::is_base_of;

      /// @brief  const-volatile modifications [4.7.1].
      using tr1::remove_const;
      using tr1::remove_volatile;
      using tr1::remove_cv;
      using tr1::add_const;
      using tr1::add_volatile;
      using tr1::add_cv;

      /// @brief  reference modifications [4.7.2].
      using tr1::remove_reference;
      //using tr1::add_reference;
      template <class _Tp> struct add_lvalue_reference {
        typedef typename tr1::add_reference<_Tp>::type type;
      };

      /// @brief  array modifications [4.7.3].
      using tr1::remove_extent;
      using tr1::remove_all_extents;

      /// @brief  pointer modifications [4.7.4].
      using tr1::remove_pointer;
      using tr1::add_pointer;

      /// @brief  other transformations [4.8].
      using tr1::aligned_storage;
    }
//  #endif
#endif

#endif /* _WBC_CXX_H__ */
