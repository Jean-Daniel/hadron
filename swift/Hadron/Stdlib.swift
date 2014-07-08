//
//  Stdlib.swift
//  Hadron
//
//  Created by Jean-Daniel on 27/06/2014.
//  Copyright (c) 2014 Xenonium. All rights reserved.
//

import Darwin

/* Provide some useful extension to the Swift Standard Library Types */

extension String {
  // Used to get a VarArg compatible type from a String.
  func withOpaquePointerToCString<Result>(body: (COpaquePointer) -> Result) -> Result {
    return self.withCString { body(COpaquePointer($0)); }
  }
}

