// Created by camilo on 2024-06-27 20:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "code_application.h"
#include "apex/platform/app_consumer.h"


namespace coding
{


   class CLASS_DECL_CODING option :
      virtual public app_consumer < ::coding::code_application >
   {
   public:


      ::property  m_property;
      ::atom_array      m_atomaOptions;
      ::string_array    m_straName;
      ::string_array    m_straDescription;


      option();
      ~option() override;

      
      void create_option(const ::property & property, const ::atom_array& atomaOptions, const ::string_array & straName, const ::string_array& straDescription);


   };


} // namespace coding



