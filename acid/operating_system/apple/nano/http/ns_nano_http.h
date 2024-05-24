//
//  FROM av_speech_synthesis.h
//  ace_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-12 22:11 <3ThomasBorregaardSorensen!!
//

//  Model.h

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface ns_nano_http : NSObject<NSURLSessionDataDelegate, NSURLSessionDelegate, NSURLSessionTaskDelegate>
{
 
   long m_lHttpResponseStatus;
   PFN_NANO_HTTP_RESPONSE m_pfn;
   void * m_userdata;
   
}

@property (nonatomic, retain) NSMutableData *dataToDownload;
@property (nonatomic) float downloadSize;

- (void)async :(const char *)psz withResponseCallback:(PFN_NANO_HTTP_RESPONSE) pfnResponseCallback andUserData:(void*)userData;



@end

