//
// Created by camilo on 2024-04-19 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/user.h"


namespace x11
{


   namespace nano
   {
      namespace user
      {
         class CLASS_DECL_ACME user :
            virtual public ::nano::user::user
         {
         public:


            user();
            ~user();


            void x11_sync(const ::procedure & procedure) override;
            void x11_async(const ::procedure & procedure) override;


         };


      } // namespace user


   } // namespace nano


} // namespace x11



