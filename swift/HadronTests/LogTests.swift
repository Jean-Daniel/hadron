//
//  LogTests.swift
//  Hadron
//
//  Created by Jean-Daniel Dupas on 25/06/2014.
//  Copyright (c) 2014 Xenonium. All rights reserved.
//

import XCTest
import Hadron

class LogTests: XCTestCase {
  
  override func setUp() {
    super.setUp()
    // Put setup code here. This method is called before the invocation of each test method in the class.
  }
  
  override func tearDown() {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    super.tearDown()
  }
  
  var marker = false;
  
  func something() {
    marker = true;
  }
  
  func testLazyEvaluation() {
    marker = false;
    Log.debug("\(something())");
    XCTAssertFalse(marker, "Should not evaluate string expression");
  }
  
//  func testPerformanceExample() {
//    // This is an example of a performance test case.
//    self.measureBlock() {
//      // Put the code you want to measure the time of here.
//    }
//  }
  
}
