//
//  apple.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//
#pragma once

// C and Objective-C include

#ifdef __OBJC__
#include "NSObject+DDExtensions.h"
#include "DDInvocationGrabber.h"

char * ns_string(NSString * str);

#endif

CGRect mm_get_workspace_rect();


void copy(CGRect * prectTarget, const RECT * prectSource);
void copy(RECT * prectTarget, const CGRect * prectSource);
void copy(CGRect * prectTarget, const RECTD * prectSource);
void copy(RECTD * prectTarget, const CGRect * prectSource);
void window_copy(CGRect * prectTarget, const RECT * prectSource);
void window_copy(RECT * prectTarget, const CGRect * prectSource);

#ifdef MM

void copy(NSRect & rect, LPCRECT lpcrect);
void copy(LPRECT lprect, const NSRect & rectSrc);
void window_copy(NSRect & rect, LPCRECT lpcrect);
void window_copy(LPRECT lprect, const NSRect & rectSrc);

#endif


#include "graphics.h"
#include "ns_exception.h"
#include "time.h"

void ns_launch_app(const char * psz, const char ** argv, int iFlags);
bool ns_open_file(const char * psz);
void ns_main_async(dispatch_block_t block);

void apple_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_on_new_file();


void acme_application_main(int argc, char *argv[], const char * pszCommandLine);



int is_window(oswindow window);

void ns_main_sync(dispatch_block_t block, unsigned int uiMillis = -1);
void ns_main_async(dispatch_block_t block);

