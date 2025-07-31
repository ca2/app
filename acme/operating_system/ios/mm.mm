//
//  ios_mm.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 8/3/15.
//
//
#import "_mm.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

void ns_main_post(dispatch_block_t block);



int _get_exe_path_len()
{
   
   return (int) strlen([[[NSBundle mainBundle] executablePath] UTF8String]);
   
}

void _get_exe_path(char * pszPath, int size)
{
   
   strncpy(scopedstrPath, [[[NSBundle mainBundle] executablePath] UTF8String], size);
   
}







//bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
//{
//   
//   return mm2_get_file_image(pcr, cx, cy, iScan, psz);
//}




NSString * applicationDocumentsDirectory()
{
   return [[[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject] path];
}


bool _ui_library_dir(char * psz, unsigned int * puiSize)
{

   NSString * pstr = [NSHomeDirectory() stringByAppendingString:@"/Library"];
   
   if(pstr == NULL)
   {
      
      return false;
      
   }
   
   *puiSize = (unsigned int) strlen([pstr UTF8String]);
   
   strncpy(scopedstr, [pstr UTF8String], *puiSize);
   
   return true;
   
}




//
//bool ns_open_file(const char * psz)
//{
//
//   NSString * path = [NSString stringWithUTF8String:psz];
//
//   if(path == NULL)
//   {
//
//      return false;
//
//   }
//
//   NSURL * url = [NSURL fileURLWithPath: path];
//
//   //https://stackoverflow.com/questions/20869815/open-file-from-local-file-system-with-default-application-ios
//
//   BOOL canOpenResource = [ [UIApplication sharedApplication] canOpenURL: url];
//
//   if (!canOpenResource)
//   {
//
//      return false;
//
//   }
//
//   if([[UIApplication sharedApplication] openURL: url])
//   {
//
//      return true;
//
//   }
//
//
//   RoundWindowApp * papp = (RoundWindowApp *)[ [UIApplication sharedApplication] delegate];
//
//   UIDocumentInteractionController *documentController = [UIDocumentInteractionController interactionControllerWithURL: url];
//   documentController.delegate = papp;
//   if([documentController presentOpenInMenuFromRect:CGRectZero inView: [papp view] animated:YES])
//   {
//
//      return false;
//
//   }
//   //https://www.infragistics.com/community/blogs/b/stevez/posts/ios-tips-and-tricks-associate-a-file-type-with-your-app-part-3
////
////   NSFileManager *filemgr = [NSFileManager defaultManager];
////   NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
////   NSString *documentsDirectory = [paths objectAtIndex:0];
////   NSString* inboxPath = [documentsDirectory stringByAppendingPathComponent:@"Inbox"];
////   NSArray *dirFiles = [filemgr contentsOfDirectoryAtPath:inboxPath error:nil];
//
//
//
//   //(However,) if your wish to present the user with a list of apps that have registered with the appropriate UTI for that file type you can do something like this-
//   //UIDocumentInteractionController *documentController = [UIDocumentInteractionController interactionControllerWithURL:[NSURL fileURLWithPath:filePath]];
//   //documentController.delegate = self;
//   //[documentController presentOpenInMenuFromRect:CGRectZero inView:self.view animated:YES];
//
//   return true;
//
//}




bool ns_open_url(const char * psz)
{
   
   NSString * str = [NSString stringWithUTF8String:psz];
   
   if(str == NULL)
   {
      
      return false;
      
   }
   
   NSURL * url = [[NSURL alloc] initWithString: str];
   
   if(url == NULL)
   {
      
      return false;
      
   }
   
   [[UIApplication sharedApplication] openURL: url options: @{} completionHandler: ^(BOOL i)
    {
      
      
   }];
//   {
//
//      return false;
//
//   }
   
   return true;
   
}



bool ns_open_file(const char * psz)
{
   
   return ns_open_url(scopedstr);
//   NSString * path = [NSString stringWithUTF8String:psz];
//   
//   if(path == NULL)
//   {
//      
//      return false;
//      
//   }
//   
//   if(![[NSWorkspace sharedWorkspace] openFile: path])
//   {
//      
//      return false;
//      
//   }
//   
//   return true;
   
}


CLASS_DECL_ACME void operating_system_get_main_screen_size(int & cx, int & cy)
{
   
   auto bounds = [[UIScreen mainScreen] bounds];
   
   cx = bounds.size.width;
   
   cy = bounds.size.height;
   
}



void ui_open_url(const char  *pszUrl)
{
   
   NSString * strUrl = [ [ NSString alloc ] initWithUTF8String:pszUrl];
   
   NSURL * url = [ NSURL URLWithString: strUrl ];

   ns_main_post(^()
                 {
      
      [ [ UIApplication sharedApplication ] openURL: url options:@{} completionHandler:nil];
      
   });

}




