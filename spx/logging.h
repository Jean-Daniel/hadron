/*
 *  logging.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2018 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Logging functions.
*/

#include <os/log.h>

// MARK: =================== Standard Logging ===================
// MARK: Generic
#define spx_log(format, ...) os_log(OS_LOG_DEFAULT, format, ## __VA_ARGS__)
#define spx_info(format, ...) os_log_info(OS_LOG_DEFAULT, format, ## __VA_ARGS__)

#define spx_log_error(format, ...) os_log_error(OS_LOG_DEFAULT, format, ## __VA_ARGS__)
#define spx_log_fault(format, ...) os_log_fault(OS_LOG_DEFAULT, format, ## __VA_ARGS__)

#if defined(DEBUG)
// MARK: Debug
#  define spx_debug(format, ...)  os_log_debug(OS_LOG_DEFAULT, format, ## __VA_ARGS__)

#  define spx_trace() spx_debug("[%s:%d]: %s", strrchr("/" __FILE__, '/') + 1, __LINE__, __PRETTY_FUNCTION__)

#else
// MARK: Release
#  define spx_debug(format, ...) do {} while (0)

#  define spx_trace() do {} while (0)
#endif

#if defined(__OBJC__)
// MARK: -
// MARK: =================== Objective-C Logging ===================

#if defined(DEBUG)
// MARK: Debug
#  define spx_trace_objc() do { \
			Class cls = [self class]; \
			spx_debug("[%s:%d]: %c[%s %s]\n", strrchr("/" __FILE__, '/') + 1, __LINE__, self == (id)cls ? '+' : '-', class_getName(cls), sel_getName(_cmd)); \
   } while(0)
#else
// MARK: Release
#  define spx_trace_objc() do {} while(0)

#endif

/*!
 @abstract Log an exception with the method where it occured.
 @discussion Use NSLog when DEBUG and asl in production.
 @param exception An id representing the Exception to log.
 */
#define spx_log_exception(exception) \
	spx_log_error("[%s:%i]: %@ caught in %s: %@", strrchr("/" __FILE__, '/') + 1, __LINE__, \
         [exception respondsToSelector:@selector(name)] ? [exception name] : @"Undefined Exception" , \
         __PRETTY_FUNCTION__, exception)

#endif /* __OBJC__ */
