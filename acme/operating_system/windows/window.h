// Created by camilo on 2024-09-13 15:55 <3ThomasBorregaardSorensen
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace windows
{


   class CLASS_DECL_ACME window :
      virtual public ::particle
   {
   public:

      double m_dVelocity;
      class ::time m_timeLastSizeMove;
      ::point_i32 m_pointSizeMoveStart;
      bool m_bMovingNow;
      bool m_bDefaultSystemMenu;
      bool m_bSizeMoveMode;
      HWND m_hwnd;
      HMENU m_hmenuSystem;

      window();
      ~window() override;

      virtual bool on_window_procedure(LRESULT & lresult, UINT message, WPARAM wparam, LPARAM lparam);
      virtual bool _on_default_system_menu_init_menu(LRESULT & lresult,  WPARAM wparam);
      virtual bool _on_default_system_menu_command(LRESULT & lresult, WPARAM wparam, LPARAM lparam);
      virtual void _defer_show_system_menu(const ::point_i32 & pointAbsolute);

   };


} // namespace windows







