/*
 *  logging.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */
/*!
 @abstract Windows Logging
*/

#include <time.h>

// MARK: -
// MARK: Windows logging
#if defined(_CONSOLE)
#  define spx_printf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#  define spx_vprintf(fmt, args) vfprintf(stderr, fmt, args)
#else

SPX_UNUSED static
void _spx_vprintf(const char *fmt, va_list args) {
  char stackbuf[256];
  char *buffer = stackbuf;

  size_t len = _vcprintf_s(fmt, args) + 1; // for '\0'
  if (len > 256)
    buffer = new char[len];

  /* write the string */
  len = vsnprintf_s(buffer, len, len, fmt, args);
  if (len > 0)
    OutputDebugStringA(buffer);

  if (buffer != stackbuf)
    delete[] buffer;
}

static inline
void _spx_printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  _spx_vprintf(fmt, args);
  va_end(args);
}

#  define spx_printf(fmt, ...) _spx_printf(fmt, ##__VA_ARGS__)
#  define spx_vprintf(fmt, args) _spx_vprintf(fmt, args)

#endif

static inline
double _time_from_filetime(const FILETIME *ft) {
	double ret = (double)ft->dwHighDateTime * 429.49672960;
	ret += (double)ft->dwLowDateTime / 10000000.0;
  /* seconds between 1601 and 1970 */
	ret -= 11644473600.0;
	return ret;
}

static inline
void __SPXLogGetLinePrefix(char *buffer, size_t length) {
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  double secs = _time_from_filetime(&ft);
  time_t t = (time_t)secs;

  struct tm now;
  char dtime[32];
  localtime_s(&now, &t);
  strftime(dtime, 32, "%Y-%m-%d %H:%M:%S", &now);

  _snprintf_s(buffer, length, _TRUNCATE, "%s.%.3u [%d:%d] ", dtime, (unsigned)(fmod(secs, 1) * 1000), getpid(), GetCurrentThreadId());
}

