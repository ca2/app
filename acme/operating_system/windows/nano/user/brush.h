//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/brush.h"
#include "object.h"


namespace windows
{


   class CLASS_DECL_ACME ::nano::user::brush :
      virtual public ::nano::user::brush,
      virtual public nano_object
   {
   public:


      //CreatableFromBase(::nano::user::brush, ::nano::user::brush);


      ::nano::user::brush();
      ~::nano::user::brush() override;

      
      void update(::nano::user::device * pnanodevice) override;


   };


} // namespace windows



