//
// Created by camilo on 25/04/2021. ~08:00 <3Thomas Borregaard Sørensen
//
//
#include "framework.h"
#include "signalization.h"


namespace parallelization
{


   signalization::signalization()
   {

      defer_create_synchronization();

   }


   signalization::~signalization()
   {

      //::output_debug_string("signalization::~signalization");

   }


} // namespace parallelization



