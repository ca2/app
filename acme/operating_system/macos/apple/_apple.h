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


void screen_coordinates_aware_copy(CGRect & rectTarget, const ::int_rectangle & rectSource);
void screen_coordinates_aware_copy(::int_rectangle & rectTarget, const CGRect & rectSource);

//void copy(CGRect & rectTarget, const ::int_rectangle & rectSource);
//void copy(::int_rectangle & rectTarget, const CGRect & rectSource);


//void copy(CGPoint & pointTarget, const ::int_point & pointSource);
//void copy(::int_point & pointTarget, const CGPoint & pointSource);
//void copy(CGPoint & pointTarget, const ::double_point & pointSource);
//void copy(::double_point & pointTarget, const CGPoint & pointSource);

CGRect mm_get_screen_cgrect();

void ns_main_post(dispatch_block_t block);

void ns_main_send(dispatch_block_t block);

posix_time _mkgmtime(struct tm * const);



