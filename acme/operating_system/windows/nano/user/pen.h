//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/pen.h"
#include "object.h"


namespace windows
{


   class CLASS_DECL_ACME ::nano::user::pen :
      virtual public ::nano::user::pen,
      virtual public nano_object
   {
   public:


      //__CreatableFromBase(::nano::user::pen, ::nano::user::pen);


      ::nano::user::pen();
      ~::nano::user::pen() override;

      
      void update(::nano::user::device * pnanodevice) override;


   };


} // namespace windows



