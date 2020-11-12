//
//  draw2d_quartzd_mm.m
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Tsumanuma on 27/10/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>





unsigned long apple_get_fonts(char ***p)
{


   NSArray *fonts = [[NSFontManager sharedFontManager] availableFontFamilies];
   
   unsigned long c = [fonts count];
   
   if(c == 0)
   {
      
      return 0;
      
   }
   
   *p = (char **) malloc(sizeof(char *) * c);
   
   for(unsigned long u = 0; u < c; u++)
   {
      
      NSString * pstr =[fonts objectAtIndex: u];
      
      (*p)[u] = strdup([pstr UTF8String]);
      
   }
   
   
   return c;


}
