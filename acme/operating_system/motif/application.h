//
// Created by camilo on 2023-12-19 04:15 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#pragma once


#define register
#include <Xm/Xm.h>
#include <X11/Intrinsic.h>
#undef register


namespace motif
{


   class application
   {
   public:


      XtAppContext   m_pappcontext;
      Widget         m_pwidgetTop;


      application();
      ~application();

      void set_exit_flag();

      void app_main_loop();

   };


} // motif



