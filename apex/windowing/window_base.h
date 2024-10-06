//
// Created by camilo on 2024-09-26 18:54 Odense Time <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/windowing/window.h"


namespace windowing
{


   class CLASS_DECL_APEX window_base :
      virtual public ::nano::windowing::window
   {
   public:


      window_base();
      ~window_base() override;


   };


} // windowing




