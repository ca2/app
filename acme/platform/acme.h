//
//  base_static_start.h
//  acme
//
//  Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
#pragma once


//#include "acme/_operating_system.h"
//#include "platform.h"


namespace platform
{


   class platform;


} // namespace platform


namespace acme
{

   
   class CLASS_DECL_ACME acme
   {
   public:


//      ::pointer < ::platform::platform >     m_pplatform;


      acme();
      ~acme();


      //void acme_construct();
      //void acme_destruct();






      //void add_release_on_end(::particle* pparticle);


      //virtual ::platform::platform * __get_platform();


   };


   //template < typename APPLICATION > 
   //class acme_impl :
   //   virtual public ::acme::acme
   //{
   //public:


   //   ::platform::platform_impl < typename APPLICATION::SYSTEM >        m_platform;

   //   ::platform::platform * __get_platform() override { return &m_platform; }

   //   APPLICATION new_application() override 
   //   { 
   //   
   //      return new APPLICATION; 
   //   
   //   }

   //   acme_impl()
   //   {

   //      acme_initialize();

   //   }

   //};

   
} // namespace acme

