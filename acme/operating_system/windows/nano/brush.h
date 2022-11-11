//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/user/nano/brush.h"
#include "object.h"


namespace windows
{


   class CLASS_DECL_ACME nano_brush :
      virtual public ::nano_brush,
      virtual public nano_object
   {
   public:


      //CreatableFromBase(nano_brush, ::nano_brush);


      nano_brush();
      ~nano_brush() override;

      
      void update(::nano_device * pnanodevice) override;


   };


} // namespace windows



