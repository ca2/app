//
// Created by camilo on 2024-09-26 18:54 Odense Time <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/window.h"
#include "apex/message/channel.h"


namespace windowing
{


   class CLASS_DECL_APEX window_base :
      virtual public ::acme::windowing::window,
      virtual public ::channel
   {
   public:


      window_base();
      ~window_base() override;


      void destroy() override;


   };


} // windowing




