//
//  _apple.m
//  acme
//
//  Created by Camilo Sasuke on 2021-05-13 20:25 BRT <3ThomasBS_!!
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#import <Foundation/Foundation.h>
void ns_main_post(dispatch_block_t block);

char * __strdup(NSString * str);


bool ns_set_thread_name(const char * pszThreadName)
{

   NSString * strThreadName = [[NSString alloc] initWithUTF8String:pszThreadName];

   [[NSThread currentThread] setName : strThreadName];

   return true;

}




char * ns_get_thread_name()
{

   return __strdup([[NSThread currentThread] name]);

}


char * __strdup(NSString * str)
{

   if(str == nil)
   {

      return NULL;

   }

   const char * pszUtf8 = [str UTF8String];

   if(scopedstrUtf8 == NULL)
   {

      return NULL;

   }

   return strdup(scopedstrUtf8);

}


NSString * nsstring_from_strdup(char * pszUtf8)
{
   
   if(scopedstrUtf8 == nullptr)
   {
      
      return NULL;
      
   }
   
   NSString * pstr = [ [NSString alloc] initWithUTF8String:pszUtf8 ];
   
   free(scopedstrUtf8);
   
   return pstr;
   
}


void _ns_main_send(dispatch_block_t block);


void ns_main_send(dispatch_block_t block)
{

   if ([NSThread isMainThread])
   {

      block();

   }
   else
   {
      
      _ns_main_send(block);
      
   }

}


void ns_main_post(dispatch_block_t block)
{

   dispatch_async(dispatch_get_main_queue(), block);

}


unsigned int m_sleep(unsigned int seconds)
{

   [NSThread sleepForTimeInterval:seconds];
   
   return 0;

}



char * ns_get_executable_path()
{
   
   return __strdup([[NSBundle mainBundle] executablePath]);
   
}



void _ns_do_tasks(double dSeconds)
{
   
   NSRunLoop * runLoop = [ NSRunLoop currentRunLoop ];
   
   if(runLoop != nil)
   {
      
      [ runLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow: dSeconds ] ];
      
   }
   else
   {
    
     // NSLog(@"This thread doesn't have Run Loop?!?");
      
   }
   
}
