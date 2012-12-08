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

// MARK: -
// MARK: Windows logging
#if !defined(_CONSOLE)

SPX_UNUSED static
void _spx_vprintf(LPCTSTR fmt, va_list args) {
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
void _spx_printf(LPCTSTR fmt, ...) {
  va_list args;
  va_start(args, fmt);
  _spx_vprintf(fmt, args);
  va_end(args);
}

#  define wb_printf(fmt, ...) _spx_printf(_T(fmt), ##__VA_ARGS__)
#  define wb_vprintf(fmt, args) _spx_vprintf(_T(fmt), args)
#else
#  define wb_printf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#  define wb_vprintf(fmt, args) vfprintf(stderr, fmt, args)
#endif

static inline
double _time_from_filetime(const FILETIME *ft) {
	double ret = (double)ft->dwHighDateTime * 429.49672960;
	ret += (double)ft->dwLowDateTime / 10000000.0;
  /* seconds between 1601 and 1970 */
	ret -= 11644473600.0;
	return ret;
}

SPX_UNUSED static
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

