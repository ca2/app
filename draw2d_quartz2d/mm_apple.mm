//
//  draw2d_mm_apple.m
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Tsumanuma on 25/08/18.
//  Copyright © 2018 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#import <Foundation/Foundation.h>

#ifdef MACOS
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#ifdef MACOS
#define kCTFontWeightUltraLight NSFontWeightUltraLight
#define kCTFontWeightThin NSFontWeightThin
#define kCTFontWeightLight NSFontWeightLight
#define kCTFontWeightRegular NSFontWeightRegular
#define kCTFontWeightMedium NSFontWeightMedium
#define kCTFontWeightSemibold NSFontWeightSemibold
#define kCTFontWeightBold NSFontWeightBold
#define kCTFontWeightHeavy NSFontWeightHeavy
#define kCTFontWeightBlack NSFontWeightBlack
#else
#define kCTFontWeightUltraLight UIFontWeightUltraLight
#define kCTFontWeightThin UIFontWeightThin
#define kCTFontWeightLight UIFontWeightLight
#define kCTFontWeightRegular UIFontWeightRegular
#define kCTFontWeightMedium UIFontWeightMedium
#define kCTFontWeightSemibold UIFontWeightSemibold
#define kCTFontWeightBold UIFontWeightBold
#define kCTFontWeightHeavy UIFontWeightHeavy
#define kCTFontWeightBlack UIFontWeightBlack
#endif

//#define FW_THIN             100
//#define FW_EXTRALIGHT       200
//#define FW_LIGHT            300
//#define FW_NORMAL           400
//#define FW_MEDIUM           500
//#define FW_SEMIBOLD         600
//#define FW_BOLD             700
//#define FW_EXTRABOLD        800
//#define FW_HEAVY            900


double nsfont_get_ctweight(int iWeight)
{
   
   double dCoreTextWeight = kCTFontWeightRegular;
   
   if (iWeight < FW_THIN + 50)
   {
      
      dCoreTextWeight = kCTFontWeightUltraLight;
      
   }
   else if (iWeight < FW_EXTRALIGHT + 50)
   {
      
      dCoreTextWeight = kCTFontWeightThin;
      
   }
   else if (iWeight < FW_LIGHT + 50)
   {

      dCoreTextWeight = kCTFontWeightLight;
      
   }
   else if (iWeight < FW_NORMAL + 50)
   {

      dCoreTextWeight = kCTFontWeightRegular;
      
   }
   else if (iWeight < FW_MEDIUM + 50)
   {

      dCoreTextWeight = kCTFontWeightMedium;
      
   }
   else if (iWeight < FW_SEMIBOLD + 50)
   {

      dCoreTextWeight = kCTFontWeightSemibold;
      
   }
   else if (iWeight < FW_BOLD + 50)
   {
      
      dCoreTextWeight = kCTFontWeightBold;
      
   }
   else if (iWeight < FW_EXTRABOLD + 50)
   {

      dCoreTextWeight = kCTFontWeightHeavy;
      
   }
   else
   {

      dCoreTextWeight = kCTFontWeightBlack;
      
   }

   return dCoreTextWeight;

}



