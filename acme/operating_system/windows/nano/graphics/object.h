//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/object.h"
#include "acme/_win32_gdi.h"


namespace windows
{




   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_ACME object :
            virtual public ::nano::graphics::object
         {
         public:


            HGDIOBJ     m_hgdiobj;


            object();
            ~object();


            void* operating_system_data() override;


            void destroy() override;


         };



      } // namespace graphics


   } // namespace nano


} // namespace windows



