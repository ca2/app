//
//  LaunchServicesWrapper.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/05/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//


@interface LaunchServicesWrapper : NSObject


+ (BOOL)setMyselfAsDefaultApplicationForFileExtension:
  (NSString *)fileExtension;


@end



