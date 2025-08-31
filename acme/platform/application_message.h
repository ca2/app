//
// Created by camilo on 2025-08-31 02:16 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   class CLASS_DECL_ACME application_message :
      virtual public ::particle
   {
   public:


      enum enum_message
      {

         e_message_none = 0,
         e_message_request_uri = 1,

      };


      enum_message m_emessage;

      long long   m_llWparam;
      long long   m_llLparam;
      ::memory    m_memory;


      application_message();
      ~application_message() override;


      void initialize_application_message(enum_message emessage, long long llWpara = 0, long long llLparam = 0, const ::block & block = {});


   };


} // platform

