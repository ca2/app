// Created by camilo with Mummi on 2024-06-14 21:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/parallelization/synchronous_lock.h"


namespace platform
{


   class CLASS_DECL_ACME system_factory :
      virtual public ::particle
   {
   public:


      system_factory();
      ~system_factory() override;


      template < typename FACTORY_REPRESENTATIVE_TYPE >
      FACTORY_REPRESENTATIVE_TYPE* __factory(::pointer < FACTORY_REPRESENTATIVE_TYPE >& p)
      {

         if (!p)
         {

            auto psystem = system();

            _synchronous_lock synchronouslock(psystem->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            auto pfactory = psystem->factory();

            bool bHasFactoryRepresentativeType = pfactory->has<FACTORY_REPRESENTATIVE_TYPE>();

            if (!bHasFactoryRepresentativeType)
            {

               ::string strComponent = FACTORY_REPRESENTATIVE_TYPE::represented_component_name();

               printf_line("Trying to create component \"%s\".", strComponent.c_str());

               psystem->defer_component_factory(strComponent);

            }

            øconstruct(p);

         }

         return p;

      }


   };


} // namespace platform



