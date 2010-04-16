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
 @discussion A bunch of macros and inline functions usefull everywhere.
 Some of them are affected by the DEBUG precompiler macros.
 It can safely be include in C and Obj-C files.
*/

#if !defined(__WBC_LOGGING_H__)
#define __WBC_LOGGING_H__ 1

#pragma mark Logging

WB_INLINE
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

#if DEBUG
// MARK: -
// MARK: =================== Debugging Configuration ===================

// Adding a static method here is not desired, but this is for debug build only.
// And we really don't want to use NSLog as it clutters the Console

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// .hack from CoreFoundation, see comment below
WB_EXTERN
void *vproc_swap_integer(void *, int, int64_t *, int64_t *);

static
void __WBLogPrintLinePrefix(FILE *f) {
  // This hacky call is from CoreFoundation. 
  // This is the way CoreFoundation (and so NSLog) determines if it should log in stderr
  // As we only use stderr (and not asl like CF does), we use this same hack to prevent duplicate
  // prefix in Console output when not running in Xcode (lauchd already append a prefix).
  // if it could be a pipe back to launchd, ignore
  int64_t val = 0;
  // assumes val is not written to on error
  vproc_swap_integer(NULL, 5 /* VPROC_GSK_IS_MANAGED */, NULL, &val);
  if (val) return;

  /* Print date first */
  char dtime[32];
  struct timeval nows;
  gettimeofday(&nows, NULL);
  
  struct tm now;
  localtime_r(&nows.tv_sec, &now);
  strftime(dtime, 32, "%F %T.", &now);
  fwrite(dtime, 1, strlen(dtime), f);
  
  fprintf(f, "%.3u %s[%u:%x] ", nows.tv_usec / 1000, getprogname(), getpid(), pthread_mach_thread_np(pthread_self()));
}

static __attribute__((unused))
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
      uint8_t buffer[128];
      CFIndex done = CFStringGetBytes(aString, range, kCFStringEncodingUTF8, '?', false, buffer, 128, &length);
      if (done > 0) {
        fwrite(buffer, 1, done, stderr);
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

#define DCLog(format, args...)  do { \
  __WBLogPrintLinePrefix(stderr); \
  fprintf(stderr, format "\n", ## args); \
} while (0)

#define DCLogv(format, args)  do { \
  __WBLogPrintLinePrefix(stderr); \
  vfprintf(stderr, format "\n", args); \
while (0)

#define WBCLog(client, msg, level, format, args...) do { \
  __WBLogPrintLinePrefix(stderr); \
  fprintf(stderr, "Log(%s): " format "\n", __WBASLLevelString(level), ## args); \
} while (0)

WB_INLINE
void WBCLogv(aslclient client, aslmsg msg, int level, const char *format, va_list args) {
  char *str = NULL;
  if (vasprintf(&str, format, args) >= 0 && str) {
    __WBLogPrintLinePrefix(stderr);
    fprintf(stderr, "Log(%s): %s\n", __WBASLLevelString(level), str);
    free(str);
  }
}

#define WBCTrace() do { \
  __WBLogPrintLinePrefix(stderr); \
  char *__file = strdup(__FILE__); \
  fprintf(stderr, "[%s:%li]: %s()\n", __file ? basename(__file) : "", (long)__LINE__, __PRETTY_FUNCTION__); \
  if (__file) free(__file); \
} while(0)

#define WBTrace() do { \
  __WBLogPrintLinePrefix(stderr); \
  char *__file = strdup(__FILE__); \
  fprintf(stderr, "[%s:%li]: %s\n", __file ? basename(__file) : "", (long)__LINE__, __PRETTY_FUNCTION__); \
  if (__file) free(__file); \
} while(0)

#if defined (__OBJC__)
// MARK: ============= Objective-C =============
#define DLog(format, args...)   do { \
  CFStringRef __str = CFStringCreateWithFormat(kCFAllocatorDefault, NULL, (CFStringRef)format, ##args); \
  if (__str) { \
    __WBLogPrintLinePrefix(stderr); \
    __WBLogPrintString(__str, true, stderr); \
    CFRelease(__str); \
  } \
} while(0)

