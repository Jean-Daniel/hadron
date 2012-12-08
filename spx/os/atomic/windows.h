/*
 *  windows.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */

#include <intrin.h>

static __inline
void OSMemoryBarrier() {
  _ReadWriteBarrier();
}

static __inline
int32_t OSAtomicAdd32(int32_t amount, volatile int32_t *value) {
  // use write barrier
  return InterlockedExchangeAdd((volatile LONG *)value, amount);
}

static __inline
int32_t OSAtomicAdd32Barrier(int32_t amount, volatile int32_t *value) {
  return InterlockedExchangeAdd((volatile LONG *)value, amount);
}

static __inline
int32_t OSAtomicIncrement32(volatile int32_t *value) {
  return InterlockedIncrement((volatile LONG *)value);
}
static __inline
int32_t OSAtomicIncrement32Barrier(volatile int32_t *value) {
  return InterlockedIncrement((volatile LONG *)value);
}

static __inline
int32_t OSAtomicDecrement32(volatile int32_t *value) {
  return InterlockedDecrement((volatile LONG *)value);
}
static __inline
int32_t OSAtomicDecrement32Barrier(volatile int32_t *value) {
  return InterlockedDecrement((volatile LONG *)value);
}

static __inline
bool OSAtomicCompareAndSwap32(int32_t oldValue, int32_t newValue, volatile int32_t *theValue) {
  return oldValue == InterlockedCompareExchange((volatile LONG *)theValue, newValue, oldValue);
}
static __inline
bool OSAtomicCompareAndSwap32Barrier(int32_t oldValue, int32_t newValue, volatile int32_t *theValue) {
  return oldValue == InterlockedCompareExchange((volatile LONG *)theValue, newValue, oldValue);
}

// Mark: -
// Mark: 64 bits functions
#if (_WIN32_WINNT >= 0x0502)
  #define WIN32_ATOMIC_64 1
#else
  #define WIN32_ATOMIC_64 0
#endif

#if WIN32_ATOMIC_64
static __inline
int64_t OSAtomicAdd64(int64_t amount, volatile int64_t *value) {
  // use write barrier
  return InterlockedExchangeAdd64((volatile LONGLONG *)value, amount);
}

static __inline
int64_t OSAtomicAdd64Barrier(int64_t amount, volatile int64_t *value) {
  return InterlockedExchangeAdd64((volatile LONGLONG *)value, amount);
}

static __inline
int64_t OSAtomicIncrement64(volatile int64_t *value) {
  return InterlockedIncrement64((volatile LONGLONG *)value);
}
static __inline
int64_t OSAtomicIncrement64Barrier(volatile int64_t *value) {
  return InterlockedIncrement64((volatile LONGLONG *)value);
}

static __inline
int64_t OSAtomicDecrement64(volatile int64_t *value) {
  return InterlockedDecrement64((volatile LONGLONG *)value);
}
static __inline
int64_t OSAtomicDecrement64Barrier(volatile int64_t *value) {
  return InterlockedDecrement64((volatile LONGLONG *)value);
}

static __inline
bool OSAtomicCompareAndSwap64(int64_t oldValue, int64_t newValue, volatile int64_t *theValue) {
  return oldValue == InterlockedCompareExchange64((volatile LONGLONG *)theValue, newValue, oldValue);
}
static __inline
bool OSAtomicCompareAndSwap64Barrier(int64_t oldValue, int64_t newValue, volatile int64_t *theValue) {
  return oldValue == InterlockedCompareExchange64((volatile LONGLONG *)theValue, newValue, oldValue);
}
#endif
