//
//  _ios_app_appUITestsLaunchTests.m
//  _ios_app_appUITests
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/05/22.
//

#import <XCTest/XCTest.h>

@interface _ios_app_appUITestsLaunchTests : XCTestCase

@end

@implementation _ios_app_appUITestsLaunchTests

+ (BOOL)runsForEachTargetApplicationUIConfiguration {
    return YES;
}

- (void)setUp {
    self.continueAfterFailure = NO;
}

- (void)testLaunch {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app launch];

    // Insert steps here to perform after app launch but before taking a screenshot,
    // such as logging into a test account or navigating somewhere in the app

    XCTAttachment *attachment = [XCTAttachment attachmentWithScreenshot:XCUIScreen.mainScreen.screenshot];
    attachment.name = @"Launch Screen";
    attachment.lifetime = XCTAttachmentLifetimeKeepAlways;
    [self addAttachment:attachment];
}

@end
