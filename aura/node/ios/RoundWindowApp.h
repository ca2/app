//
//  AppDelegate.h
//  teste_ios
//
//  Created by Camilo Sasuke Tsumanuma on 05/05/14.
//  Copyright (c) 2014 ca2 Desenvolvimento de Software Ltda. All rights reserved.
//

//#import <UIKit/UIKit.h>


@class AuraWindowFrameView;

@interface AuraWindowApp : UIResponder <UIApplicationDelegate, UIDocumentInteractionControllerDelegate>
{
   
@public
   
   struct plane_system * m_psystem;
   
}

@property (strong, nonatomic) UIWindow * window;
@property (strong, nonatomic) AuraWindowFrameView * view;

@end
