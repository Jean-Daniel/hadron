//
//  StdLib.swift
//  Psymo
//
//  Created by Jean-Daniel Dupas
//  Copyright © 2018 Xenonium. All rights reserved.
//

import Foundation

@inline(__always)
func with<T>(_ object: T, update: (inout T) throws -> (Void)) rethrows -> T {
  var obj = object
  try update(&obj)
  return obj
}

@objc
class _BundleAnchor : NSObject {}

extension Bundle {
  static let current : Bundle = Bundle(for: _BundleAnchor.self)
}

@inline(__always)
func LocalizedString(_ key: String, tableName: String? = nil, comment: String) -> String {
  return NSLocalizedString(key, tableName: tableName, bundle: Bundle.current, comment: comment)
}

