//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/user/nano/pen.h"
#include "object.h"


namespace windows
{


   class CLASS_DECL_ACME nano_pen :
      virtual public ::nano_pen,
      virtual public nano_object
   {
   public:


      //__CreatableFromBase(nano_pen, ::nano_pen);


      nano_pen();
      ~nano_pen() override;

      
      void update(::nano_device * pnanodevice) override;


   };


} // namespace windows



