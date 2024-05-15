//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/object.h"
#include "acme/_win32_gdi.h"


namespace windows
{




   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_ACME object :
            virtual public ::nano::user::object
         {
         public:


            HGDIOBJ     m_hgdiobj;


            object();
            ~object();


            void* operating_system_data() override;


            void destroy() override;


         };



      } // namespace user


   } // namespace nano


} // namespace windows



