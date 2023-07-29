//
//  mm.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:28

//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
//#include "framework.h"
#include "_nano_http.h"
#include <Foundation/Foundation.h>


void nano_asynchronous_http_memory(const char * pszUrl, PFN_HTTP_RESPONSE pfn)
{
   
   NSString * strUrl = [[NSString alloc] init
                        WithCString: pszUrl];
   
   NSURL * url =[NSURL URLWithString:strUrl];
   
   NSURLSession *aSession = [NSURLSession sessionWithConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
   
   NSURLSessionDataTask * pdatatask = [aSession dataTaskWithURL:url completionHandler:
       ^(NSData *data, NSURLResponse *response, NSError *error)
{
            pfn(((NSHTTPURLResponse *)response).statusCode, [data bytes], [data length]);
//            NSString *contentOfURL = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
//            NSLog(@"%@", contentOfURL);
   }];
   
   [pdatatask resume];
   
   
}
