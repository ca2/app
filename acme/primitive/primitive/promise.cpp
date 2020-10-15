#include "framework.h"


promise::promise(::element * pelement, ::future future) :
   m_pelement(pelement),
   m_future(future)
{

   os_fork();

}


promise::~promise()
{

}


::estatus promise::run()
{

   m_future.send(m_pelement->realize());

   delete this;

   return ::success;

}


CLASS_DECL_ACME var __launch(::element * pelement, ::future future)
{

   if(future)
   {

      new promise(pelement, future);

      return ::success_promise;

   }
   else
   {

      return pelement->realize();

   }

}



