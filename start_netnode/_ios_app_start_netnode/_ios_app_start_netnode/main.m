//
//  main.m
//  _ios_app_app
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/05/22.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
   NSString * appDelegateClassName;
   @autoreleasepool {
       // Setup code that might create autoreleased objects goes here.
       appDelegateClassName = NSStringFromClass([AppDelegate class]);
   }
   return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
