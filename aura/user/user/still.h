#pragma once


#include "interaction.h"


namespace user
{


   class CLASS_DECL_AURA still :
      virtual public ::user::interaction
   {
   public:


      ::write_text::font_pointer          m_pfont;
      ::image::image_pointer                     m_pimage;          // not pressed default bitmap
      //::int_rectangle                   m_rectangleMargin;
      //::int_rectangle                   m_rectangleBorder;
      //::int_rectangle                   m_rectanglePadding;
      ::e_align                           m_ealignText;
      enum_still                          m_estill;
      //::int_rectangle                     m_rectangleText;
      ::collection::index                               m_iClick;
      enum_stock_icon                     m_estockicon;
      ::image::icon_pointer              m_picon;
      ::pointer < ::write_text::text_out_array > m_ptextouta;
      //::string                            m_strTextOutArray;

      ::int_rectangle                     m_rectangleCheckBox;
      string                              m_strLink;

      still();
      ~still() override;


      ::appearance::appearance * get_appearance() override;

      //virtual bool should_hover();

      bool has_link() override;

      //virtual bool create_interaction(::user::interaction * pinteractionParent) override;

      ::write_text::font_pointer get_font(style * pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) override;

      void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      virtual void set_text_align(::e_align ealignText);

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDrawImage(::draw2d::graphics_pointer & pgraphics);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      //void set_check(const ::e_check & check, const ::action_context & action_context) override;
      //virtual ::enum_check get_check() override;
       
      using ::user::interaction::get_color;
      ::status < ::color::color > get_color(::user::style * pstyle, enum_element eelement, ::user::enum_state elayout = e_state_none) override; 


      virtual void set_text_color(::status < ::color::color > statuscolor);

      //virtual bool is_pressed();

      //virtual ::write_text::font_pointer get_font(style * pstyle, enum_element eelement, estate estate = e_state_none) const;

      virtual void defer_update_text_out_array(::draw2d::graphics_pointer & pgraphics);

      //virtual ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_middle_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_create);


      ::double_size get_fitting_size(::draw2d::graphics_pointer & pgraphics) override;


      bool keyboard_focus_is_focusable() override;

      // virtual bool has_action_hover() override;

      bool LoadBitmaps(::payload payload, ::payload varSel = ::e_type_null, ::payload varFocus = ::e_type_null, ::payload varDisabled = ::e_type_null, ::payload varHover = ::e_type_null);


      virtual void set_still_type(enum_still estill);
      virtual enum_still get_still_type() const;


      virtual void on_enter_still_style(enum_still estill);
      virtual void on_exit_still_style(enum_still estill);


      virtual ::image::icon * still_get_icon();


      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
      virtual void BaseToolTipGetRect(::int_rectangle & rectangle);

      virtual int BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pmessage) override;


      ::item_pointer on_hit_test(const ::int_point & point, e_zorder ezorder) override;

      void on_set_window_text() override;
      bool on_perform_layout(::draw2d::graphics_pointer & pgraphics) override;
      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      void set_stock_icon(enum_stock_icon eicon) override;
      enum_stock_icon get_stock_icon() override;


   };


} // namespace user



