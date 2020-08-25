//
//  mm_graphics.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/05/20.
//
#include "_mm.h"

void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);
double font_similarity(const char * pszSystem, const char * pszUser);


bool similar_font(char sz[256], const char * psz)
{
   
   auto fonts = [ [ NSFontManager sharedFontManager] availableFontFamilies ];
   
   if(!fonts)
   {
    
      return false;
      
   }
   
   double dMaxSimilarity = 0.2;
   
   int iFound = -1;
   
   for(int i = 0; i < [fonts count]; i++)
   {
    
      NSString * family = fonts[i];
      
      if(family)
      {
       
         double dSimilarity = font_similarity([family UTF8String], psz);
         
         if(dSimilarity > dMaxSimilarity)
         {
            
            iFound = i;
            
            dMaxSimilarity = dSimilarity;
         
         }
      
      }
      
   }
   
   if(iFound < 0)
   {
      
      return false;
      
   }
   
   NSString * family = fonts[iFound];
   
   strncpy(sz, [family UTF8String], 256);
   
   return true;

   
}


void default_font_name(char sz[256])
{
   
   strncpy(sz, "ArialMT", 256);
   
}



void * ns_image_get_image_data(int & width, int & height, int & iScan, NSImage * image)
{
   
   CGImageRef inputCGImage = [image CGImageForProposedRect:NULL context:NULL hints:NULL];
   
   return cg_image_get_image_data(width, height, iScan, inputCGImage);
}



