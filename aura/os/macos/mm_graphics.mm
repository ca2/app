//
//  mm_graphics.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/05/20.
//
#include "_mm.h"

void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);
double font_similarity(const char * pszSystem, const char * pszUser);

extern NSCursor * g_pcurrentNscursor;


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

// int_bool window_set_mouse_cursor(oswindow window, HCURSOR hcursor)
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



