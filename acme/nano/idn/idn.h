// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"


namespace nano
{


   namespace idn
   {


      class CLASS_DECL_ACME idn :
        virtual public ::platform::department
      {
      public:


         inline static const_char_pointer represented_component_name()
         {

            return "nano_idn";

         }


         idn();
         ~idn() override;


         virtual string idn_to_punycode(const ::scoped_string & scopedstr);
         virtual string idn_from_punycode(const ::scoped_string & scopedstr);


      };


   } // idn


} // nano


