// Created by camilo on 2023-10-02 03:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_BASE auto_hide :
      virtual public ::user::interaction
   {
   public:


      bool                                         m_bEffectiveVisibleControl;
      bool                                         m_bControlVisibilityChanging;
      bool                                         m_bOverrideVisibleControl;
      bool                                         m_bHideControlOnFullScreenOrTransparentFrame;
      bool                                         m_bVisibleControl;
      bool                                         m_bForceHiddenControl;
      bool                                         m_bVisibleIfWindowActive;
      class ::time                                 m_timeLastControlVisibilityChange;



      auto_hide();
      ~auto_hide() override;


      virtual void auto_hide_calculate_control_visibility();

      virtual bool auto_hide_is_top_level_full_screen_or_transparent();

      virtual bool auto_hide_full_screen_or_transparent_frame_control_visibility();

      //virtual void calculate_tab_visibility();

      virtual int auto_hide_threshold_height();

      bool should_draw() override;

      void on_timer(::timer * ptimer) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      DECLARE_MESSAGE_HANDLER(auto_hide_on_message_create);
      DECLARE_MESSAGE_HANDLER(auto_hide_on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(auto_hide_on_message_mouse_leave);


   };


} // namespace user
