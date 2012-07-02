/*
 *  SCDefine.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2012 Jean-Daniel Dupas. All rights reserved.
 */

#if !defined(__SC_DEFINE_H__)
#define __SC_DEFINE_H__ 1

// MARK: Clang Macros
#ifndef __has_builtin
  #define __has_builtin(x) __has_builtin ## x
#endif

#ifndef __has_attribute
  #define __has_attribute(x) __has_attribute ## x
#endif

#ifndef __has_feature
  #define __has_feature(x) __has_feature ## x
#endif

#ifndef __has_extension
  #define __has_extension(x) __has_feature(x)
#endif

#ifndef __has_include
  #define __has_include(x) 0
#endif

#ifndef __has_include_next
  #define __has_include_next(x) 0
#endif

// MARK: Visibility
#if defined(_WIN32)
  #define SC_HIDDEN

  #if defined(SC_STATIC_LIBRARY)
      #define SC_VISIBLE
  #else
    #if defined(SC_SYMBOLS_EXPORTS)
      #define SC_VISIBLE __declspec(dllexport)
    #else
      #define SC_VISIBLE __declspec(dllimport)
    #endif
  #endif
#endif

#if !defined(SC_VISIBLE)
  #define SC_VISIBLE __attribute__((__visibility__("default")))
#endif

#if !defined(SC_HIDDEN)
  #define SC_HIDDEN __attribute__((__visibility__("hidden")))
#endif

#if !defined(SC_EXTERN)
  #if defined(__cplusplus)
    #define SC_EXTERN extern "C"
  #else
    #define SC_EXTERN extern
  #endif
#endif

/* SC_EXPORT SC_PRIVATE should be used on
 extern variables and functions declarations */
#if !defined(SC_EXPORT)
  #define SC_EXPORT SC_EXTERN SC_VISIBLE
#endif

#if !defined(SC_PRIVATE)
  #define SC_PRIVATE SC_EXTERN SC_HIDDEN
#endif

// MARK: Inline
#if defined(__cplusplus) && !defined(__inline__)
  #define __inline__ inline
#endif

#if !defined(SC_INLINE)
  #if !defined(__NO_INLINE__)
    #if defined(_MSC_VER)
      #define SC_INLINE __forceinline static
    #else
      #define SC_INLINE __inline__ __attribute__((__always_inline__)) static
    #endif
  #else
    #define SC_INLINE __inline__ static
  #endif /* No inline */
#endif

// MARK: Attributes
#if !defined(SC_NORETURN)
  #if defined(_MSC_VER)
    #define SC_NORETURN __declspec(noreturn)
  #else
    #define SC_NORETURN __attribute__((__noreturn__))
  #endif
#endif

#if !defined(SC_DEPRECATED)
  #if defined(_MSC_VER)
    #define SC_DEPRECATED(msg) __declspec(deprecated(msg))
  #elif defined(__clang__)
    #define SC_DEPRECATED(msg) __attribute__((__deprecated__(msg)))
  #else
    #define SC_DEPRECATED(msg) __attribute__((__deprecated__))
  #endif
#endif

#if !defined(SC_UNUSED)
  #if defined(_MSC_VER)
    #define SC_UNUSED
  #else
    #define SC_UNUSED __attribute__((__unused__))
  #endif
#endif

#if !defined(SC_REQUIRES_NIL_TERMINATION)
  #if defined(_MSC_VER)
    #define SC_REQUIRES_NIL_TERMINATION
  #elif defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
    #define SC_REQUIRES_NIL_TERMINATION __attribute__((__sentinel__(0,1)))
  #else
    #define SC_REQUIRES_NIL_TERMINATION __attribute__((__sentinel__))
  #endif
#endif

#if !defined(SC_REQUIRED_ARGS)
  #if defined(_MSC_VER)
    #define SC_REQUIRED_ARGS(idx, ...)
  #else
    #define SC_REQUIRED_ARGS(idx, ...) __attribute__((__nonnull__(idx, ##__VA_ARGS__)))
  #endif
#endif

