#include "framework.h"


promise::promise(::matter * pmatter, const ::future & future) :
   m_pmatter(pmatter),
   m_future(future)
{

   ::task::launch(this);

}


promise::~promise()
{

}


::estatus promise::on_task()
{

   m_future(m_pmatter->realize());

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



