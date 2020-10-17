#include "framework.h"


promise::promise(::matter * pmatter, ::future future) :
   m_pelement(pmatter),
   m_future(future)
{

   fork_run();

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


CLASS_DECL_ACME var __launch(::matter * pmatter, ::future future)
{

   if(future)
   {

      new promise(pmatter, future);

      return ::success_promise;

   }
   else
   {

      return pmatter->realize();

   }

}



