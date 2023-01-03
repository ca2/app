//
//  _apple.m
//  acme
//
//  Created by Camilo Sasuke on 2021-05-13 20:25 BRT <3ThomasBS_!!
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#import <Foundation/Foundation.h>
void ns_main_async(dispatch_block_t block);

char * ns_string(NSString * str);


bool ns_set_thread_name(const char * pszThreadName)
{

   NSString * strThreadName = [[NSString alloc] initWithUTF8String:pszThreadName];

   [[NSThread currentThread] setName : strThreadName];

   return true;

}




char * ns_get_thread_name()
{

   return ns_string([[NSThread currentThread] name]);

}






char * ns_string(NSString * str)
{

   if(str == nil)
   {

      return NULL;

   }

   const char * pszUtf8 = [str UTF8String];

   if(pszUtf8 == NULL)
   {

      return NULL;

   }

   return strdup(pszUtf8);


}



void ns_main_sync(dispatch_block_t block)
{

   if ([NSThread isMainThread])
   {

      block();

   }
   else
   {

      dispatch_sync(dispatch_get_main_queue(), block);

   }

}



void ns_main_async(dispatch_block_t block)
{

   //   dispatch_block_t block = ^{
   //      // Code for the method goes here
   //   };
   //

   if ([NSThread isMainThread])
   {

      block();

   }
   else
   {

      dispatch_async(dispatch_get_main_queue(), block);

   }

}


unsigned int m_sleep(unsigned int seconds)
{

   [NSThread sleepForTimeInterval:seconds];
   
   return 0;

}



char * ns_get_executable_path()
{
   
   return ns_string([[NSBundle mainBundle] executablePath]);
   
}
