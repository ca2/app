// Created by camilo on 2023-10-17 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE selection :
         virtual public ::particle
      {
      public:


         selection();
         ~selection() override;


         virtual ::pointer<::user::rich_text::format>get_selection_common_format();


      };


   } // namespace rich_text


} // namespace user



