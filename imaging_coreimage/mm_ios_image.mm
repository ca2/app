//
//  mm_ios_image.m
//  coreimage_imaging
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//

#import <Foundation/Foundation.h>
//
//  visual_apple_image_mm.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 25/10/17.
//


void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);

CFDataRef CopyImagePixels(CGImageRef inImage) {     return CGDataProviderCopyData(CGImageGetDataProvider(inImage)); }

void * ui_image_get_image_data(int & width, int & height, int & iScan, UIImage * pimage);

void * get_image_data(int & width, int & height, int & iScan, const void * pdata, unsigned long size)
{
   
   NSData * data = [NSData dataWithBytes:pdata length:size];
   
   if(data == nil)
   {
      
      return NULL;
      
   }
   
   UIImage * image = [[UIImage alloc] initWithData: data];
   
   return ui_image_get_image_data(width, height, iScan, image);
   
}


void * file_memory_to_image_data(int & width, int & height, int & iScan, const void * pdata, unsigned long size)
{
   
   NSData * data = [NSData dataWithBytes:pdata length:size];
   
   if(data == nil)
   {
      
      return NULL;
      
   }
   
   UIImage * image = [[UIImage alloc] initWithData: data];
   
   return ui_image_get_image_data(width, height, iScan, image);
   
}


void * ui_image_get_image_data(int & width, int & height, int & iScan, UIImage * image)
{
   
   CGImageRef inputCGImage = [image CGImage];
   
   return cg_image_get_image_data(width, height, iScan, inputCGImage);
   
}


void * return_data(unsigned long & size, NSData * data)
{
   
   if(data == NULL)
   {
      
      return NULL;
      
   }
   
   if([data length] <= 0 || [data bytes] == NULL)
   {
      
      return NULL;
      
   }
   
   void * p = malloc([data length]);
   
   if(p == NULL)
   {
      
      return NULL;
      
   }
   
   ::memcpy(p, [data bytes], [data length]);
   
   size = [data length];
   
   return p;
   
}


void * get_png_image_data(unsigned long & size, CGImageRef image)
{
   
   UIImage *img = [[UIImage alloc] initWithCGImage:image];
   
   NSData* data = UIImagePNGRepresentation (img);
   
   return return_data(size, data);

}


void * get_jpeg_image_data(unsigned long & size, CGImageRef cgimage)
{
   
   UIImage *img = [[UIImage alloc] initWithCGImage:cgimage];
   
   NSData* data = UIImageJPEGRepresentation (img, 0.89);
   
   return return_data(size, data);
   
}


int os_window_set_mouse_cursor(void *, void * p)
{
   
   return 0;

}



