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

#if defined(__APPLE__)
#  include <asl.h>
#else
typedef void *aslmsg;
typedef void *aslclient;

/*! @defineblock Log Message Priority Levels
 * Log levels of the message.
 */
#  define ASL_LEVEL_EMERG   0
#  define ASL_LEVEL_ALERT   1
#  define ASL_LEVEL_CRIT    2
#  define ASL_LEVEL_ERR     3
#  define ASL_LEVEL_WARNING 4
#  define ASL_LEVEL_NOTICE  5
#  define ASL_LEVEL_INFO    6
#  define ASL_LEVEL_DEBUG   7
/*! @/defineblock */

/*! @defineblock Log Message Priority Level Strings
 * Strings corresponding to log levels.
 */
#  define ASL_STRING_EMERG   "Emergency"
#  define ASL_STRING_ALERT   "Alert"
#  define ASL_STRING_CRIT    "Critical"
#  define ASL_STRING_ERR     "Error"
#  define ASL_STRING_WARNING "Warning"
#  define ASL_STRING_NOTICE  "Notice"
#  define ASL_STRING_INFO    "Info"
#  define ASL_STRING_DEBUG   "Debug"
/*! @/defineblock */

#if defined(_WIN32)
#  include <win32\logging.h>
#  define asl_log(...) do {} while (0)
#  define asl_vlog(...) do {} while (0)
#else
// Using syslog when asl not available
#  include <sys/syslog.h>

#  define asl_log(client, msg, level, format, ...) syslog(level, format, ## __VA_ARGS__)
#  define asl_vlog(client, msg, level, format, args) vsyslog(level, format, args)
#endif /* _WIN32 */

#endif /* __APPLE__ */

#if defined(DEBUG)

#include <sys/time.h>

SPX_EXTERN pthread_t pthread_self(void);

#if defined(__APPLE__)
SPX_EXTERN mach_port_t pthread_mach_thread_np(pthread_t);
// .hack from CoreFoundation, see comment in __SPXLogGetLinePrefix
SPX_EXTERN void *vproc_swap_integer(void *, int, int64_t *, int64_t *);
#endif

#ifndef _WIN32
#  define spx_printf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#  define spx_vprintf(fmt, args) vfprintf(stderr, fmt, args)
#endif

// Adding a static method here is not desirable, but this is for debug build only.
// And we really don't want to use NSLog as it clutters the Console
SPX_UNUSED static
void __SPXLogGetLinePrefix(char *buffer, size_t length) {
  // This hacky call is from CoreFoundation.
  // This is the way CoreFoundation (and so NSLog) determines if it should log in stderr
  // As we only use stderr (and not asl like CF does), we use this same hack to prevent duplicate
  // prefix in Console output when not running in Xcode (launchd already append a prefix).
  // if it could be a pipe back to launchd, ignore
#if defined(__APPLE__)
  static int64_t val = -1;
  if (val < 0) // assumes val is not written to on error
    vproc_swap_integer(NULL, 5 /* VPROC_GSK_IS_MANAGED */, NULL, &val);
  if (val > 0) {
    buffer[0] = '\0';
    return;
  }
#endif
  
  /* Print date first */
  char dtime[32];
  struct timeval nows;
  gettimeofday(&nows, NULL);
  
  struct tm now;
  localtime_r(&nows.tv_sec, &now);
  strftime(dtime, 32, "%F %T", &now);
  
  snprintf(buffer, length, "%s.%.3u %s[%u:%x] ", dtime, nows.tv_usec / 1000, getprogname(), getpid(), pthread_mach_thread_np(pthread_self()));
}

SPX_INLINE
const char *__SPXASLLevelString(int level) {
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

#endif // DEBUG

