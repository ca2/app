#pragma once


#include "aura/user/user/main_window.h"


namespace app_app
{


   class CLASS_DECL_APP_APP main_window :
      virtual public ::user::main_window
   {
   public:


      double            m_dBreathPeriod;
      class ::time        m_timeStart;
      double            m_dPhaseShift;
      int               m_iCloseButtonDraw;


      main_window();
      ~main_window() override;





      virtual void on_create_user_interaction() override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem, const ::user::e_state & estate) override;


   };


} // namespace app_app



