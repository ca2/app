// Created by camilo on 2022-05-06 03:44 <3ThomasBorregaardSorensen!!
#pragma once


namespace acme
{


   class asset;
   

   class CLASS_DECL_ACME asset_manager :
      public ::particle
   {
   public:


      
      asset_manager();
      ~asset_manager() override;


      virtual ::pointer<asset>get_asset(const_char_pointer  path);


   };


} // namespace acme


