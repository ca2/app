//
//  ios_mm.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 8/3/15.
//
//
#import "_mm.h"


bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);;

int _get_exe_path_len()
{
   
   return (int) strlen([[[NSBundle mainBundle] executablePath] UTF8String]);
   
}

void _get_exe_path(char * pszPath, int size)
{
   
   strncpy(pszPath, [[[NSBundle mainBundle] executablePath] UTF8String], size);
   
}



bool mm2_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   NSString * str = [NSString stringWithUTF8String:psz];
   
   if(str == NULL)
   {
      
      return false;
      
   }
   
   NSURL *URL = [NSURL fileURLWithPath: str];
   
   UIDocumentInteractionController *documentInteractionController =[UIDocumentInteractionController interactionControllerWithURL:URL];
   
   int iFind = 0;
   
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





bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   return mm2_get_file_image(pcr, cx, cy, iScan, psz);
}


char * ns_get_executable_path()
{
   
   return ns_string([[NSBundle mainBundle] executablePath]);
   
}


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
   
   strncpy(psz, [pstr UTF8String], *puiSize);
   
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
   
   return ns_open_url(psz);
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
