// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
#pragma once


namespace nano
{


   namespace idn
   {


      class CLASS_DECL_ACME idn :
        virtual public ::acme::department
      {
      public:


         inline static const char * represented_component_name()
         {

            return "nano_idn";

         }


         idn();
         ~idn() override;


         virtual string idn_to_punycode(const ::string & str);
         virtual string idn_from_punycode(const ::string & str);


      };


   } // idn


} // nano


