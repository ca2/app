// Created by camilo on 2022-03-30 <3ThomasBorregaardSorensen!!
#pragma once


#include "check.h"
#include "text.h"


namespace user
{


   class command_update_target :
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      virtual void enable_window(bool bEnable) = 0;


   };


} // namespace user



