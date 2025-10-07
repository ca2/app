//
// Created by camilo on 2024-12-05 17:05 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"


namespace windows
{


   class window;


   class CLASS_DECL_ACME windowing :
      virtual public ::acme::windowing::windowing
   {
   public:

      
      map_base < ::oswindow, ::pointer < ::windows::window > >     m_windowmap;


      windowing();
      ~windowing() override;



   };


} // namespace windows



