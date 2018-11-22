//
//  Stopwatch.swift
//  Psymo
//
//  Created by Jean-Daniel Dupas on 22/11/2018.
//  Copyright © 2018 Xenonium. All rights reserved.
//

import Foundation

private let ABSOLUTE_TO_NANO_FACTOR : Double = {
  var sTimebaseInfo = mach_timebase_info();
  mach_timebase_info(&sTimebaseInfo);
  return Double(sTimebaseInfo.numer) / Double(sTimebaseInfo.denom)
}()

struct StopWatch {

  struct Unit {
    fileprivate let factor : Double

    func from(hostTime time: UInt64) -> Double {
      return Double(time) * factor
    }

    static var seconds = Unit(factor: ABSOLUTE_TO_NANO_FACTOR / 1e9)
    static var milliseconds = Unit(factor: ABSOLUTE_TO_NANO_FACTOR / 1e6)
    static var microseconds = Unit(factor: ABSOLUTE_TO_NANO_FACTOR / 1e3)
    static var nanoseconds = Unit(factor: ABSOLUTE_TO_NANO_FACTOR)
  }

  private var _start : UInt64 = 0
  private var _stop : UInt64 = 0

  mutating func start() {
    _start = mach_absolute_time()
  }

  mutating func stop(unit: Unit) -> Double {
    _stop = mach_absolute_time()
    return unit.from(hostTime: _stop - _start)
  }

  static func run(_ unit: Unit = .seconds, function: () throws -> ()) rethrows -> Double {
    var sw = StopWatch()
    sw.start()
    try function()
    return sw.stop(unit: unit)
  }
}

