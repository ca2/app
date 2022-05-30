//
//  LaunchServicesWrapper.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/05/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#import <ApplicationServices/ApplicationServices.h>
#import "LaunchServicesWrapper.h"


@implementation LaunchServicesWrapper


+ (NSString *)UTIforFileExtension:(NSString *)extension
{
   
  return (NSString *)CFBridgingRelease(
    UTTypeCreatePreferredIdentifierForTag(
      kUTTagClassFilenameExtension, (__bridge CFStringRef)extension,
      NULL
    )
  );
}

+ (BOOL)setMyselfAsDefaultApplicationForFileExtension:
  (NSString *)fileExtension
{
  return LSSetDefaultRoleHandlerForContentType(
    (__bridge CFStringRef) [LaunchServicesWrapper
    UTIforFileExtension:fileExtension], kLSRolesAll,
    (__bridge CFStringRef) [[NSBundle mainBundle]
    bundleIdentifier]
  );
}

@end



void setMyselfAsDefaultApplicationForFileExtension(const char * pszExtension)
{
   
   NSString * strExtension = [ NSString stringWithUTF8String: pszExtension ];
   
   [ LaunchServicesWrapper setMyselfAsDefaultApplicationForFileExtension : strExtension];
   
}
