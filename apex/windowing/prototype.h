//
// Created by camilo on 2024-09-26 18:54 Odense Time <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/window_base.h"


namespace windowing
{

   class prototype :
      virtual public ::windowing::window_base
   {
     public:


       prototype();
       ~prototype() override;

   };

} // windowing


