//
//  apple_debug.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 06/01/18.
//

#include "debug.h"

void throw_ns_exception()
{
   
   __throw(ns_exception());
   
}
