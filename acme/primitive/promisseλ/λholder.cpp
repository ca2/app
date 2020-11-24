#include "framework.h"


λarray::λarray()
{

}


λarray::~λarray()
{

}


void λarray::run_all()
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



