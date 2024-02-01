//
//  file_image.m
//  static_acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-01.
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <UniformTypeIdentifiers/UTType.h>


bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool apple_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   NSString * str = [NSString stringWithUTF8String:psz];
   
   if(str == NULL)
   {
      
      return false;
      
   }
   
   NSURL *URL = [NSURL fileURLWithPath: str];
   
   UIDocumentInteractionController *documentInteractionController =[UIDocumentInteractionController interactionControllerWithURL:URL];
   
   auto iFind = 0;
   
   for(; iFind < [[documentInteractionController icons] count]; iFind++)
   {
      
      UIImage *image = [[documentInteractionController icons] objectAtIndex:iFind];
      
      if([image size].width > cx && [image size].height > cy)
      {
         
         if(iFind > 0)
         {
            
            iFind--;
            
         }
         
         break;
         
      }
      
   }
   
   if(iFind >= [[documentInteractionController icons] count])
   {
      
      return false;
      
   }
   
   UIImage *image = [[documentInteractionController icons] objectAtIndex:iFind];
   
   if(image == NULL)
   {
      
      return false;
      
   }
   
   CGImageRef i = [image CGImage];
   
   bool bOk = GetImagePixelData(pcr, cx, cy, iScan,  i);
   
   //CFRelease(i);
   
   return bOk;
   
   
   
}




bool apple_get_file_image_by_type_identifier(unsigned int * pcr, int cx, int cy, int iScan, const char * pszTypeIdentifier)
{

   NSString * strTypeIdentifier = [NSString stringWithUTF8String:pszTypeIdentifier];

   if(strTypeIdentifier == NULL)
   {

      return false;

   }

   
   //Need to initialize this way or the doc controller doesn't work
   NSURL*fooUrl = [NSURL URLWithString:@"file://foot.dat"];
   UIDocumentInteractionController* docController = [UIDocumentInteractionController interactionControllerWithURL:fooUrl];

   UIImage* image = nil;
//   //Need to convert from mime type to a UTI to be able to get icons for the document
//   NSString *uti = [NSMakeCollectable(UTTypeCreatePreferredIdentifierForTag(kUTTagClassMIMEType, (CFStringRef)self.contentType, NULL)) autorelease];

   //Tell the doc controller what UTI type we want
   docController.UTI = strTypeIdentifier;

   //The doc controller now seems to have icon(s) for the type I ask for...
   NSArray* icons = docController.icons;
   if([icons count] > 0) {
      
      UIImage * imageLargest = nil;
      for(int i = 0; i < [icons count]; i++)
      {
         UIImage * icon = [icons objectAtIndex:i];
         if(!imageLargest)
         {
            
            imageLargest = icon;
            
         }
         else if([icon size].width * [icon size].height > [imageLargest size].width * [imageLargest size].height)
         {
            
            imageLargest = icon;
            
         }

         if([icon size].width == cx
            && [icon size].height == cy)
         {
            
            image = icon;
            
            break;
            
         }
         
      }
       
      if(!image)
      {
       
         image = imageLargest;
         
      }
      
   }
   //return thumbnail;
//   UIImage * image = nullptr;
//
//
//   NSString *extension = @"pptx"; // or something else
//   NSString *dummyPath = [@"~/foo" stringByAppendingPathExtension:extension]; // doesn't exist
//   NSURL *URL = [NSURL fileURLWithPath:dummyPath];
//   UIDocumentInteractionController *documentInteractionController = [UIDocumentInteractionController interactionControllerWithURL:URL];
//   NSArray *systemIconImages = documentInteractionController.icons;
//
//   return systemIconImages;
//   if(@available(macOS 11.0, *))
//   {
//
//      UTType * ptype = [ UTType typeWithIdentifier: strTypeIdentifier ];
//
//      if(ptype == NULL)
//      {
//
//         return false;
//
//      }
//
//      image = [[ UIWorkspace sharedWorkspace ] iconForContentType: ptype];
//
//      if(image == NULL)
//      {
//
//         return false;
//
//      }
//
//   }
//   else
//   {
//
//      image = [[NSWorkspace sharedWorkspace] iconForFileType: strTypeIdentifier];
//
//   }
//
//   if(image == NULL)
//   {
//
//      return false;
//
//   }
//
//   NSRect r;
//
//   r.origin.x = 0;
//   r.origin.y = 0;
//   r.size.width = cx;
//   r.size.height = cy;
//
   CGImageRef i = [image CGImage];

   bool bOk = GetImagePixelData(pcr, cx, cy, iScan,  i);

   return bOk;
//
//   //return false;

}
