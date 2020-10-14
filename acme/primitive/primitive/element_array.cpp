#include "framework.h"


element_array::~element_array()
{

}


void element_array::call_update(::i64 iUpdate)
{

   for(auto & pelement : *this)
   {

      pelement->call_update(iUpdate);

   }

}



