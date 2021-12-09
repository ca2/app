//
//  macos_file.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 03/05/18.
//
#import "_mm.h"

//void ns_create_alias(const char * pszTarget, const char * pszSource)
//{
//   NSString * strTarget = [[NSString alloc]initWithUTF8String:pszTarget];
//   NSString * strSource = [[NSString alloc]initWithUTF8String:pszSource];
//   
//   [[NSFileManager defaultManager ] createSymbolicLinkAtPath: strTarget withDestinationPath: strSource error:nil];
//}
//

char * ns_user_local_folder(NSSearchPathDirectory e)
{
   
   NSArray < NSURL * > * pa = [[NSFileManager defaultManager ] URLsForDirectory:e inDomains:NSLocalDomainMask| NSUserDomainMask];
   
   if(pa == NULL || [pa count] <= 0)
   {
      
      return NULL;
      
   }
   
   return ns_string([[pa objectAtIndex:0] path]);
   
}



char * ns_user_local_desktop_folder()
{
   
   return ns_user_local_folder(NSDesktopDirectory);
   
}


char * ns_user_local_documents_folder()
{
   
   return ns_user_local_folder(NSDocumentDirectory);
   
}

char * ns_user_local_downloads_folder()
{
   
   return ns_user_local_folder(NSDownloadsDirectory);
   
}


char * ns_user_local_music_folder()
{
   
   return ns_user_local_folder(NSMusicDirectory);
   
}


char * ns_user_local_image_folder()
{
   
   return ns_user_local_folder(NSPicturesDirectory);
   
}

char * ns_user_local_video_folder()
{
   
   return ns_user_local_folder(NSMoviesDirectory);
   
}



