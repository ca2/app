// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 18:09 <3ThomasBorregaardSorensen!!
// From dynamic_library by camilo on 2024-06-02 18:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"
#include "acme/prototype/collection/string_map.h"


namespace nano
{


   namespace account
   {


      class CLASS_DECL_ACME account :
              virtual public ::acme::department
      {
      public:


         inline static const_char_pointer represented_component_name()
         {

            return "nano_account";

         }


         string_map_base<::pointer<::nano::account::user>> m_usermap;

         account();
         ~account() override;


         void on_initialize_particle() override;


         virtual ::pointer<::nano::account::user> get_user(const ::pointer < ::nano::account::id > & pid);

         virtual ::pointer<::nano::account::user> _get_user(const ::pointer < ::nano::account::id > & pid);

         virtual ::pointer < ::nano::account::id > username_id(const ::scoped_string & scopedstrUsername);

         virtual ::pointer < ::nano::account::id > current_user_id();

      };


   } // dynamic_library


} // nano


