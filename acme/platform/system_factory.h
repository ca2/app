// Created by camilo with Mummi on 2024-06-14 21:24 <3ThomasBorregaardSorensen!!
#pragma once


namespace acme
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

            auto pplatform = platform();

            auto pfactory = pplatform->factory();

            bool bHasFactoryRepresentativeType = pfactory->has<FACTORY_REPRESENTATIVE_TYPE>();

            if (!bHasFactoryRepresentativeType)
            {

               ::string strComponent = FACTORY_REPRESENTATIVE_TYPE::represented_component_name();

               system()->on_component_factory(strComponent);

            }

            __construct(p);

         }

         return p;

      }


   };


} // namespace acme



