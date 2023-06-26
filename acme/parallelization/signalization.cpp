//
// Created by camilo on 25/04/2021. ~08:00 <3Thomas Borregaard Soerensen
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

      //::infomration("signalization::~signalization");

   }


} // namespace parallelization



