//
//  StdLib.swift
//  Psymo
//
//  Created by Jean-Daniel on 28/05/2016.
//  Copyright © 2016 Xenonium. All rights reserved.
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

private let _self_bundle : Bundle = Bundle(for: _BundleAnchor.self)

@inline(__always)
func LocalizedString(_ key: String, tableName: String? = nil, comment: String) -> String {
  return NSLocalizedString(key, tableName: tableName, bundle: _self_bundle, comment: comment)
}

