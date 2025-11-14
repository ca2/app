//
//  _random.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2023-06-05 00:42
//  Copyright (c) 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "quadruple.h"
#include "acme/prototype/mathematics/mathematics.h"


template < primitive_number NUMBER >
inline quadruple_type < NUMBER > random(::mathematics::mathematics * pmathematics, const quadruple_type < NUMBER > & quadruple1, const quadruple_type < NUMBER > & quadruple2)
{

   return quadruple_type < NUMBER >(
          pmathematics->random(quadruple1.x, quadruple2.x),
          pmathematics->random(quadruple1.y, quadruple2.y),
          pmathematics->random(quadruple1.c(), quadruple2.c()),
          pmathematics->random(quadruple1.d(), quadruple2.d()));

}


template < primitive_number NUMBER >
inline quadruple_type < NUMBER > homogeneous_minimum_maximum_rand(const quadruple_type < NUMBER > & quadruple1, const quadruple_type < NUMBER > & quadruple2)
{
   
   auto iRand = ::rand();

   return quadruple_type < NUMBER >(
          linear_rate(quadruple1.x, quadruple2.x, iRand, RAND_MAX),
          linear_rate(quadruple1.y, quadruple2.y, iRand, RAND_MAX),
          linear_rate(quadruple1.c(), quadruple2.c(), iRand, RAND_MAX),
          linear_rate(quadruple1.d(), quadruple2.d(), iRand, RAND_MAX));

}



