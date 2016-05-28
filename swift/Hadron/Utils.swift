//
//  StdLib.swift
//  Psymo
//
//  Created by Jean-Daniel on 28/05/2016.
//  Copyright © 2016 Xenonium. All rights reserved.
//

func with<T>(_ object: T, update: @noescape (inout T) throws -> (Void)) rethrows -> T {
  var obj = object
  try update(&obj)
  return obj
}
