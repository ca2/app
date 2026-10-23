#pragma once


#include "core/user/userex/_.h"
#include "berg/user/user/split_impact.h"
#include "berg/user/user/auto_hide.h"


namespace userex
{


   class CLASS_DECL_CORE top_impact :
      virtual public ::user::split_impact
   {
   public:


      top_edit_impact *                     m_peditimpact;
      top_toggle_impact *                   m_ptoggleimpact;
      bool m_bAutoHideOnFullScreen = false;
      bool m_bFullScreenEditorRevealed = false;
      bool m_bWasAutoHiddenFullScreen = false;
      ::i32 m_iFullScreenRevealHeight = 5;
      ::i32 m_iNormalEditorHeight = 31;
      ::i32 m_iFullScreenOverlaySpacing = 0;
      ::pointer<::user::auto_hide> m_pAutoHideCoordinator;
      bool m_bCoordinatedFullScreenAutoHide = false;
      bool m_bCoordinatedFullScreenVisible = false;

      void set_auto_hide_on_full_screen(bool bEnable = true);
      void set_auto_hide_coordinator(::user::auto_hide * pcoordinator,
         ::user::interaction * pprevious = nullptr);
      void update_full_screen_auto_hide();
      void destroy() override;
      void operator()(::timer * ptimer) override;


      top_impact();
      ~top_impact() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual void on_create_split_impact() override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual bool is_this_visible(::user::enum_layout elayout = ::user::e_layout_design) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;


   };


} // namespace userex