#if !defined(SC_FORMAT)
  #if defined(_MSC_VER)
    #define SC_FORMAT(fmtarg, firstvararg)
  #else
    #define SC_FORMAT(fmtarg, firstvararg) __attribute__((__format__ (__printf__, fmtarg, firstvararg)))
  #endif
#endif

#if !defined(SC_CF_FORMAT)
  #if defined(__clang__)
    #define SC_CF_FORMAT(i, j) __attribute__((__format__(__CFString__, i, j)))
  #else
    #define SC_CF_FORMAT(i, j)
  #endif
#endif

#if !defined(SC_NS_FORMAT)
  #if defined(__clang__)
    #define SC_NS_FORMAT(i, j) __attribute__((__format__(__NSString__, i, j)))
  #else
    #define SC_NS_FORMAT(i, j)
  #endif
#endif

// MARK: -
// MARK: Static Analyzer
#ifndef CF_CONSUMED
  #if __has_attribute(__cf_consumed__)
    #define CF_CONSUMED __attribute__((__cf_consumed__))
  #else
    #define CF_CONSUMED
  #endif
#endif

#ifndef CF_RETURNS_RETAINED
  #if __has_attribute(__cf_returns_retained__)
    #define CF_RETURNS_RETAINED __attribute__((__cf_returns_retained__))
  #else
    #define CF_RETURNS_RETAINED
  #endif
#endif

#ifndef CF_RETURNS_NOT_RETAINED
	#if __has_attribute(__cf_returns_not_retained__)
		#define CF_RETURNS_NOT_RETAINED __attribute__((__cf_returns_not_retained__))
	#else
		#define CF_RETURNS_NOT_RETAINED
	#endif
#endif


#if defined(__cplusplus)

/* SC_CXX_EXPORT and SC_CXX_PRIVATE can be used
 to define C++ classes visibility. */
#if defined(__cplusplus)
  #if !defined(SC_CXX_PRIVATE)
    #define SC_CXX_PRIVATE SC_HIDDEN
  #endif

  #if !defined(SC_CXX_EXPORT)
    #define SC_CXX_EXPORT SC_VISIBLE
  #endif
#endif

// VisualStudio 2010
#if defined(_MSC_VER) && _MSC_VER >= 1600
  #define __has_feature__cxx_nullptr__ 1
  #define __has_feature__cxx_auto_type__ 1
  #define __has_feature__cxx_static_assert__ 1
  #define __has_feature__cxx_trailing_return__ 1
  #define __has_feature__cxx_override_control__ 1
  #define __has_feature__cxx_rvalue_references__ 1
  #define __has_feature__cxx_local_type_template_args__ 1
#endif

// VisualStudio 2011
#if defined(_MSC_VER) && _MSC_VER >= 1700
  #define __has_feature__cxx_lambdas__ 1
  #define __has_feature__cxx_decltype__ 1
  #define __has_feature__cxx_range_for__ 1
#endif

// MARK: C++ 2011
#if __has_extension(__cxx_override_control__)
  #if !defined(_MSC_VER) || _MSC_VER >= 1700
    #define sc_final final
  #else
    #define sc_final sealed
  #endif
  #define sc_override override
#else
  // not supported
  #define sc_final
  #define sc_override
#endif

#if __has_extension(__cxx_nullptr__)
  #undef NULL
  #define NULL nullptr
#else
  // use the standard declaration
#endif

#if __has_extension(__cxx_noexcept__)
  #define sc_noexcept noexcept
  #define sc_noexcept_(arg) noexcept(arg)
#else
  #define sc_noexcept
  #define sc_noexcept_(arg)
#endif

#if __has_extension(__cxx_constexpr__)
  #define sc_constexpr constexpr
#else
  #define sc_constexpr
#endif

#if __has_extension(__cxx_rvalue_references__)
  /* declaration for move, swap, forward, ... */
  #define sc_move(arg) std::move(arg)
  #define sc_forward(Ty, arg) std::forward<Ty>(arg)
#else
  #define sc_move(arg) arg
  #define sc_forward(Ty, arg) arg
