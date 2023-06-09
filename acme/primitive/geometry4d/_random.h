//
//  _random.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-06-05 00:42
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "quadruple.h"
#include "acme/primitive/mathematics/_random.h"


template < primitive_number NUMBER >
inline quadruple_type < NUMBER > minimum_maximum_rand(const quadruple_type < NUMBER > & quadruple1, const quadruple_type < NUMBER > & quadruple2)
{

   return quadruple_type < NUMBER >(
          minimum_maximum_rand(quadruple1.a(), quadruple2.a()),
          minimum_maximum_rand(quadruple1.b(), quadruple2.b()),
          minimum_maximum_rand(quadruple1.c(), quadruple2.c()),
          minimum_maximum_rand(quadruple1.d(), quadruple2.d()));

}


template < primitive_number NUMBER >
inline quadruple_type < NUMBER > homogeneous_minimum_maximum_rand(const quadruple_type < NUMBER > & quadruple1, const quadruple_type < NUMBER > & quadruple2)
{
   
   auto iRand = ::rand();

   return quadruple_type < NUMBER >(
          linear_rate(quadruple1.a(), quadruple2.a(), iRand, RAND_MAX),
          linear_rate(quadruple1.b(), quadruple2.b(), iRand, RAND_MAX),
          linear_rate(quadruple1.c(), quadruple2.c(), iRand, RAND_MAX),
          linear_rate(quadruple1.d(), quadruple2.d(), iRand, RAND_MAX));

}



