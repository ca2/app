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



void * nscursor_system(enum_cursor ecursor)
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
