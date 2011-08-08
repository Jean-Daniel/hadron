/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Logging functions. noop or use asl(3) in release mode, and console in debug mode.
*/

#if !defined(__WBC_LOGGING_H__)
#define __WBC_LOGGING_H__ 1

#if defined(__clang__)
  #define __cfloglike(i, j) __attribute__((format(CFString, i, j)))
  #define __nsloglike(i, j) __attribute__((format(NSString, i, j)))
  #if !defined(__printflike)
    #define __printflike(i, j) __attribute__((format(printf, i, j)))
  #endif
#else
  #define __cfloglike(i, j)
  #define __nsloglike(i, j)
  #if !defined(__printflike)
    #if defined(_MSC_VER)
      #define __printflike(fmtarg, firstvararg)
    #else
      #define __printflike(fmtarg, firstvararg) __attribute__((__format__ (__printf__, fmtarg, firstvararg)))
    #endif
  #endif
#endif

// MARK: Logging
#if !defined(__APPLE__)

typedef void *aslmsg;
typedef void *aslclient;

#define asl_log(...) do {} while (0)
#define asl_vlog(...) do {} while (0)

/*! @defineblock Log Message Priority Levels
 * Log levels of the message.
 */
#define ASL_LEVEL_EMERG   0
#define ASL_LEVEL_ALERT   1
#define ASL_LEVEL_CRIT    2
#define ASL_LEVEL_ERR     3
#define ASL_LEVEL_WARNING 4
#define ASL_LEVEL_NOTICE  5
#define ASL_LEVEL_INFO    6
#define ASL_LEVEL_DEBUG   7
/*! @/defineblock */

/*! @defineblock Log Message Priority Level Strings
 * Strings corresponding to log levels.
 */
#define ASL_STRING_EMERG   "Emergency"
#define ASL_STRING_ALERT   "Alert"
#define ASL_STRING_CRIT    "Critical"
#define ASL_STRING_ERR     "Error"
#define ASL_STRING_WARNING "Warning"
#define ASL_STRING_NOTICE  "Notice"
#define ASL_STRING_INFO    "Info"
#define ASL_STRING_DEBUG   "Debug"
/*! @/defineblock */
#endif

#if DEBUG
// MARK: -
// MARK: =================== Debugging Configuration ===================

#if defined(_WIN32) && !defined(_CONSOLE)

  SC_UNUSED static
  void _wb_vprintf(LPCTSTR fmt, va_list args) {
    TCHAR stackbuf[256];
    TCHAR *buffer = stackbuf;

    size_t len = _vtcprintf_s(fmt, args) + 1; // for '\0'
    if (len > 256)
      buffer = (TCHAR *)malloc(len);

    /* write the string */
    len = _vsntprintf_s(buffer, len, len, fmt, args);
    if (len > 0)
      OutputDebugString(buffer);

    if (buffer != stackbuf)
      free(buffer);
  }

  static inline
  void _wb_printf(LPCTSTR fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _wb_vprintf(fmt, args);
    va_end(args);
  }

  #define wb_printf(fmt, ...) _wb_printf(_T(fmt), ##__VA_ARGS__)
  #define wb_vprintf(fmt, args) _wb_vprintf(_T(fmt), args)
#else
  #define wb_printf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
  #define wb_vprintf(fmt, args) vfprintf(stderr, fmt, args)
#endif

#if defined(_WIN32)

static inline
double _time_from_filetime(const FILETIME *ft) {
	double ret = (double)ft->dwHighDateTime * 429.49672960;
	ret += (double)ft->dwLowDateTime / 10000000.0;
  /* seconds between 1601 and 1970 */
	ret -= 11644473600.0;
	return ret;
}

SC_UNUSED static
void __WBLogPrintLinePrefix(FILE *f) {
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  double secs = _time_from_filetime(&ft);
  time_t t = (time_t)secs;

  struct tm now;
  char dtime[32];
  localtime_s(&now, &t);
  strftime(dtime, 32, "%Y-%m-%d %H:%M:%S", &now);

  wb_printf("%s.%.3u [%d:%d] ", dtime, (unsigned)(fmod(secs, 1) * 1000), getpid(), GetCurrentThreadId());
}

