//
//  Log.swift
//  Hadron
//
//  Created by Jean-Daniel Dupas on 20/06/2014.
//  Copyright (c) 2014 Xenonium. All rights reserved.
//

import os
import Foundation

@inline(__always)
func spx_info(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString) {
  os_log(message, dso: dso, log: log, type: .info)
}
@inline(__always)
func spx_info(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args: CVarArg) {
  os_log(message, dso: dso, log: log, type: .info, args)
}
@inline(__always)
func spx_info(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args1: CVarArg, _ args2: CVarArg) {
  os_log(message, dso: dso, log: log, type: .info, args1, args2)
}

@inline(__always)
func spx_log(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString) {
  os_log(message, dso: dso, log: log, type: .default)
}
@inline(__always)
func spx_log(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args: CVarArg) {
  os_log(message, dso: dso, log: log, type: .default, args)
}
@inline(__always)
func spx_log(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args1: CVarArg, _ args2: CVarArg) {
  os_log(message, dso: dso, log: log, type: .default, args1, args2)
}

@inline(__always)
func spx_error(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString) {
  os_log(message, dso: dso, log: log, type: .error)
}
@inline(__always)
func spx_error(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args: CVarArg) {
  os_log(message, dso: dso, log: log, type: .error, args)
}
@inline(__always)
func spx_error(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args1: CVarArg, _ args2: CVarArg) {
  os_log(message, dso: dso, log: log, type: .error, args1, args2)
}

#if DEBUG
@inline(__always)
func spx_debug(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString) {
  os_log(message, dso: dso, log: log, type: .debug)
}
@inline(__always)
func spx_debug(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args: CVarArg) {
  os_log(message, dso: dso, log: log, type: .debug, args)
}
@inline(__always)
func spx_debug(dso: UnsafeRawPointer = #dsohandle, log: OSLog = OSLog.default, _ message: StaticString, _ args1: CVarArg, _ args2: CVarArg) {
  os_log(message, dso: dso, log: log, type: .debug, args1, args2)
}

@inline(__always)
func spx_trace(args: String = "", file : String = #file, line : Int = #line, function : String = #function, dso: UnsafeRawPointer? = #dsohandle) {
  let filename = (file as NSString).lastPathComponent
  os_log("[%@:%d]: %@ (%@)", dso: dso, log: OSLog.default, type: .debug, filename, line, function, args)
}
#else
// MARK: Release
@inline(__always)
func spx_debug(log: OSLog = OSLog.default, _ message: StaticString, _ args: CVarArg...) { /* noop */  }

@inline(__always)
func spx_trace(args: @autoclosure () -> String = "") { /* Noop */ }
#endif
