#include "framework.h"


promise::promise(::matter * pmatter, ::future future) :
   m_pelement(pmatter),
   m_future(future)
{

   task::start(this);

}


promise::~promise()
{

}


::estatus promise::on_task()
{

   m_future.send(m_pelement->realize());

   //delete this;

   return ::success;

}


CLASS_DECL_ACME var __realize(::matter * pmatter, ::future future)
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



