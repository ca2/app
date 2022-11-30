//
//  _numeric_concepts.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "acme/primitive/primitive/e_status.h"


template < typename T >
concept a_enum = std::is_enum < T >::value;

template < typename T >
concept primitive_integral =
   std::is_integral_v < T > ||
   std::is_enum < T >::value ||
   std::is_same < T, ::e_status >::value;


template < typename T >
concept primitive_integer = std::is_integral < T >::value;

template < typename T >
concept primitive_natural = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept primitive_signed = (std::is_integral < T >::value || std::is_enum < T >::value) && std::is_signed < T >::value;

template < typename T >
concept primitive_signed_not_8bit = primitive_signed < T > && sizeof(T) != 1;

template < typename T >
concept primitive_unsigned = (std::is_integral < T >::value || std::is_enum < T >::value) && !std::is_signed < T >::value;

template < typename T >
concept primitive_unsigned_not_8bit = primitive_unsigned < T > && sizeof(T) != 1;

template < typename T >
concept primitive_floating = std::is_floating_point < T >::value;

template < typename NUMBER >
concept primitive_number =
   std::is_integral_v < NUMBER > ||
   std::is_enum_v < NUMBER > ||
   std::is_floating_point_v < NUMBER >;
