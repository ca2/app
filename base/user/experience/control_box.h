#pragma once


#include "aura/user/user/box.h"


namespace experience
{


   class CLASS_DECL_BASE control_box :
      virtual public ::user::box
   {
   public:


      class CLASS_DECL_BASE item :
         virtual public ::matter
      {
      public:

         
         ::atom                    m_atom;
         bool                    m_bPresent;
         __pointer(button)       m_pbutton;


         item() 
         {
         
            m_bPresent = true;

         }


      };


      __declare_map(enum_button_item_map, enum_button_item, enum_button, m_ebutton, __pointer(item), m_pitem);


      ::experience::frame_window *           m_pframewindow;
      ::duration                             m_durationShow;
      bool                                   m_bShowAttempt;
      bool                                   m_bDrag;
      point_i32                              m_pointDrag;
      i32                                    m_iDefaultButtonMargin;
      i32                                    m_iDefaultButtonSize;
      ::size_i32                             m_sizeButtonDefault;
      ::write_text::font_pointer             m_pfontMarlett;

      ::draw2d::brush_pointer                m_pbrushButtonBack;
      ::draw2d::brush_pointer                m_pbrushButtonBackSel;
      ::draw2d::brush_pointer                m_pbrushButtonBackFocus;
      ::draw2d::brush_pointer                m_pbrushButtonBackDisabled;

      ::draw2d::pen_pointer                  m_ppenButtonBack;
      ::draw2d::pen_pointer                  m_ppenButtonBackSel;
      ::draw2d::pen_pointer                  m_ppenButtonBackFocus;
      ::draw2d::pen_pointer                  m_ppenButtonBackDisabled;

      ::color::color                         m_colorButtonFore;
      ::color::color                         m_colorButtonForeSel;
      ::color::color                         m_colorButtonForeFocus;
      ::color::color                         m_colorButtonForeDisabled;

      enum_button_item_map                   m_itemmap;
      id_map < enum_button >                 m_idmap;
            
      status < ::color::color  >      m_colorBackground;


      control_box();
      ~control_box() override;


      virtual void set_button_color_system_default_001();


      void install_message_routing(::channel *pframewindow) override;

      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      void drag(const ::point_i32 & point);


      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_move);
      DECLARE_MESSAGE_HANDLER(on_message_size);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual ::size_i32 get_button_size(enum_button ebutton);

      virtual ::rectangle_i32 get_button_margin(enum_button ebutton);

      virtual i32 calc_button_size(::draw2d::graphics_pointer & pgraphics);

      virtual i32 calc_control_box_width(::draw2d::graphics_pointer & pgraphics);

      virtual void reset_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void _layout_button(enum_button ebutton, ::rectangle_i32 & rectangle);
      virtual bool should_show_button(enum_button ebutton) const;

      virtual item * get_item(enum_button ebutton, bool bCreate = false);

      inline const item * get_item(enum_button ebutton) const
      {
         return ((control_box *)this)->get_item(ebutton);
      }

      virtual bool has_button(enum_button ebutton) const;
      virtual bool hide_button(enum_button ebutton, bool bHide = true);
      virtual bool create_buttons();
      virtual bool update_control_box_button(enum_button ebutton);
      virtual void update_control_box_buttons();
      virtual bool create_button(enum_button ebutton);
      virtual bool get_control_box_button_caption(enum_button ebutton, string & str) const;
      virtual enum_stock_icon get_control_box_button_stock_icon(enum_button ebutton);
      virtual void set_control_box_button_id(enum_button ebutton, atom atom);
      virtual atom get_control_box_button_id(enum_button ebutton) const;
      virtual string get_control_box_button_tag(enum_button ebutton) const;
      virtual enum_button get_control_box_button_type(atom atom) const;
      __pointer(button) get_button(enum_button ebutton);
      virtual __pointer(button) get_box_button(enum_button ebutton);

      virtual ::count get_visible_control_box_button() const;

      virtual bool get_font(::write_text::font_pointer & font);


   };



} // namespace experience



