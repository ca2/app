//
//  NSPasteboard++.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 10/08/17.
//
//

#import <Foundation/Foundation.h>

#undef new


char * ns_string(NSString * str);

static NSPasteboard * g_ppasteboard = nullptr;

bool mm_clipboard_has_changed(long & lTicket)
{
   
   auto lClipboardChangeCount = [g_ppasteboard changeCount];
   
   if(lTicket != lClipboardChangeCount)
   {
      
      lTicket = lClipboardChangeCount;
      
      return true;
      
   }
   
   return false;

}


long mm_clipboard_init()
{
   
   if(g_ppasteboard == nullptr)
   {
      
      g_ppasteboard = [NSPasteboard generalPasteboard];
      
   }
   
   long lTicket = [g_ppasteboard changeCount];
   
   return lTicket;
   
}


long mm_clipboard_get_file_count()
{
   
   NSPasteboard * pasteboard = [NSPasteboard generalPasteboard];
   
   NSArray * classes = [NSArray arrayWithObject:[NSURL class]];
   
   NSDictionary *options = [NSDictionary dictionaryWithObject:
                            [NSNumber numberWithBool:YES] forKey:NSPasteboardURLReadingFileURLsOnlyKey];
   
   NSArray * filea = [pasteboard readObjectsForClasses:classes options:options];
   
   long iCount =  [filea count];

   return iCount;

}


char ** mm_clipboard_get_filea(long * pc)
{
   
   NSPasteboard * pasteboard = [NSPasteboard generalPasteboard];
   
   NSArray * classes = [NSArray arrayWithObject:[NSURL class]];
   
   NSDictionary *options = [NSDictionary dictionaryWithObject:
                            [NSNumber numberWithBool:YES] forKey:NSPasteboardURLReadingFileURLsOnlyKey];
   
   NSArray * filea = [pasteboard readObjectsForClasses:classes options:options];
   
   long c = [filea count];
   
   *pc = c;
   
   char ** psza = NULL;
   
   if(c > 0)
   {
      
      psza = (char **) malloc(c * sizeof(char *));
      
      for(int i = 0; i < c; i++)
      {
         
         NSURL * url = [filea objectAtIndex: i];
         
         NSString * str = [url path];
         
         psza[i] = strdup([str UTF8String]);
         
      }
      
   }
   
   return psza;
   
}


void mm_clipboard_set_filea(const char ** psza, long c)
{
   
   NSMutableArray * filea = [NSMutableArray new];
   
   for(int i = 0; i < c; i++)
   {
      
      const char * psz = psza[i];
      
      NSString * str = [NSString stringWithUTF8String: psz];
      
      str = [str stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
      
      if(psz[0] == '/')
      {
         
         str = [NSString stringWithFormat:@"file://%@", str];
         
      }
         

      
      NSURL * url = [NSURL URLWithString:str];
      
      [filea addObject : url];
      
   }
   
   NSPasteboard * pasteboard = [NSPasteboard generalPasteboard];
   
   [pasteboard declareTypes:[NSArray arrayWithObject:NSFilenamesPboardType] owner:nil];

   [pasteboard writeObjects: filea];
       
//
//   [pasteboard setPropertyList:filea forType:NSFilenamesPboardType];
   
}




// https://stackoverflow.com/questions/6167557/get-string-from-nspasteboard
char * mm_clipboard_get_plain_text()
{
   
   NSPasteboard * pasteboard = [NSPasteboard generalPasteboard];
   
   NSString * strPasteboard = [pasteboard stringForType:NSPasteboardTypeString];
   
   return ns_string(strPasteboard);
   
}


bool mm_clipboard_has_plain_text()
{
   
   NSPasteboard * pasteboard = [NSPasteboard generalPasteboard];
   
   NSString * strPasteboard = [pasteboard stringForType:NSPasteboardTypeString];
   
   return strPasteboard != nil;
   
}


//https://stackoverflow.com/questions/3655038/how-to-copy-textfield-to-osx-clipboard
//On OSX

void mm_clipboard_set_plain_text(const char * psz)
{
   
   NSPasteboard * pasteboard = [NSPasteboard generalPasteboard];
   
   NSString * strPasteboard = [NSString stringWithUTF8String: psz];

   [pasteboard clearContents];
   
   [pasteboard setString:strPasteboard forType:NSStringPboardType];

}


void * ns_image_get_image_data(int & width, int & height, int & iScan, NSImage * pimage);

bool mm_clipboard_has_image()
{
   
   NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
   
   NSArray *classArray = [NSArray arrayWithObject:[NSImage class]];
   
   NSDictionary *options = [NSDictionary dictionary];
   
   BOOL ok = [pasteboard canReadObjectForClasses:classArray options:options];
   
   return ok != FALSE;
   
}


// http://findnerd.com/list/view/How-to-copy-image-in-NSPasteBoard/756/
void * mm_clipboard_get_image(int & cx, int & cy, int & iScan)
{

   NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];

   NSArray *classArray = [NSArray arrayWithObject:[NSImage class]];

   NSDictionary *options = [NSDictionary dictionary];

   BOOL ok = [pasteboard canReadObjectForClasses:classArray options:options];

   if (!ok)
   {
   
      return NULL;
   
   }
   
   NSArray *objectsToPaste = [pasteboard readObjectsForClasses:classArray options:options];
   
   NSImage *image = [objectsToPaste objectAtIndex:0];
   
   void * pdata = ns_image_get_image_data(cx, cy, iScan, image);
   
   if(pdata == NULL)
   {
      
      return NULL;
      
   }

   return pdata;
   
}
