//
// Created by camilo on 25/04/2021. ~08:00 <3Thomas Borregaard Soerensen
//
//
#include "platform.h"
#include "signalization.h"


namespace parallelization
{


   signalization::signalization()
   {

      defer_create_synchronization();

   }


   signalization::~signalization()
   {

      //informationf("signalization::~signalization");

   }


} // namespace parallelization



