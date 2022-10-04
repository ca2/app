//
//  _apple_no_templates.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

#pragma once


//#include "acme/operating_system/cross/windows/windows_defs.h"

void copy(CGRect * prectTarget, const RECTANGLE_I32 * prectSource);
void copy(RECTANGLE_I32 * prectTarget, const CGRect * prectSource);
void copy(CGRect * prectTarget, const RECTANGLE_F64 * prectSource);
void copy(RECTANGLE_F64 * prectTarget, const CGRect * prectSource);
void window_copy(CGRect * prectTarget, const RECTANGLE_I32 * prectSource);
void window_copy(RECTANGLE_I32 * prectTarget, const CGRect * prectSource);


void copy(CGPoint * ppointTarget, const POINT_I32 * ppointSource);
void copy(POINT_I32 * ppointTarget, const CGPoint * ppointSource);
void copy(CGPoint * ppointTarget, const POINT_F64 * ppointSource);
void copy(POINT_F64 * ppointTarget, const CGPoint * ppointSource);



void ns_main_async(dispatch_block_t block);


void ns_main_sync(dispatch_block_t block);

time_t _mkgmtime(struct tm * const);



