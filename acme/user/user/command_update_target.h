// Created by camilo on 2022-03-30 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/data/property_container.h"


namespace user
{


   class command_update_target :
      virtual public ::data::property_container
   {
   public:



      virtual void enable_window(bool bEnable) = 0;



   };


} // namespace user



