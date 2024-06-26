// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
// From acme/nano/idn by camilo on 2024-06-02 21:51 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/nano/idn/idn.h"


namespace windows_common
{


   namespace nano
   {


      namespace idn
      {


         class CLASS_DECL_ACME idn :
            virtual public ::nano::idn::idn
         {
         public:


            inline static const char* represented_component_name()
            {

               return "nano_idn";

            }


            idn();
            ~idn() override;


            string idn_to_punycode(const ::string& str) override;
            string idn_from_punycode(const ::string& str) override;


         };


      } // idn


   } // nano


} // namespace windows_common


