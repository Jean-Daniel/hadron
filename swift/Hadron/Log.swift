//
//  Log.swift
//  Hadron
//
//  Created by Jean-Daniel Dupas on 20/06/2014.
//  Copyright (c) 2014 Xenonium. All rights reserved.
//

import Foundation

@asmname("pthread_mach_thread_np")
func pthread_mach_thread_np(pthread_t) -> mach_port_t;

typealias asl_object_t = COpaquePointer;
@asmname("asl_log") func asl_log(client: asl_object_t, msg: asl_object_t, level : Int, fmt : CString, args : CVaListPointer);

// This hacky call is from CoreFoundation.
// This is the way CoreFoundation (and so NSLog) determines if it should log in stderr
// As we only use stderr (and not asl like CF does), we use this same hack to prevent duplicate
// prefix in Console output when not running in Xcode (launchd already append a prefix).
// if it could be a pipe back to launchd, don't prepend a prefix
@asmname("vproc_swap_integer")
func _vproc_swap_integer(COpaquePointer, CInt, UnsafePointer<Int64>, UnsafePointer<Int64>) -> COpaquePointer;

@final
class Log {
  
  enum Level : Int {
    case Emergency = 0,
    Alert,
    Critical,
    Error,
    Warning,
    Notice,
    Info,
    Debug
  }
 
  // MARK: Convenient methods
  class func log(client: asl_object_t, msg: asl_object_t, level : Level, message : String) {
    _Shared.logger.log(client: client, msg: msg, level: level, message: message);
  }
  
  class func warn(#client: asl_object_t, msg: asl_object_t, message : String) {
    _Shared.logger.warn(client: client, msg: msg, message: message);
  }
  
  class func error(#client: asl_object_t, msg: asl_object_t, message : String) {
    _Shared.logger.error(client: client, msg: msg, message: message);
  }
  
  // MARK: Convenient methods
  func warn(#client: asl_object_t, msg: asl_object_t, message : String) {
    log(client: client, msg: msg, level: .Warning, message: message);
  }
  
  func error(#client: asl_object_t, msg: asl_object_t, message : String) {
    log(client: client, msg: msg, level: .Error, message: message);
  }
  
  // MARK: =================== Standard Logging ===================
  #if DEBUG
  class func debug(message : String) {
    _Shared.logger.debug(message);
  }
  
  class func trace(file : String = __FILE__, line : Int = __LINE__, function : String = __FUNCTION__) {
    _Shared.logger.trace(file: file, line: line, function: function);
  }
  
  func debug(message : String) {
    if _cls_vars.hasPrefix {
      var nows = timeval(tv_sec: 0, tv_usec: 0);
      gettimeofday(&nows, nil);
      let date = _cls_vars.format.stringFromDate(NSDate(timeIntervalSince1970:NSTimeInterval(nows.tv_sec)));
      "\(date).%.3u \(_cls_vars.progname)[\(getpid()):%x] %s\n".withCString { (var fmt : CString) -> Void in
        message.withOpaquePointerToCString {
          withVaList([nows.tv_usec / 1000, pthread_mach_thread_np(pthread_self()), $0]) {
            vfprintf(__stderrp, fmt, $0);
            return;
          }
        }
      }
    } else {
      "%s\n".withCString { (var str : CString) in
        message.withOpaquePointerToCString {
          withVaList([$0]) { vfprintf(__stderrp, str, $0); }
        }
      }
    }
  }
  
  func trace(file : String = __FILE__, line : Int = __LINE__, function : String = __FUNCTION__) {
    debug("[\(file.lastPathComponent):\(line)]: \(function)\n");
  }
  
  func log(#client: asl_object_t, msg: asl_object_t, level : Level, message : String) {
    debug("Log(\(level): \(message)");
  }
  
  #else
  // MARK: Release
  class func debug(message : @auto_closure () -> String) { /* noop */  }
  
  class func trace() { /* Noop */ }
  
  // Instance Methods
  func debug(message : @auto_closure () -> String) {}
  
  func trace() {}
  
  func log(#client: asl_object_t, msg: asl_object_t, level : Level, message : String) {
    "%s".withCString { (var fmt : CString) -> Void in
      message.withOpaquePointerToCString {
        withVaList([$0]) {
          asl_log(client, msg, level.toRaw(), fmt, $0);
        }
      }
    }
  }
  #endif
  
  // private:
  struct _Shared {
    static let logger = Log();
  }
  
  #if DEBUG
  struct _cls_vars {
    static let progname = String.fromCString(getprogname())
    static let hasPrefix : Bool = {
      var val : Int64 = 0;
      _vproc_swap_integer(nil, 5 /* VPROC_GSK_IS_MANAGED */, nil, &val);
      return val <= 0;
    }();

    static let format : NSDateFormatter = {
      let fmt = NSDateFormatter()
      fmt.dateFormat = "yyyy-MM-dd HH:mm:ss";
      fmt.locale = NSLocale(localeIdentifier:"en_US");
      return fmt;
    }()
  }

  #endif
}
