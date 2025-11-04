#pragma once


#include "core/user/user/_.h"
#include "format_host.h"
#include "aura/user/user/tool_window.h"
#include "core/user/user/font_combo_box.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE format_tool :
         virtual public ::user::tool_window
      {
      public:


         ::user::rich_text::e_attribute                              m_eattribute;
         // an array just to hold one format
         // the one the tool is editing
         ::pointer < ::user::rich_text::format >                     m_pformat;
         //::pointer < ::user::rich_text::format_host >                m_pformathost;
         ::pointer<::user::button>                                   m_pbuttonBold;
         ::pointer<::user::button>                                   m_pbuttonItalic;
         ::pointer<::user::button>                                   m_pbuttonUnderline;
         ::pointer<::user::font_combo_box>                           m_pcomboFamily;
         ::pointer<::user::combo_box>                                m_pcomboSize;
         ::pointer<::user::button>                                   m_pbuttonForeground;
         ::pointer<::user::button>                                   m_pbuttonBackground;
         ::pointer<::user::button>                                   m_pbuttonSubscript;
         ::pointer<::user::button>                                   m_pbuttonSuperscript;
         ::pointer<::user::button>                                   m_pbuttonLineHeight;
         ::pointer<::user::button>                                   m_pbuttonAlignLeft;
         ::pointer<::user::button>                                   m_pbuttonAlignCenter;
         ::pointer<::user::button>                                   m_pbuttonAlignRight;
         ::pointer<::user::color_selector_popup>                     m_pcolorselectorpopupForeground;
         ::pointer<::user::color_selector_popup>                     m_pcolorselectorpopupBackground;
         ::color::hls                                                m_hlsForeground;
         ::color::hls                                                m_hlsBackground;

         format_tool();
         ~format_tool() override;

         
         void initialize(::particle * pparticle)override;
      
         void install_message_routing(::channel * psender) override;

         ::user::enum_translucency get_translucency(::user::style* pstyle) override;

         DECLARE_MESSAGE_HANDLER(on_message_create);

         virtual void set_font_size(double d);

         void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         virtual bool is_showing_for_ui(::user::interaction * pinteraction);

         void on_layout(::draw2d::graphics_pointer & pgraphics) override;

         virtual void show_for_ui(::user::interaction * puserinteraction, ::user::rich_text::selection * pselection);

         void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


         void update_data(bool bSaveAndValidate) override;


      };


   } // namespace rich_text


} // namespace user



