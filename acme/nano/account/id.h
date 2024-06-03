//
// Created by camilo on 2024-06-02 20:06 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace nano
{


   namespace account
   {


      class id :
              virtual public ::particle
      {
      public:


         id();
         ~id() override;


         virtual bool is_equal(id * pid);
         virtual bool is_less(id * pid);
         virtual ::string as_string();

      };


   } // namespace account


} // namespace nano

