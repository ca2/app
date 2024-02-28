//
//  LaunchServicesWrapper.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 30/05/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//


@interface LaunchServicesWrapper : NSObject


+ (BOOL)setMyselfAsDefaultApplicationForFileExtension:
  (NSString *)fileExtension;


@end



