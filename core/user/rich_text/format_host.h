// Created by camilo on 2023-10-09 18:10 <3ThomasBorregaardSorensen!!
#pragma once


#include "format.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE format_host :
         virtual public ::pointer_array < ::user::rich_text::format >
      {
      public:


         format_host();
         ~format_host() override;

         virtual ::pointer<::user::rich_text::format>add_format();

         //virtual ::pointer<::user::rich_text::format>get_selection_common_format();


      };


   } // namespace rich_text


} // namespace user



