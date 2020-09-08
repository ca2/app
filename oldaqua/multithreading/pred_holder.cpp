#include "framework.h"


pred_array::pred_array(::object * pobject)
{

}

pred_array::~pred_array()
{

}


void pred_array::run_all()
{

   for(auto & pred : *this)
   {

      if(!::thread_get_run())
      {

         break;

      }

      try
      {

         pred->run();

      }
      catch(...)
      {

      }

   }

}
