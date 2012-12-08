/*
 *  logging.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Logging functions. noop or use asl(3) in release mode, and console in debug mode.
*/

#include "logging_impl.h"

// MARK: =================== Standard Logging ===================
#if !defined(DEBUG)
// MARK: Release
#  define spx_debug(format, ...) do {} while (0)
#  define spx_debugv(format, args) do {} while (0)

#  define spx_log(client, msg, level, format, ...) asl_log(client, msg, level, format, ## __VA_ARGS__)

SPX_INLINE SPX_FORMAT(4, 0)
void spx_logv(aslclient client, aslmsg msg, int level, const char *format, va_list args) {
  asl_vlog(client, msg, level, format, args);
}

#define spx_trace() do {} while (0)

#else
// MARK: Debug

#define spx_debug(format, ...)  do { \
  char _spx_prefix[256]; \
  __SPXLogGetLinePrefix(_spx_prefix, 256); \
  spx_printf("%s" format "\n", _spx_prefix, ## __VA_ARGS__); \
} while (0)

SPX_INLINE SPX_FORMAT(1, 0)
void spx_debugv(const char *format, va_list args) {
  char *str = NULL;
  if (vasprintf(&str, format, args) >= 0 && str) {
    spx_debug("%s", str);
    free(str);
  }
}

#define spx_log(client, msg, level, format, ...) do { \
  spx_debug("Log(%s): " format "\n", __SPXASLLevelString(level), ## __VA_ARGS__); \
} while (0)

SPX_INLINE SPX_FORMAT(4, 0)
void spx_logv(aslclient client, aslmsg msg, int level, const char *format, va_list args) {
  char *str = NULL;
  if (vasprintf(&str, format, args) >= 0 && str) {
    spx_log(client, msg, level, "%s", str);
    free(str);
  }
}

#define spx_trace() do { \
  spx_debug("[%s:%li]: %s\n", strrchr("/" __FILE__, '/') + 1, (long)__LINE__, __PRETTY_FUNCTION__); \
} while(0)

#endif

// MARK: Generic
#define spx_log_warning(format, ...) spx_log(NULL, NULL, ASL_LEVEL_WARNING, format, ## __VA_ARGS__)
#define spx_log_error(format, ...)   spx_log(NULL, NULL, ASL_LEVEL_ERR, format, ## __VA_ARGS__)

#if defined(__OBJC__)
// MARK: -
// MARK: =================== Objective-C Logging ===================

#if !defined(DEBUG)
// MARK: Release
#  define SPXDebug(format, ...) do {} while (0)
#  define SPXDebugv(format, ...) do {} while (0)

//void SPXLog(aslclient client, aslmsg msg, int level, NSString *format, ...) { var_args and inline are incompatible
#  define SPXLog(client, msg, level, format, ...) do { \
     NSString *_spx_str = [[NSString alloc] initWithFormat:format, ##__VA_ARGS__]; \
     if (_spx_str) { \
       asl_log(client, msg, level, "%s", [_spx_str UTF8String]); \
       spx_release(_spx_str); \
     } \
   } while (0)

SPX_INLINE SPX_NS_FORMAT(4, 0)
void SPXLogv(aslclient client, aslmsg msg, int level, NSString *format, va_list args) {
  NSString *_spx_str = [[NSString alloc] initWithFormat:format arguments:args];
  if (_spx_str) {
    asl_log(client, msg, level, "%s", [_spx_str UTF8String]);
    spx_release(_spx_str);
  }
}

#define SPXTrace() do {} while (0)

#else
// MARK: Debug

#define SPXDebug(format, ...)   do { \
  NSString *_spx_str = [[NSString alloc] initWithFormat:format, ##__VA_ARGS__]; \
  if (_spx_str) { \
    spx_debug("%s", [_spx_str UTF8String]); \
    spx_release(_spx_str); \
  } \
} while(0)

SPX_INLINE SPX_NS_FORMAT(1, 0)
void SPXDebugv(NSString *format, va_list args) {
  NSString *_spx_str = [[NSString alloc] initWithFormat:format arguments:args];
  if (_spx_str) {
    spx_debug("%s", [_spx_str UTF8String]);
    spx_release(_spx_str);
  }
}

#define SPXLog(client, msg, level, format, ...) do { \
  NSString *_spx_str = [[NSString alloc] initWithFormat:format, ##__VA_ARGS__]; \
  if (_spx_str) { \
    spx_log(client, msg, level, "%s", [_spx_str UTF8String]); \
    spx_release(_spx_str); \
  } \
} while (0)

SPX_INLINE SPX_NS_FORMAT(4, 0)
void SPXLogv(aslclient client, aslmsg msg, int level, NSString *format, va_list args) {
  NSString *_spx_str = [[NSString alloc] initWithFormat:format arguments:args];
  if (_spx_str) {
    spx_log(client, msg, level, "%s", [_spx_str UTF8String]);
    spx_release(_spx_str);
  }
}

#define SPXTrace() __SPXTrace(self, _cmd, strrchr("/" __FILE__, '/') + 1, __LINE__)

// Implementation
OBJC_EXPORT const char *class_getName(Class cls);
SPX_INLINE
void __SPXTrace(id self, SEL _cmd, const char *filename, long line) {
  Class cls = [self class];
  spx_debug("[%s:%li]: %c[%s %s]\n", filename, line, self == (id)cls ? '+' : '-', class_getName(cls), sel_getName(_cmd));
}

#endif

// MARK: Generic
#define SPXLogWarning(format, ...) SPXLog(NULL, NULL, ASL_LEVEL_WARNING, format, ## __VA_ARGS__)
#define SPXLogError(format, ...)   SPXLog(NULL, NULL, ASL_LEVEL_ERR, format, ## __VA_ARGS__)

/*!
 @abstract Log an exception with the method where it occured.
 @discussion Use NSLog when DEBUG and asl in production.
 @param exception An id representing the Exception to log.
 */
#define SPXLogException(exception) do { \
  SPXLog(NULL, NULL, ASL_LEVEL_ERR, @"%@ caught in %s (%s:%li): %@", \
         [exception respondsToSelector:@selector(name)] ? [exception name] : @"Undefined Exception" , \
         __func__, strrchr("/" __FILE__, '/') + 1, (long)__LINE__, exception); \
} while(0)

/*!
 @abstract Log an exception with the function where it occured.
 @discussion Use NSLog when DEBUG and asl in production.
 @param exception An id representing the Exception to log.
 */
#define SPXCLogException(exception) do { \
  SPXLog(NULL, NULL, ASL_LEVEL_ERR, @"%@ caught in %s() [%s:%li]: %@", \
         [exception respondsToSelector:@selector(name)] ? [exception name] : @"Undefined Exception" , \
         __func__, strrchr("/" __FILE__, '/') + 1, (long)__LINE__, exception); \
} while(0)

#endif /* __OBJC__ */
