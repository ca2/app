//
//  shell.m
//  aura_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 22/08/21.
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UniformTypeIdentifiers/UTType.h>


bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool apple_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * pszFilePath)
{
   
   NSString * strFilePath = [NSString stringWithUTF8String:pszFilePath];
   
   if(strFilePath == NULL)
   {
      
      return false;
      
   }
   
   NSImage * image = [[NSWorkspace sharedWorkspace] iconForFile:strFilePath];
   
   if(image == NULL)
   {
      
      return false;
      
   }
   
   NSRect r;
   
   r.origin.x = 0;
   r.origin.y = 0;
   r.size.width = cx;
   r.size.height = cy;
   
   CGImageRef i = [image CGImageForProposedRect: &r context:nil hints:nil];
   
   bool bOk = GetImagePixelData(pcr, cx, cy, iScan,  i);
   
   return bOk;
   
}


bool mm2_get_file_image_by_type_identifier(unsigned int * pcr, int cx, int cy, int iScan, const char * pszTypeIdentifier)
{
   
   NSString * strTypeIdentifier = [NSString stringWithUTF8String:pszTypeIdentifier];
   
   if(strTypeIdentifier == NULL)
   {
      
      return false;
      
   }
   
   NSImage * image = nullptr;
   
   if(@available(macOS 11.0, *))
   {
      
      UTType * ptype = [ UTType typeWithIdentifier: strTypeIdentifier ];

      if(ptype == NULL)
      {

         return false;

      }

      image = [[ NSWorkspace sharedWorkspace ] iconForContentType: ptype];
   
      if(image == NULL)
      {

         return false;

      }
      
   }
   else
   {
   
      image = [[NSWorkspace sharedWorkspace] iconForFileType: strTypeIdentifier];
      
   }
   
   if(image == NULL)
   {
      
      return false;
      
   }

   NSRect r;
   
   r.origin.x = 0;
   r.origin.y = 0;
   r.size.width = cx;
   r.size.height = cy;
   
   CGImageRef i = [image CGImageForProposedRect: &r context:nil hints:nil];
   
   bool bOk = GetImagePixelData(pcr, cx, cy, iScan,  i);
   
   return bOk;
   
}


bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   return mm2_get_file_image(pcr, cx, cy, iScan, psz);
   
}


bool mm1_get_file_image_by_type_identifier(unsigned int * pcr, int cx, int cy, int iScan, const char * pszTypeIdentifier)
{
   
   return mm2_get_file_image_by_type_identifier(pcr, cx, cy, iScan, pszTypeIdentifier);
   
}



