#include "framework.h"


namespace promise
{


   ::payload __realize(::matter *pmatter, ::promise::process process = ::promise::process());


   promise::promise(::matter *pmatter, const ::promise::process &process) :
           m_pmatter(pmatter),
           m_process(process)
   {

      ::task::launch(this);

   }


   promise::~promise()
   {

   }


   ::e_status promise::on_task()
   {

      m_process(m_pmatter->realize());

      return ::success;

   }


   ::payload __realize(::matter *pmatter, ::promise::process process)
   {

      if (process)
      {

         new promise(pmatter, process);

         return ::success_promise;

      }
      else
      {

         return pmatter->realize();

      }

   }


} //  namespace promise



