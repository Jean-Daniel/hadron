/*
 *  gnuc.h
 *  SharedPrefix
 *
 *  Created by Jean-Daniel Dupas.
 *  Copyright © 2004 - 2012 Jean-Daniel Dupas. All rights reserved.
 */

static __inline
void OSMemoryBarrier() { __sync_synchronize(); }

static __inline
int32_t OSAtomicAdd32(int32_t amount, volatile int32_t *value) {
  // use write barrier
  return __sync_add_and_fetch(value, amount);
}

static __inline
int32_t OSAtomicAdd32Barrier(int32_t amount, volatile int32_t *value) {
  return __sync_add_and_fetch(value, amount);
}

static __inline
int32_t OSAtomicIncrement32(volatile int32_t *value) {
  return __sync_add_and_fetch(value, 1);
}
static __inline
int32_t OSAtomicIncrement32Barrier(volatile int32_t *value) {
  return __sync_add_and_fetch(value, 1);
}

static __inline
int32_t OSAtomicDecrement32(volatile int32_t *value) {
  return __sync_sub_and_fetch(value, 1);
}
static __inline
int32_t OSAtomicDecrement32Barrier(volatile int32_t *value) {
  return __sync_sub_and_fetch(value, 1);
}

static __inline
bool OSAtomicCompareAndSwap32(int32_t oldValue, int32_t newValue, volatile int32_t *theValue) {
  return __sync_bool_compare_and_swap(theValue, newValue, oldValue);
}
static __inline
bool OSAtomicCompareAndSwap32Barrier(int32_t oldValue, int32_t newValue, volatile int32_t *theValue) {
  return __sync_bool_compare_and_swap(theValue, newValue, oldValue);
}

static __inline
int64_t OSAtomicAdd64(int64_t amount, volatile int64_t *value) {
  // use write barrier
  return __sync_add_and_fetch(value, amount);
}

static __inline
int64_t OSAtomicAdd64Barrier(int64_t amount, volatile int64_t *value) {
  return __sync_add_and_fetch(value, amount);
}

static __inline
int64_t OSAtomicIncrement64(volatile int64_t *value) {
  return __sync_add_and_fetch(value, 1);
}
static __inline
int64_t OSAtomicIncrement64Barrier(volatile int64_t *value) {
  return __sync_add_and_fetch(value, 1);
}

static __inline
int64_t OSAtomicDecrement64(volatile int64_t *value) {
  return __sync_sub_and_fetch(value, 1);
}
static __inline
int64_t OSAtomicDecrement64Barrier(volatile int64_t *value) {
  return __sync_sub_and_fetch(value, 1);
}

static __inline
bool OSAtomicCompareAndSwap64(int64_t oldValue, int64_t newValue, volatile int64_t *theValue) {
  return __sync_bool_compare_and_swap(theValue, newValue, oldValue);
}
static __inline
bool OSAtomicCompareAndSwap64Barrier(int64_t oldValue, int64_t newValue, volatile int64_t *theValue) {
  return __sync_bool_compare_and_swap(theValue, newValue, oldValue);
}
