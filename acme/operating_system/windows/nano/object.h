//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/user/nano/object.h"
#include "acme/_operating_system.h"


namespace windows
{


   class CLASS_DECL_ACME nano_object :
      virtual public ::nano_object
   {
   public:


      HGDIOBJ     m_hgdiobj;


      nano_object();
      ~nano_object();


      void * operating_system_data() override;


      void destroy() override;


   };


} // namespace windows