WB_INLINE 
void DLogv(NSString *format, va_list args) {
  CFStringRef __str = CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL, (CFStringRef)format, args);
  if (__str) {
    __WBLogPrintLinePrefix(stderr);
    __WBLogPrintString(__str, true, stderr);
    CFRelease(__str);
  }
}

WB_INLINE 
void WBLogv(aslclient client, aslmsg msg, int level, NSString *format, va_list args) {
  CFStringRef __str = CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL, (CFStringRef)format, args);
  if (__str) {
    __WBLogPrintLinePrefix(stderr);
    fprintf(stderr, "Log(%s): ", __WBASLLevelString(level));
    __WBLogPrintString(__str, true, stderr);
    CFRelease(__str);
  }
}

//WB_INLINE 
//void WBLog(aslclient client, aslmsg msg, int level, NSString *format, ...) { var_args and inline are incompatible
#define WBLog(client, msg, level, format, args...) do { \
  CFStringRef __str = CFStringCreateWithFormat(kCFAllocatorDefault, NULL, (CFStringRef)format, ##args); \
  if (__str) { \
    __WBLogPrintLinePrefix(stderr); \
    fprintf(stderr, "Log(%s): ", __WBASLLevelString(level)); \
    __WBLogPrintString(__str, true, stderr); \
    CFRelease(__str); \
  } \
} while (0)

/* Dynamic trace */
extern const char * class_getName(Class cls);
WB_INLINE
void __WBDTrace(id self, SEL _cmd, const char *filename, long line) {
  __WBLogPrintLinePrefix(stderr);
  char *__file = strdup(filename);
  fprintf(stderr, "[%s:%li]: %c[%s %s]\n", __file ? basename(__file) : "", line, self == (id)[self class] ? '+' : '-', class_getName([self class]), sel_getName(_cmd));
  if (__file) free(__file);
}

#define WBDTrace() __WBDTrace(self, _cmd, __FILE__, __LINE__)

// Property Accessor checking
#define WBProperty(propName)    NSStringFromSelector(@selector(propName))

#endif /* __OBJC__ */

#else /* DEBUG */
// MARK: =================== Release Configuration ===================

#define DCLog(format, args...) do {} while (0)
#define DCLogv(format, args) do {} while (0)

#define WBCLog(client, msg, level, format, args...) asl_log(client, msg, level, format, ## args)
WB_INLINE
void WBCLogv(aslclient client, aslmsg msg, int level, const char *format, va_list args) {
  asl_vlog(client, msg, level, format, args);
}

/*!
 @defined WBCTrace
 @abstract Print a string like: '[file:line]: function()'.
 @discussion This Macro does nothing when DEBUG is not defined
 */
#define WBCTrace() do {} while (0)

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
#define DLogv(format, args) do {} while (0)

WB_INLINE
void WBLogv(aslclient client, aslmsg msg, int level, NSString *format, va_list args) {
  NSString *__str = [[NSString alloc] initWithFormat:format arguments:args];
  if (__str) {
    asl_log(client, msg, level, "%s", [__str UTF8String]);
    [__str release];
  }
}

//WB_INLINE 
//void WBLog(aslclient client, aslmsg msg, int level, NSString *format, ...) { var_args and inline are incompatible
#define WBLog(client, msg, level, format, args...) do { \
  NSString *__str = [[NSString alloc] initWithFormat:format, ##args]; \
  if (__str) { \
    asl_log(client, msg, level, "%s", [__str UTF8String]); \
    [__str release]; \
  } \
} while (0)

/*!
 @defined WBTrace
 @abstract Print a string like: '+/-[sender selector]'.
 @discussion This Macro does nothing when DEBUG is not defined
 */
#define WBTrace() do {} while (0)
#define WBDTrace() do {} while (0)

#endif /* __OBJC__ */

#endif /* DEBUG */

/* =================== Common =================== */
#define WBCLogWarning(format, args...) WBCLog(NULL, NULL, ASL_LEVEL_WARNING, format, ## args)
#define WBCLogError(format, args...) WBCLog(NULL, NULL, ASL_LEVEL_ERR, format, ## args)

#if defined (__OBJC__)

#define WBLogWarning(format, args...) WBLog(NULL, NULL, ASL_LEVEL_WARNING, format, ## args)
#define WBLogError(format, args...) WBLog(NULL, NULL, ASL_LEVEL_ERR, format, ## args)

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
