#include "framework.h"


predicate_array::predicate_array()
{

}


predicate_array::~predicate_array()
{

}


void predicate_array::run_all()
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



