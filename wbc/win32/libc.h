/*
 *  SharedPrefix.h
 *  WonderBox
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright (c) 2004 - 2008 Jean-Daniel Dupas. All rights reserved.
 */
/*!
@header SharedPrefix
 @abstract Some standard functions
*/

#if !defined(__WBC_WIN32_LIBC_H__)
#define __WBC_WIN32_LIBC_H__ 1

// io and locale do not like open macro.
// include them before defining open
#include <io.h>
#include <locale>

#include <fcntl.h>
#include <stdarg.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef SSIZE_T ssize_t;
#define SSIZE_MAX MAXSSIZE_T

#ifndef PATH_MAX
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

#define snprintf(str, length, fmt, ...) _snprintf_s(str, length, _TRUNCATE, fmt, __VA_ARGS__)

static __inline
FILE *w32_fopen(const char *file, const char *mode) {
	char bmode[32];
	bmode[0] = 'b';
	size_t length = 1;
	if (mode) {
		length += strlen(mode);
		if (length <= 30)
		 memcpy(bmode + 1, mode, length - 1);
	}
	bmode[length] = '\0';

	FILE *result;
	if (0 == fopen_s(&result, file, bmode))
		return result;
	return NULL;
}
static __inline
FILE *w32_fdopen(int fd, const char *mode) {
	char bmode[32];
	size_t length = 0;
	if (mode) {
		length = strlen(mode);
		if (length <= 30)
		  memcpy(bmode, mode, length);
		else
		  return NULL;
	}
	bmode[length] = 'b';
	bmode[length + 1] = '\0';
	return _fdopen(fd, bmode);
}

#define fopen(path, mode) w32_fopen(path, mode)
#define fdopen(fd, mode) w32_fdopen(fd, mode)

static __inline off_t ftello(FILE *stream) { return _ftelli64(stream); }
static __inline int fseeko(FILE *stream, off_t offset, int whence) { return _fseeki64(stream, offset, whence); }

#define open(path, mode, ...) _open(path, mode | O_BINARY, __VA_ARGS__)
#define close(fd) _close(fd)
#define fileno(stream) _fileno(stream)

#if defined(_WIN64)
static __inline int flsl(unsigned __int64 value) {
  unsigned long idx = 0;
  if (_BitScanReverse64(&idx, value))
    return idx + 1; // [1; 64] with 1 least significant bit
  return 0;
}
#else
static __inline int flsl(unsigned long value) {
  unsigned long idx = 0;
  if (_BitScanReverse(&idx, value))
    return idx + 1; // [1; 32] with 1 least significant bit
  return 0;
}
#endif

#ifdef _MSC_VER
  #define __builtin_popcount(var) __popcnt(var)
#endif

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

#if defined(__cplusplus)
}
#endif

#endif /* __WBC_WIN32_PROFILE_H__ */