#else

#include <pthread.h>
#include <sys/time.h>

#if defined(__APPLE__) && MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5
// .hack from CoreFoundation, see comment in __WBLogPrintLinePrefix
SC_EXTERN void *vproc_swap_integer(void *, int, int64_t *, int64_t *);
#endif

// Adding a static method here is not desired, but this is for debug build only.
// And we really don't want to use NSLog as it clutters the Console
SC_UNUSED static
void __WBLogPrintLinePrefix(FILE *f) {
  // This hacky call is from CoreFoundation.
  // This is the way CoreFoundation (and so NSLog) determines if it should log in stderr
  // As we only use stderr (and not asl like CF does), we use this same hack to prevent duplicate
  // prefix in Console output when not running in Xcode (launchd already append a prefix).
  // if it could be a pipe back to launchd, ignore
#if defined(__APPLE__) && MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5
  static int64_t val = -1;
  if (val < 0) // assumes val is not written to on error
    vproc_swap_integer(NULL, 5 /* VPROC_GSK_IS_MANAGED */, NULL, &val);
  if (val > 0) return;
#endif

  /* Print date first */
  char dtime[32];
  struct timeval nows;
  gettimeofday(&nows, NULL);

  struct tm now;
  localtime_r(&nows.tv_sec, &now);
  strftime(dtime, 32, "%F %T", &now);

  fprintf(f, "%s.%.3u %s[%u:%x] ", dtime, nows.tv_usec / 1000, getprogname(), getpid(), pthread_mach_thread_np(pthread_self()));
}
#endif

SC_INLINE
const char *__WBASLLevelString(int level) {
  switch (level) {
    case ASL_LEVEL_EMERG: return ASL_STRING_EMERG;
    case ASL_LEVEL_ALERT: return ASL_STRING_ALERT;
    case ASL_LEVEL_CRIT: return ASL_STRING_CRIT;
    case ASL_LEVEL_ERR: return ASL_STRING_ERR;
    case ASL_LEVEL_WARNING: return ASL_STRING_WARNING;
    case ASL_LEVEL_NOTICE: return ASL_STRING_NOTICE;
    case ASL_LEVEL_INFO: return ASL_STRING_INFO;
    case ASL_LEVEL_DEBUG: return ASL_STRING_DEBUG;
  }
  return "????";
}

#if defined(__COREFOUNDATION__)
SC_UNUSED static
void __WBLogPrintString(CFStringRef aString, bool eol, FILE *f) {
  // Print message
  const char *cstr = NULL;
  if (!aString)
    cstr = "(null)";
  else
    cstr = CFStringGetCStringPtr(aString, kCFStringEncodingUTF8);

  if (cstr) {
    fwrite(cstr, 1, strlen(cstr), f);
  } else {
    // Fallback to slow path
    CFRange range = CFRangeMake(0, CFStringGetLength(aString));
    while (range.length > 0) {
      CFIndex length;
      uint8_t buffer[256];
      size_t done = (size_t)CFStringGetBytes(aString, range, kCFStringEncodingUTF8, '?', false, buffer, 256, &length);
      if (done > 0) {
        if (length > 0)
          fwrite(buffer, 1, (size_t)length, stderr); // lenght may be ≠ done when generating multibytes chars
        range.location += done;
        range.length -= done;
      } else {
        // abort convertion
        range.length = 0;
      }
    }
  }
  if (eol)
    fwrite("\n", 1, 1, f);
}
#endif

#define DCLog(format, ...)  do { \
  __WBLogPrintLinePrefix(stderr); \
  wb_printf(format "\n", ## __VA_ARGS__); \
} while (0)

#define DCLogv(format, args)  do { \
  __WBLogPrintLinePrefix(stderr); \
  wb_vprintf(format "\n", args); \
