#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE format_tool :
         virtual public ::user::tool_window
      {
      public:


         ::user::rich_text::eattribute          m_eattribute;
         // an array just to hold one format
         // the one the tool is editing
         __pointer_array(::user::rich_text::format)  m_formata;
         __composite(::user::button)                         m_pbuttonBold;
         __composite(::user::button)                         m_pbuttonItalic;
         __composite(::user::button)                         m_pbuttonUnderline;
         __composite(::user::font_combo_box)                 m_pcomboFamily;
         __composite(::user::combo_box)                      m_pcomboSize;
         __composite(::user::button)                         m_pbuttonForeground;
         __composite(::user::button)                         m_pbuttonBackground;
         __composite(::user::button)                         m_pbuttonSubscript;
         __composite(::user::button)                         m_pbuttonSuperscript;
         __composite(::user::button)                         m_pbuttonLineHeight;
         __composite(::user::button)                         m_pbuttonAlignLeft;
         __composite(::user::button)                         m_pbuttonAlignCenter;
         __composite(::user::button)                         m_pbuttonAlignRight;



         format_tool();
         virtual ~format_tool();

         virtual e_status initialize(::context_object* pcontextobject)override;
      
         virtual void install_message_routing(::channel * psender) override;

         virtual ::user::enum_translucency get_translucency(::user::style* pstyle) const override;

         DECL_GEN_SIGNAL(on_message_create);

         virtual void set_font_size(double d);

         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         virtual bool is_showing_for_ui(::user::interaction * pinteraction);

         virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

         virtual void show_for_ui(::user::interaction * pinteraction);

         virtual void on_control_event(::user::control_event * pevent) override;


         virtual bool update_data(bool bSaveAndValidate) override;




      };


   } // namespace rich_text


} // namespace user




