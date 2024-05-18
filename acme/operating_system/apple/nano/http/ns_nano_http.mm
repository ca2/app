//
//  mm.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:28

//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
//#include "framework.h"
#include "_http.h"
#include "ns_nano_http.h"
#include <Foundation/Foundation.h>
#ifdef MACOS
#import <Cocoa/Cocoa.h>
#elif defined(_APPLE_IOS_)
#import <UIKit/UIKit.h>
#endif
void nano_http_get_transfer_progress(void * userdata, long done, long total);
void nano_http_get_set_out_header(void * userdata, const char * pszKey, const char * pszPayload);
bool nano_http_get_only_headers(void * userdata);

@implementation ns_nano_http


- (void)async :(const char *) pszUrl withResponseCallback:(PFN_NANO_HTTP_RESPONSE) pfnResponseCallback andUserData:(void*)userdata
{
   
   m_lHttpResponseStatus = 0;
   m_pfn = pfnResponseCallback;
   m_userdata = userdata;
 
   NSString * strUrl = [[NSString alloc] initWithUTF8String: pszUrl];
   
   NSURL * url =[NSURL URLWithString:strUrl];
   
    NSURLSessionConfiguration *defaultConfigObject = [NSURLSessionConfiguration defaultSessionConfiguration];

    NSURLSession *defaultSession = [NSURLSession sessionWithConfiguration: defaultConfigObject delegate: self delegateQueue: [NSOperationQueue mainQueue]];

   NSURLSessionDataTask *dataTask = [defaultSession dataTaskWithURL: url ];

//completionHandler:
//                                      ^(NSData *data, NSURLResponse *response, NSError *error)
//                               {
//       pfnResponseCallback(((NSHTTPURLResponse *)response).statusCode, [data bytes], [data length], userdata);
//                               //            NSString *contentOfURL = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
//                               //            NSLog(@"%@", contentOfURL);
//                                     //passynchronoushttpdata->m_event.setEvent();
//                                     
//                                }];

    [dataTask resume];
}

- (void)didReceiveMemoryWarning {
    //[super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask onHeaders:(NSURLResponse *)response
{
   //progressBar.progress=0.0f;
   _downloadSize=[response expectedContentLength];
  NSHTTPURLResponse * phttpurlresponse =  (NSHTTPURLResponse *)response;
  m_lHttpResponseStatus = [phttpurlresponse statusCode];
  
  auto dict = [phttpurlresponse allHeaderFields];
  // To print out all key-value pairs in the NSDictionary myDict
  for(id key in dict)
  {
     NSString * strKey = key;
     NSString * strPayload = [dict objectForKey:key];
     nano_http_get_set_out_header(
                                  self->m_userdata,
                                  [strKey UTF8String], [strPayload UTF8String]);
  }

   return !nano_http_get_only_headers(self->m_userdata);
   
}

- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask didReceiveResponse:(NSURLResponse *)response completionHandler:(void (^)(NSURLSessionResponseDisposition disposition))completionHandler
{
   

   if(![self URLSession :session dataTask : dataTask onHeaders: response])
   {
      //[dataTask suspend];
      //[dataTask cancel];
      completionHandler(NSURLSessionResponseCancel);

      return;
   }
   _dataToDownload=[[NSMutableData alloc]init];
   nano_http_get_transfer_progress(self->m_userdata, 0, _downloadSize);
   completionHandler(NSURLSessionResponseAllow);


}

- (void)URLSession:(NSURLSession *)session
              task:(NSURLSessionTask *)dataTask
willPerformHTTPRedirection:(NSHTTPURLResponse *)response
        newRequest:(NSURLRequest *)request
 completionHandler:(void (^)(NSURLRequest *))completionHandler
{
   
   //[self URLSession :session dataTask : dataTask onHeaders: response];
   
   completionHandler(nil);

}

- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask didReceiveData:(NSData *)data {
    [_dataToDownload appendData:data];
   nano_http_get_transfer_progress(self->m_userdata, [_dataToDownload length], _downloadSize);
}

/* Sent as the last message related to a specific task.  Error may be
 * nil, which implies that no error occurred and this task is complete.
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                           didCompleteWithError:(nullable NSError *)error;
{
   
   if(m_pfn)
   {
    
      m_pfn(m_lHttpResponseStatus, [_dataToDownload bytes],
            [_dataToDownload length], m_userdata);
      
   }
   
}

@end


void nano_asynchronous_http_get(const char * pszUrl, PFN_NANO_HTTP_RESPONSE pfn, void * userdata)
{
   
   ns_nano_http * phttp = [[ns_nano_http alloc] init];
   
   [phttp async:pszUrl withResponseCallback:pfn andUserData:userdata];
   
//   NSURL * url =[NSURL URLWithString:strUrl];
//   
//   NSURLSession *aSession = [NSURLSession sessionWithConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
   
//   NSURLSessionDataTask * pdatatask = [aSession dataTaskWithURL:url completionHandler:
//       ^(NSData *data, NSURLResponse *response, NSError *error)
//{
//            pfn(((NSHTTPURLResponse *)response).statusCode, [data bytes], [data length], userdata);
////            NSString *contentOfURL = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
////            NSLog(@"%@", contentOfURL);
//      //passynchronoushttpdata->m_event.setEvent();
//      
// }];
//   
//   [pdatatask resume];
//   
   
}
