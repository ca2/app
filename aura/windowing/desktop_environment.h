//
// Created by camilo on 8/16/22. <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/platform/department.h"


namespace windowing
{


   class CLASS_DECL_AURA desktop_environment :
      virtual public ::acme::department
   {
   public:


      bool                                      m_bUnhook;
      ::pointer<::windowing::windowing>        m_pwindowing;


      desktop_environment();
      ~desktop_environment() override;


      virtual void get_monitor_rectangle(::index iMonitor, ::rectangle_i32 * prectangle);
      virtual void get_workspace_rectangle(::index iMonitor, ::rectangle_i32 * prectangle);


      virtual void windowing_post(const ::procedure & procedure);


      virtual bool message_loop_step();


   };


} // namespace windowing



