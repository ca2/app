//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/brush.h"
#include "object.h"


namespace windows
{



   namespace nano
   {


      namespace user
      {

         class CLASS_DECL_ACME brush :
            virtual public ::nano::user::brush,
            virtual public nano_object
         {
         public:


            //CreatableFromBase(brush, brush);


            brush();
            ~brush() override;


            void update(::nano::user::device* pnanodevice) override;


         };



      } // namespace user


   } // namespace nano


} // namespace windows



