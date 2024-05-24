//
//  _cg_context.cpp
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-01.
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"

#include <CoreGraphics/CoreGraphics.h>
#include <CoreImage/CoreImage.h>


CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy)
{

   CGContextRef    context = nullptr;

   CGColorSpaceRef colorSpace;

   //void *          bitmapData;

   int             bitmapByteCount;

   int             bitmapBytesPerRow;

   bitmapBytesPerRow   = (cx * 4);

   bitmapByteCount     = (bitmapBytesPerRow * cy);

   colorSpace = CGColorSpaceCreateDeviceRGB();

   if (colorSpace == nullptr)
   {

      output_debug_string("CreateARGBBitmapContext: Error allocating color space\n");

      return nullptr;

   }

   //   bitmapData = malloc( bitmapByteCount );
   //
   //   if (bitmapData == nullptr)
   //   {
   //
   //      output_debug_string("CreateARGBBitmapContext: Memory not allocated!");
   //
   //      CGColorSpaceRelease( colorSpace );
   //
   //      return nullptr;
   //
   //   }
   //
   //   __memset(bitmapData, 0, bitmapByteCount);

   // Create the bitmap context. We want pre-multiplied argb, 8-bits
   // per component. Regardless of what the source image format is
   // (CMYK, Grayscale, and so on) it will be converted over to the format
   // specified here by CGBitmapContextCreate.
   context =
   CGBitmapContextCreate (
   nullptr,
   cx,
   cy,
   8,
   bitmapBytesPerRow,
   colorSpace,
   kCGImageAlphaPremultipliedLast);

   //   if (context == nullptr)
   //   {
   //
   //      free (bitmapData);
   //
   //      output_debug_string("CreateARGBBitmapContext: Context not created!");
   //
   //   }

   CGColorSpaceRelease( colorSpace );

   return context;
}


bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage)
{

   CGContextRef cgctx = CreateARGBBitmapContext(inImage, cx, cy);

   if (cgctx == nullptr)
   {

      return false;

   }

   CGRect rectangle = {{0,0},{(CGFloat)cx,(CGFloat)cy}};

   CGContextDrawImage(cgctx, rectangle, inImage);

   void *data = CGBitmapContextGetData (cgctx);

   u8 * pdest = (u8 * ) pcr;

   if (data != nullptr)
   {

      for(int y = cy - 1; y >= 0; y--)
      {

         u8 * pline = (u8 *) &((unsigned int*)data)[y * cx];

         ::memory_copy(pdest, pline, cx* 4);

         pdest += iScan;

      }

   }

   CGContextRelease(cgctx);

   return data != nullptr;

}

