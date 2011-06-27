/*
 *  SharedPrefix.h
 *  WBConfig
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2011 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Some standard functions
*/

#if !defined(__WBC_WIN32_LIBC_H__)
#define __WBC_WIN32_LIBC_H__ 1

#include <io.h>
#include <fcntl.h>
#include <stdarg.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef SSIZE_T ssize_t;
#if !defined(SSIZE_MAX)
  #define SSIZE_MAX MAXSSIZE_T
#endif

#if !defined(PATH_MAX)
  #define PATH_MAX 2048
#endif

#define MAXPATHLEN PATH_MAX

static __inline
DWORD GetLastErrorOrDefault() {
  DWORD err = GetLastError();
  return err ? err : -1;
}

static __forceinline
void sleep(int seconds) {
  Sleep(seconds * 1000);
}
static __forceinline
void usleep(unsigned long usecs) {
  if (usecs > 0UL)
     Sleep(((usecs + 999UL) / 1000UL));
}

static __forceinline
DWORD getpid() {
  return GetCurrentProcessId();
}

static __forceinline
int setenv(const char *name, const char *value, int overwrite) {
  return SetEnvironmentVariableA(name, value) ? 0 : GetLastErrorOrDefault();
}

static __forceinline
int setlinebuf(FILE *f) {
  return setvbuf(f, (char *)NULL, _IOLBF, BUFSIZ);
}

static __inline
const char *w32_getfmode(const char *mode, char bmode[32]) {
  /* is "b" already present ? */
  if (mode && strchr(mode, 'b'))
    return mode;

  size_t length = 0;
	if (mode) {
		length = strlen(mode);
		if (length <= 30)
		  memcpy(bmode, mode, length);
		else
		  return mode;
	}
  bmode[length] = 'b';
  bmode[length + 1] = '\0';
  return bmode;
}

static __inline
FILE *w32_fopen(const char *file, const char *mode) {
  FILE *result;
	char bmode[32];
	if (0 == fopen_s(&result, file, w32_getfmode(mode, bmode)))
		return result;
	return NULL;
}
static __inline
FILE *w32_fdopen(int fd, const char *mode) {
	char bmode[32];
	return _fdopen(fd, w32_getfmode(mode, bmode));
}

#define fopen(path, mode) w32_fopen(path, mode)
#define fdopen(fd, mode) w32_fdopen(fd, mode)

static __forceinline int ftruncate(int fd, __int64 size) {
	int err = _chsize_s(fd, size);
	if (!err) return 0;
	/* match posix version and set errno instead of returning it */
	_set_errno(err);
	return -1;
}

static __forceinline off_t ftello(FILE *stream) { return _ftelli64(stream); }
static __forceinline int fseeko(FILE *stream, off_t offset, int whence) { return _fseeki64(stream, offset, whence); }

// May conflict with open and close function defined afterwards (member function for instance)
// #define open(path, mode, ...) _open(path, mode | O_BINARY, ##__VA_ARGS__)
// #define close(fd) _close(fd)
// #define fileno(stream) _fileno(stream)

/* String */
#define snprintf(str, length, fmt, ...) _snprintf_s(str, length, _TRUNCATE, fmt, ##__VA_ARGS__)
//#define snscanf(str, len, format, ...) _snscanf_s(str, len, format, ##__VA_ARGS__)

static __forceinline int strcasecmp(const char *string1, const char *string2) { return _stricmp(string1, string2); }
static __forceinline int strncasecmp(const char *string1, const char *string2, size_t count) { return _strnicmp(string1, string2, count); }
/* Date Time */
static __forceinline time_t timegm(struct tm * const tmtime) { return _mkgmtime(tmtime); }
static __forceinline struct tm *gmtime_r(const time_t *clock, struct tm *result) { return (0 == gmtime_s(result, clock)) ? result : NULL; }

static __inline
int _NSGetExecutablePath(char *filename, uint32_t *length) {
  uint32_t bsize = *length;
  *length = GetModuleFileNameA(NULL, filename, *length);
  if (*length > 0) {
    /* make sure the string is zero terminated */
    if (*length == bsize) filename[bsize-1] = '\0';
    return 0;
  } else {
    return GetLastErrorOrDefault();
  }
}

static
int vasprintf( char **sptr, const char *fmt, va_list argv )  {
    int wanted = vsnprintf_s( *sptr = NULL, 0, 0, fmt, argv );
    if( (wanted > 0) && ((*sptr = (char *)malloc( 1 + wanted )) != NULL) )
        return vsnprintf_s( *sptr, 1 + wanted, 1 + wanted, fmt, argv );

    return wanted;
}

static
int asprintf( char **sptr, const char *fmt, ... ) {
    int retval;
    va_list argv;
    va_start( argv, fmt );
    retval = vasprintf( sptr, fmt, argv );
    va_end( argv );
    return retval;
}

/* functions defined in winrt */
extern char *basename(const char *path);
extern char *dirname(char *path);

extern char *strcasestr(const char* phaystack, const char* pneedle);

extern size_t strlcat(char *strDest, const char *strSource, size_t count);
extern size_t strlcpy(char *strDest, const char *strSource, size_t count);

extern char *strptime(const char *buf, const char *format, struct tm *tm);
// strftime is defined in windows.

#if defined(__cplusplus)
}
#endif

#endif /* __WBC_WIN32_PROFILE_H__ */
