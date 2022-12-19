//
//  _apple_no_templates.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

#pragma once


#include <CoreGraphics/CoreGraphics.h>


void throw_ns_exception(enum_status estatus, const scoped_string & strName, const scoped_string & strDescription, const ::property_set & propertyset);


void copy(CGRect & rectTarget, const RECTANGLE_I32 & rectSource);
void copy(RECTANGLE_I32 & rectTarget, const CGRect & rectSource);
void copy(CGRect & rectTarget, const RECTANGLE_F64 & rectSource);
void copy(RECTANGLE_F64 & rectTarget, const CGRect & rectSource);
void screen_coordinates_aware_copy(CGRect & rectTarget, const RECTANGLE_I32 & rectSource);
void screen_coordinates_aware_copy(RECTANGLE_I32 & rectTarget, const CGRect & rectSource);


void copy(CGPoint & pointTarget, const POINT_I32 & pointSource);
void copy(POINT_I32 & pointTarget, const CGPoint & pointSource);
void copy(CGPoint & pointTarget, const POINT_F64 & pointSource);
void copy(POINT_F64 & pointTarget, const CGPoint & pointSource);

CGRect mm_get_screen_cgrect();

void ns_main_async(dispatch_block_t block);


void ns_main_sync(dispatch_block_t block);

time_t _mkgmtime(struct tm * const);