while (0)

#define WBCLog(client, msg, level, format, ...) do { \
  __WBLogPrintLinePrefix(stderr); \
  wb_printf("Log(%s): " format "\n", __WBASLLevelString(level), ## __VA_ARGS__); \
} while (0)

SC_INLINE
__printflike(4, 0)
void WBCLogv(aslclient client, aslmsg msg, int level, const char *format, va_list args) {
  char *str = NULL;
  if (vasprintf(&str, format, args) >= 0 && str) {
    __WBLogPrintLinePrefix(stderr);
    wb_printf("Log(%s): %s\n", __WBASLLevelString(level), str);
    free(str);
  }
}

#define WBTrace() do { \
  __WBLogPrintLinePrefix(stderr); \
  char *__file = strdup(__FILE__); \
  wb_printf("[%s:%li]: %s\n", __file ? basename(__file) : "", (long)__LINE__, __PRETTY_FUNCTION__); \
  if (__file) free(__file); \
} while(0)

// MARK: ============= Objective-C =============
#if defined (__OBJC__)

static __attribute__((unused))
__nsloglike(1, 2)
CFStringRef __WBNSStringCreateWithFormat(NSString *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  CFStringRef str = CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL, WBNSToCFString(fmt), args);
  va_end(args);
  return str;
}

SC_INLINE __cfloglike(1, 0)
CFStringRef __WBCFStringCreateWithFormatAndArguments(CFStringRef fmt, va_list args) {
  return CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL, fmt, args);
}

#define DLog(format, args...)   do { \
  CFStringRef __str = __WBNSStringCreateWithFormat(format, ##args); \
  if (__str) { \
    __WBLogPrintLinePrefix(stderr); \
    __WBLogPrintString(__str, true, stderr); \
    CFRelease(__str); \
  } \
} while(0)

SC_INLINE
__nsloglike(1, 0)
void DLogv(NSString *format, va_list args) {
  CFStringRef __str = CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL, WBNSToCFString(format), args);
  if (__str) {
    __WBLogPrintLinePrefix(stderr);
    __WBLogPrintString(__str, true, stderr);
    CFRelease(__str);
  }
}

SC_INLINE
__nsloglike(4, 0)
void WBLogv(aslclient client, aslmsg msg, int level, NSString *format, va_list args) {
  CFStringRef __str = CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL, WBNSToCFString(format), args);
  if (__str) {
    __WBLogPrintLinePrefix(stderr);
    wb_printf("Log(%s): ", __WBASLLevelString(level));
    __WBLogPrintString(__str, true, stderr);
    CFRelease(__str);
  }
}

//SC_INLINE
//void WBLog(aslclient client, aslmsg msg, int level, NSString *format, ...) { var_args and inline are incompatible
#define WBLog(client, msg, level, format, args...) do { \
  CFStringRef __str = __WBNSStringCreateWithFormat(format, ##args); \
  if (__str) { \
    __WBLogPrintLinePrefix(stderr); \
    wb_printf("Log(%s): ", __WBASLLevelString(level)); \
    __WBLogPrintString(__str, true, stderr); \
    CFRelease(__str); \
  } \
} while (0)

/* Dynamic trace */
OBJC_EXPORT const char * class_getName(Class cls);
SC_INLINE
void __WBDTrace(id self, SEL _cmd, const char *filename, long line) {
  __WBLogPrintLinePrefix(stderr);
  char *__file = strdup(filename);
  Class cls = [self class];
  wb_printf("[%s:%li]: %c[%s %s]\n", __file ? basename(__file) : "", line, self == (id)cls ? '+' : '-', class_getName(cls), sel_getName(_cmd));
  if (__file) free(__file);
}

#define WBDTrace() __WBDTrace(self, _cmd, __FILE__, __LINE__)

// Property Accessor checking
#define WBProperty(propName)    NSStringFromSelector(@selector(propName))

#endif /* __OBJC__ */

