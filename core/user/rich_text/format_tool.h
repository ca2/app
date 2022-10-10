#pragma once


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


         ::user::rich_text::e_attribute                           m_eattribute;
         // an array just to hold one format
         // the one the tool is editing
         pointer< pointer_array < ::user::rich_text::format > >    m_pformata;
         ::pointer<::user::button>                             m_pbuttonBold;
         ::pointer<::user::button>                             m_pbuttonItalic;
         ::pointer<::user::button>                             m_pbuttonUnderline;
         ::pointer<::user::font_combo_box>                     m_pcomboFamily;
         ::pointer<::user::combo_box>                          m_pcomboSize;
         ::pointer<::user::button>                             m_pbuttonForeground;
         ::pointer<::user::button>                             m_pbuttonBackground;
         ::pointer<::user::button>                             m_pbuttonSubscript;
         ::pointer<::user::button>                             m_pbuttonSuperscript;
         ::pointer<::user::button>                             m_pbuttonLineHeight;
         ::pointer<::user::button>                             m_pbuttonAlignLeft;
         ::pointer<::user::button>                             m_pbuttonAlignCenter;
         ::pointer<::user::button>                             m_pbuttonAlignRight;



         format_tool();
         ~format_tool() override;

         
         void initialize(::object * pobject)override;
      
         void install_message_routing(::channel * psender) override;

         ::user::enum_translucency get_translucency(::user::style* pstyle) const override;

         DECLARE_MESSAGE_HANDLER(on_message_create);

         virtual void set_font_size(double d);

         void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         virtual bool is_showing_for_ui(::user::interaction * pinteraction);

         void on_layout(::draw2d::graphics_pointer & pgraphics) override;

         virtual void show_for_ui(::user::interaction * pinteraction);

         void handle(::topic * ptopic, ::context * pcontext) override;


         void update_data(bool bSaveAndValidate) override;


      };


   } // namespace rich_text


} // namespace user