#endif

#if __has_extension(__cxx_deleted_functions__)
  #define sc_deleted = delete
#else
  #define sc_deleted
#endif

// MARK: Other C++ macros

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#ifndef SC_DISALLOW_COPY_AND_ASSIGN
  #define SC_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    private: \
     TypeName(const TypeName&) sc_deleted; \
     void operator=(const TypeName&) sc_deleted
#endif

#ifndef SC_DISALLOW_MOVE
  #if __has_extension(__cxx_rvalue_references__)
    #define SC_DISALLOW_MOVE(TypeName) \
      private: \
       TypeName(TypeName&&) sc_deleted; \
       void operator=(TypeName&&) sc_deleted
  #else
    #define SC_DISALLOW_MOVE(TypeName)
  #endif
#endif

#ifndef SC_DISALLOW_COPY_ASSIGN_MOVE
  #define SC_DISALLOW_COPY_ASSIGN_MOVE(TypeName) \
    SC_DISALLOW_MOVE(TypeName);                  \
    SC_DISALLOW_COPY_AND_ASSIGN(TypeName)
#endif

#endif /* __cplusplus */

#if defined(__OBJC__)

/* SC_OBJC_EXPORT and SC_OBJC_PRIVATE can be used
 to define ObjC classes visibility. */
#if !defined(SC_OBJC_PRIVATE)
  #if __LP64__
    #define SC_OBJC_PRIVATE SC_HIDDEN
  #else
    #define SC_OBJC_PRIVATE
  #endif /* 64 bits runtime */
#endif

#if !defined(SC_OBJC_EXPORT)
  #if __LP64__
    #define SC_OBJC_EXPORT SC_VISIBLE
  #else
    #define SC_OBJC_EXPORT
  #endif /* 64 bits runtime */
#endif

// MARK: Static Analyzer
#ifndef SC_UNUSED_IVAR
  #if __has_extension(__attribute_objc_ivar_unused__)
    #define SC_UNUSED_IVAR __attribute__((__unused__))
  #else
    #define SC_UNUSED_IVAR
  #endif
#endif

#ifndef NS_CONSUMED
  #if __has_attribute(__ns_consumed__)
    #define NS_CONSUMED __attribute__((__ns_consumed__))
  #else
    #define NS_CONSUMED
  #endif
#endif

#ifndef NS_CONSUMES_SELF
  #if __has_attribute(__ns_consumes_self__)
    #define NS_CONSUMES_SELF __attribute__((__ns_consumes_self__))
  #else
    #define NS_CONSUMES_SELF
  #endif
#endif

#ifndef NS_RETURNS_RETAINED
  #if __has_attribute(__ns_returns_retained__)
    #define NS_RETURNS_RETAINED __attribute__((__ns_returns_retained__))
  #else
    #define NS_RETURNS_RETAINED
  #endif
#endif

#ifndef NS_RETURNS_NOT_RETAINED
  #if __has_attribute(__ns_returns_not_retained__)
    #define NS_RETURNS_NOT_RETAINED __attribute__((__ns_returns_not_retained__))
  #else
    #define NS_RETURNS_NOT_RETAINED
  #endif
#endif

#ifndef NS_RETURNS_AUTORELEASED
  #if __has_attribute(__ns_returns_autoreleased__)
    #define NS_RETURNS_AUTORELEASED __attribute__((__ns_returns_autoreleased__))
  #else
    #define NS_RETURNS_AUTORELEASED
  #endif
#endif

/* Method Family */
#ifndef NS_METHOD_FAMILY
  /* supported families are: none, alloc, copy, init, mutableCopy, and new. */
  #if __has_attribute(__ns_returns_autoreleased__)
    #define NS_METHOD_FAMILY(family) __attribute__((objc_method_family(family)))
  #else
    #define NS_METHOD_FAMILY(arg)
  #endif
#endif

// gracefully degrade
#if !__has_feature(__objc_instancetype__)
  #define instancetype id
#endif

#endif /* ObjC */


#endif /* __SC_DEFINE_H__ */
