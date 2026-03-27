// Created by camilo on 2024-03-01 01:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "group.h"


namespace coding
{


   class CLASS_DECL_CODING group_new_release_prefix :
      virtual public group
   {
   public:


      //::string m_strNewaMachineBox;


      group_new_release_prefix();
      ~group_new_release_prefix() override;


      //virtual void initialize_group_new_release_prefix(const ::string_array& straMachineBox);
      virtual void initialize_group_new_release_prefix();


      ::collection::count get_size() override;
      enum_integrate get_eintegrate(::collection::index i) override;
      ::string get_name(::collection::index i) override;
      ::string get_short_name(::collection::index i) override;


   };


} // namespace coding