#else /* DEBUG */
// MARK: =================== Release Configuration ===================

#define DCLog(format, ...) do {} while (0)
#define DCLogv(format, args) do {} while (0)

#define WBCLog(client, msg, level, format, ...) asl_log(client, msg, level, format, ## __VA_ARGS__)
SC_INLINE
__printflike(4, 0)
void WBCLogv(aslclient client, aslmsg msg, int level, const char *format, va_list args) {
  asl_vlog(client, msg, level, format, args);
}

#define WBTrace()  do {} while (0)

#if defined (__OBJC__)
// MARK: ============= Objective-C =============
/*!
 @defined DLog
 @abstract Debug Log. This function is just a NSLog Wrapper that can enabled or disabled by the Precompiler.
 @discussion This Macro does nothing when DEBUG is not defined
 @param str A String like in NSLog.
 @param ... parameters.
 */
#define DLog(format, args...) do {} while (0)
#define DLogv(format, args)   do {} while (0)

SC_INLINE
__nsloglike(4, 0)
void WBLogv(aslclient client, aslmsg msg, int level, NSString *format, va_list args) {
  NSString *__str = [[NSString alloc] initWithFormat:format arguments:args];
  if (__str) {
    asl_log(client, msg, level, "%s", [__str UTF8String]);
    wb_release(__str);
  }
}

//SC_INLINE
//void WBLog(aslclient client, aslmsg msg, int level, NSString *format, ...) { var_args and inline are incompatible
#define WBLog(client, msg, level, format, args...) do { \
  NSString *__str = [[NSString alloc] initWithFormat:format, ##args]; \
  if (__str) { \
    asl_log(client, msg, level, "%s", [__str UTF8String]); \
    wb_release(__str); \
  } \
} while (0)

/*!
 @defined WBTrace
 @abstract Print a string like: '+/-[sender selector]'.
 @discussion This Macro does nothing when DEBUG is not defined
 */
#define WBDTrace() do {} while (0)

#endif /* __OBJC__ */

#endif /* DEBUG */

/* =================== Common =================== */
#define WBCLogWarning(format, ...) WBCLog(NULL, NULL, ASL_LEVEL_WARNING, format, ## __VA_ARGS__)
#define WBCLogError(format, ...)   WBCLog(NULL, NULL, ASL_LEVEL_ERR, format, ## __VA_ARGS__)

#if defined (__OBJC__)

#define WBLogWarning(format, args...) WBLog(NULL, NULL, ASL_LEVEL_WARNING, format, ## args)
#define WBLogError(format, args...)   WBLog(NULL, NULL, ASL_LEVEL_ERR, format, ## args)

/*!
 @defined WBLogException
 @abstract Log an exception with the method where it occured.
 @discussion Use NSLog when DEBUG and asl in production.
 @param exception An id representing the Exception to log.
 */
#define WBLogException(exception) do { \
  char *__file = strdup(__FILE__); \
  WBLog(NULL, NULL, ASL_LEVEL_ERR, @"%@ caught in %s (%s:%li): %@", \
        [exception respondsToSelector:@selector(name)] ? [exception name] : @"Undefined Exception" , \
        __func__, __file ? basename(__file) : "", (long)__LINE__, exception); \
  if (__file) free(__file); \
} while(0)

/*!
 @defined WBCLogException
 @abstract Log an exception with the function where it occured.
 @discussion Use NSLog when DEBUG and asl in production.
 @param exception An id representing the Exception to log.
 */
#define WBCLogException(exception) do { \
  char *__file = strdup(__FILE__); \
  WBLog(NULL, NULL, ASL_LEVEL_ERR, @"%@ caught in %s() [%s:%li]: %@", \
        [exception respondsToSelector:@selector(name)] ? [exception name] : @"Undefined Exception" , \
        __func__, __file ? basename(__file) : "", (long)__LINE__, exception); \
  if (__file) free(__file); \
} while(0)

#endif

#endif /* __WBC_LOGGING_H__ */
