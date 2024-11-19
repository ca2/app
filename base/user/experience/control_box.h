#pragma once


#include "aura/user/user/box.h"
#include "base/user/user/auto_hide.h"


namespace experience
{


   class CLASS_DECL_BASE control_box :
      virtual public ::user::box,
      virtual public ::user::auto_hide
   {
   public:


      class CLASS_DECL_BASE item :
         virtual public ::matter
      {
      public:

         
         ::atom                    m_atom;
         bool                    m_bPresent;
         ::pointer<button>      m_pbutton;


         item() 
         {
         
            m_bPresent = true;

         }


      };


      using enum_button_item_map = ::map < enum_button, ::pointer < item > >;


      ::experience::frame_window *           m_pframewindow;
      class ::time                           m_timeShow;
      bool                                   m_bShowAttempt;
      bool                                   m_bDrag;
      int_point                              m_pointDrag;
      int                                    m_iDefaultButtonMargin;
      int                                    m_iDefaultButtonSize;
      ::int_size                             m_sizeButtonDefault;
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
      atom_map < enum_button >               m_idmap;
            
      status < ::color::color  >             m_colorBackground;


      control_box();
      ~control_box() override;


      virtual void set_button_color_system_default_001();


      void install_message_routing(::channel *pframewindow) override;

      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      void drag(const ::int_point & point);


      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_move);
      DECLARE_MESSAGE_HANDLER(on_message_size);


      void on_timer(::timer * ptimer) override;

      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void layout_control_box_buttons();

      virtual ::int_size get_button_size(enum_button ebutton);

      virtual ::int_rectangle get_button_margin(enum_button ebutton);

      virtual int calculate_button_size(::draw2d::graphics_pointer & pgraphics);

      virtual int calculate_control_box_width(::draw2d::graphics_pointer & pgraphics);

      //virtual void reset_layout(::draw2d::graphics_pointer & pgraphics);

      int auto_hide_threshold_height() override;

      virtual void _layout_button(enum_button ebutton, ::int_rectangle & rectangle);
      virtual bool should_show_button(enum_button ebutton) const;

      virtual item * get_item(enum_button ebutton, bool bCreate = false);

      inline const item * get_item(enum_button ebutton) const
      {
         return ((control_box *)this)->get_item(ebutton);
      }

      virtual bool has_button(enum_button ebutton) const;
      virtual bool hide_button(enum_button ebutton, bool bHide = true);
      virtual bool create_buttons();
      virtual void destroy_buttons();
      virtual bool update_control_box_button(enum_button ebutton);
      virtual void update_control_box_buttons();
      virtual bool create_button(enum_button ebutton);
      virtual bool get_control_box_button_caption(enum_button ebutton, string & str) const;
      virtual enum_stock_icon get_control_box_button_stock_icon(enum_button ebutton);
      virtual void set_control_box_button_id(enum_button ebutton, atom atom);
      virtual atom get_control_box_button_id(enum_button ebutton) const;
      virtual string get_control_box_button_tag(enum_button ebutton) const;
      virtual enum_button get_control_box_button_type(atom atom) const;
      ::pointer<button>get_button(enum_button ebutton);
      virtual ::pointer<button>get_box_button(enum_button ebutton);

      virtual ::collection::count get_visible_control_box_button() const;

      virtual bool get_font(::write_text::font_pointer & font);


      void handle(::topic * ptopic, ::context * pcontext) override;


   };



} // namespace experience



