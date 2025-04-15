#pragma once


#include "interaction.h"
#include "acme/user/user/check.h"


namespace user
{


   class CLASS_DECL_AURA button :
      virtual public ::user::interaction,
      virtual public ::user::check
   {
   public:


      enum enum_style
      {
         e_style_none,
         e_style_normal,
         e_style_simple,
         e_style_image,
         e_style_image_and_text,
         e_style_push,
         e_style_push_group,
         e_style_list,
         e_style_stock_icon,
      };

      class bitmap :
         virtual public ::particle
      {
      public:

         ::image::image_pointer                    m_pimage;          // not pressed default bitmap
         ::image::image_pointer                    m_pimageSel;       // pressed bitmap
         ::image::image_pointer                    m_pimageFocus;     // focus bitmap
         ::image::image_pointer                    m_pimageDisabled;  // disabled bitmap
         ::image::image_pointer                    m_pimageHover;     // hover bitmap

      };


      class list :
         virtual public ::particle
      {
      public:

         ::image::image_list_pointer          m_pimagelistNormal;
         ::image::image_list_pointer          m_pimagelistItemHover;
         ::image::image_list_pointer          m_pimagelistSubItemHover;
         int                              m_iImageNormal;
         int                              m_iImageItemHover;
         int                              m_iImageSubItemHover;

      };

      //normal

      //e_rect                            m_erectMargin;
      //e_rect                            m_erectBorder;
      //e_rect                            m_erectPadding;
      ::e_align                           m_ealignText;
      ::e_draw_text                       m_edrawtext;
      enum_style                          m_estyle;
      //::int_rectangle                     m_rectangleText;
      ::collection::index                               m_iClick;
      enum_stock_icon                     m_estockicon;
      ::int_rectangle                     m_rectangleCheckBox;
      ::pointer < bitmap >                m_pbitmap;
      ::pointer < list >                  m_plist;


      button();
      button(const ::string & pszName, const ::atom & atom);
      ~button() override;


      void user_button_construct();


      ::subparticle_pointer clone() override;

      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;


      ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) override;
      enum_translucency get_translucency(style * pstyle) override;

      //virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      void install_message_routing(::channel * pchannel) override;
      
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawBitmap(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics, bool bDecoration);
      virtual void _001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, ::int_rectangle & rectText);

      virtual void _001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics);

      virtual ::color::color _001GetButtonBackgroundColor();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool is_custom_draw() override;


      void on_check_changed(::data::check_change & change) override;


      //using ::user::check::set_check;
      //virtual void set_check(const ::e_check & check, const ::action_context & action_context) override;
      //virtual ::enum_check get_check() override;

      //virtual bool is_pressed();


      //virtual ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);


      ::double_size get_fitting_size(::draw2d::graphics_pointer & pgraphics) override;
      ::double_size get_preferred_size(::draw2d::graphics_pointer & pgraphics) override;

      bool keyboard_focus_is_focusable() override;

      //virtual bool has_action_hover() override;

      bool LoadBitmaps(::payload payload,::payload varSel = ::e_type_null,::payload varFocus = ::e_type_null,::payload varDisabled = ::e_type_null,::payload varHover = ::e_type_null);


      virtual void set_button_style(enum_style estyle);
      virtual void on_enter_button_style(enum_style estyle);
      virtual void on_exit_button_style(enum_style estyle);

      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
      virtual void BaseToolTipGetRect(::int_rectangle & rectangle);

      virtual int BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pmessage) override;

      void on_set_window_text() override;

      bool on_perform_layout(::draw2d::graphics_pointer& pgraphics) override;


      void set_stock_icon(enum_stock_icon eicon) override;
      enum_stock_icon get_stock_icon() override;

      //virtual ::color::color get_button_text_color();


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      bool on_click_generation(::item * pitem, ::user::mouse * pmouse) override;


      //bool on_click(::item * pitem) override;


   };


} // namespace user



