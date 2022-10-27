//
//  AppDelegate.h
//  teste_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/05/14.
//  Copyright (c) 2014 ca2 Desenvolvimento de Software Ltda. All rights reserved.
//

//#import <UIKit/UIKit.h>


@class RoundWindowFrameImpact;

@interface RoundWindowApp : UIResponder <UIApplicationDelegate, UIDocumentInteractionControllerDelegate>
{
   
@public
   
   struct plane_system * acmesystem();
   
}

@property (strong, nonatomic) UIWindow * window;
@property (strong, nonatomic) RoundWindowFrameImpact * impact;

@end
