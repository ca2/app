//
//  mm.mm
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//

#import <Foundation/Foundation.h>


void _openURL(const char * psz);


void _openURL(const char * psz)
{
   CFURLRef url = CFURLCreateWithBytes(
                  nullptr,                        // allocator
                  (const ::u8*)psz,     // URLBytes
                  strlen(psz),            // length
                  kCFStringEncodingASCII,      // encoding
                  nullptr                         // baseURL
                  );
   LSOpenCFURLRef(url,0);
   CFRelease(url);
}

