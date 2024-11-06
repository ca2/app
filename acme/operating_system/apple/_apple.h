//
//  _apple.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/02/20.
//
//
//  _apple_no_templates.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 18/08/21.
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#pragma once


//#include <CoreGraphics/CoreGraphics.h>


//#include "acme/prototype/geometry2d/_geometry2d.h"


void throw_ns_exception(enum_status estatus, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrDescription, const ::property_set & propertyset);


void screen_coordinates_aware_copy(CGRect & rectTarget, const ::rectangle_i32 & rectSource);
void screen_coordinates_aware_copy(::rectangle_i32 & rectTarget, const CGRect & rectSource);

//void copy(CGRect & rectTarget, const ::rectangle_i32 & rectSource);
//void copy(::rectangle_i32 & rectTarget, const CGRect & rectSource);


//void copy(CGPoint & pointTarget, const ::point_i32 & pointSource);
//void copy(::point_i32 & pointTarget, const CGPoint & pointSource);
//void copy(CGPoint & pointTarget, const ::point_f64 & pointSource);
//void copy(::point_f64 & pointTarget, const CGPoint & pointSource);

CGRect mm_get_screen_cgrect();

void ns_main_post(dispatch_block_t block);

void ns_main_send(dispatch_block_t block);

posix_time _mkgmtime(struct tm * const);



