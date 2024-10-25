//
// Created by camilo on 2024-10-24 21:28 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace data
{


   class CLASS_DECL_ACME client :
      virtual public ::particle
   {
   public:

      client();
      ~client() override;

      virtual ::string calculate_data_key();
      virtual ::string calculate_data_key(const ::scoped_string & strKey);

   };


}



