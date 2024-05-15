//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/pen.h"
#include "object.h"


namespace windows
{


   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_ACME pen :
            virtual public ::nano::user::pen,
            virtual public object
         {
         public:


            //__CreatableFromBase(::nano::user::pen, ::nano::user::pen);


            pen();
            ~pen() override;


            void update(::nano::user::device* pnanodevice) override;


         };



      } // namespace user


   } // namespace nano

} // namespace windows



