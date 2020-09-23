//
//  visual_apple_image_mm.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 25/10/17.
//

#import <Foundation/Foundation.h>

void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);

CFDataRef CopyImagePixels(CGImageRef inImage)
{
   
   return CGDataProviderCopyData(CGImageGetDataProvider(inImage));
   
}


void * ns_image_get_image_data(int & width, int & height, int & iScan, NSImage * pimage);


void * file_memory_to_image_data(int & width, int & height, int & iScan, const void * pdata, unsigned long size)
{
   
   NSData * data = [NSData dataWithBytes:pdata length:size];
   
   if(data == nil)
   {
      
      return NULL;
      
   }
   
   NSImage * image = [[NSImage alloc] initWithData: data];
   
   return ns_image_get_image_data(width, height, iScan, image);
   
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
   
   memcpy(p, [data bytes], [data length]);
   
   size = [data length];
   
   return p;
   
}


void * get_png_image_data(unsigned long & size, CGImageRef image)
{
   
   NSBitmapImageRep *imgRep = [[NSBitmapImageRep alloc] initWithCGImage:image];

   NSDictionary *imageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];

   NSData *data = [imgRep representationUsingType: NSPNGFileType properties: imageProps];
   
   return return_data(size, data);

}


void * get_jpeg_image_data(unsigned long & size, CGImageRef cgimage)
{
   
   NSImage * image = [[NSImage alloc] initWithCGImage:cgimage size: NSZeroSize];
   
   NSData *imageData = [image TIFFRepresentation];
   
   NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithData:imageData];
   
   NSDictionary *imageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];
   
   imageData = [imageRep representationUsingType:NSJPEGFileType properties:imageProps];;
   
   return return_data(size, imageData);
   
}


NSImage * nsimage_from_cgimageref(CGImageRef image, int cx, int cy)
{
   
   NSSize sz;
   
   sz.width = cx;
   
   sz.height = cy;
   
   return [[NSImage alloc] initWithCGImage:image size:sz];
   
}

extern NSCursor * g_pcurrentNscursor;

void ns_set_cursor_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot)
{
   
   if(g_pcurrentNscursor != nullptr)
   {
      
      [g_pcurrentNscursor pop];
      
   }
   
   if(image == nullptr)
   {
      
      return;
      
   }

   NSPoint point;

   point.x = xHotSpot;

   point.y = yHotSpot;

   NSImage * pimage = nsimage_from_cgimageref(image, cx, cy);

   g_pcurrentNscursor = [[NSCursor alloc] initWithImage: pimage hotSpot:point];

   [g_pcurrentNscursor push];
   
   
}


void * nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot)
{
   
   if(image == nullptr)
   {
      
      return NULL;
      
   }
   
   NSPoint point;
   
   point.x = xHotSpot;
   
   point.y = yHotSpot;
   
   NSImage * pimage = nsimage_from_cgimageref(image, cx, cy);
   
   NSCursor * pcursor = [[NSCursor alloc] initWithImage: pimage hotSpot:point];

   return (__bridge_retained void *) pcursor;
   
}


void * nscursor_system(e_cursor ecursor)
{
   
   NSCursor * pcursor;
   
   if(ecursor == cursor_arrow)
   {
      
      pcursor = [NSCursor arrowCursor];
      
   }
   else if(ecursor == cursor_hand)
   {
      
      pcursor = [NSCursor openHandCursor];
      
   }
   else if(ecursor == cursor_text_select)
   {
      
      pcursor = [NSCursor IBeamCursor];
      
   }
   else if(ecursor == cursor_size_bottom)
   {
      
      pcursor = [NSCursor resizeUpDownCursor];
      
   }
   else if(ecursor == cursor_size_top)
   {
      
      pcursor = [NSCursor resizeUpDownCursor];
      
   }
   else if(ecursor == cursor_size_left)
   {
      
      pcursor = [NSCursor resizeLeftRightCursor];
      
   }
   else if(ecursor == cursor_size_right)
   {
      
      pcursor = [NSCursor resizeLeftRightCursor];
      
   }
   else if(ecursor == cursor_size_bottom_left)
   {
      
      pcursor = [NSCursor openHandCursor];
      
   }
   else if(ecursor == cursor_size_bottom_right)
   {
      
      pcursor = [NSCursor openHandCursor];
      
   }
   else if(ecursor == cursor_size_top_left)
   {
      
      pcursor = [NSCursor openHandCursor];
      
   }
   else if(ecursor == cursor_size_top_right)
   {
      
      pcursor = [NSCursor openHandCursor];
      
   }
   else
   {

      pcursor = [NSCursor arrowCursor];

   }
   
   return (__bridge_retained void *) pcursor;
   
}

// WINBOOL window_set_mouse_cursor(oswindow window, HCURSOR hcursor)
int os_window_set_mouse_cursor(void *, void * p)
{

   NSCursor * pcursor = (__bridge NSCursor *) p;
   
   if(g_pcurrentNscursor != nullptr)
   {
      
      if(p == NULL)
      {
         
         [NSCursor hide];
         
      }
      
   }
   else
   {

      if(p != NULL)
      {
         
         [NSCursor unhide];
         
      }

   }

   g_pcurrentNscursor = pcursor;
   
   if(g_pcurrentNscursor != NULL)
   {
      
      if(g_pcurrentNscursor != [NSCursor currentCursor])
      {
   
         [g_pcurrentNscursor set];
         
      }
      
   }

   return 1;
   
}
