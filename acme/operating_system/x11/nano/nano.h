//
// Created by camilo on 2024-04-19 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/nano/nano.h"


namespace x11
{


   class CLASS_DECL_ACME nano :
      virtual public ::nano::nano
   {
   public:


      nano();
      ~nano();


      void x11_sync(const ::procedure & procedure) override;
      void x11_async(const ::procedure & procedure) override;


   };

} // namespace x11



