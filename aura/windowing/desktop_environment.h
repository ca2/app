//
// Created by camilo on 8/16/22. <3ThomasBorregaardSorensen!!
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


      desktop_environment();
      ~desktop_environment() override;


      virtual bool get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle);
      virtual bool get_workspace_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle);


      //virtual void windowing_post(const ::procedure & procedure);
      virtual ::pointer < ::graphics::graphics > create_graphics();

      virtual bool message_loop_step();

      virtual ::string get_user_theme();
      virtual void set_user_theme(const ::scoped_string & scopedstrUserTheme);


   };


} // namespace windowing



