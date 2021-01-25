#pragma once


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

         
         ::id                    m_id;
         bool                    m_bPresent;
         __pointer(button)       m_pbutton;


         item() 
         {
         
            m_bPresent = true;

         }


      };


      __declare_map(enum_button_item_map, enum_button_item, enum_button, m_ebutton, __pointer(item), m_pitem);


      ::experience::frame_window *              m_pframewindow;
      millis                                    m_millisShow;
      bool                                      m_bShowAttempt;
      bool                                      m_bDrag;
      point                                     m_pointDrag;
      i32                                       m_iDefaultButtonMargin;
      i32                                       m_iDefaultButtonSize;
      ::size                                    m_sizeButtonDefault;
      ::draw2d::font_pointer                    m_fontMarlett;

      ::draw2d::brush_pointer                   m_brushButtonBack;
      ::draw2d::brush_pointer                   m_brushButtonBackSel;
      ::draw2d::brush_pointer                   m_brushButtonBackFocus;
      ::draw2d::brush_pointer                   m_brushButtonBackDisabled;

      ::draw2d::pen_pointer                     m_penButtonBack;
      ::draw2d::pen_pointer                     m_penButtonBackSel;
      ::draw2d::pen_pointer                     m_penButtonBackFocus;
      ::draw2d::pen_pointer                     m_penButtonBackDisabled;

      ::color                                   m_colorButtonFore;
      ::color                                   m_colorButtonForeSel;
      ::color                                   m_colorButtonForeFocus;
      ::color                                   m_colorButtonForeDisabled;

      enum_button_item_map                      m_itemmap;
      id_map < enum_button >                    m_idmap;
            
      ::color                                   m_colorBackground;


      control_box();
      virtual ~control_box();


      virtual void set_button_color_system_default_001();


      virtual void install_message_routing(::channel *pframewindow);

      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics);

      void drag(const ::point & point);


      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      virtual ::size get_button_size(enum_button ebutton);

      virtual ::rect get_button_margin(enum_button ebutton);

      virtual i32 calc_button_size(::draw2d::graphics_pointer & pgraphics);

      virtual i32 calc_control_box_width(::draw2d::graphics_pointer & pgraphics);

      virtual void reset_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void _layout_button(enum_button ebutton, ::rect & rect);
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
      virtual e_stock_icon get_control_box_button_stock_icon(enum_button ebutton);
      virtual ::e_status set_control_box_button_id(enum_button ebutton, id id);
      virtual id get_control_box_button_id(enum_button ebutton) const;
      virtual string get_control_box_button_tag(enum_button ebutton) const;
      virtual enum_button get_control_box_button_type(id id) const;
      __pointer(button) get_button(enum_button ebutton);
      virtual __pointer(button) get_box_button(enum_button ebutton);

      virtual ::count get_visible_control_box_button() const;

      virtual bool get_font(::draw2d::font_pointer & font);


   };



} // namespace experience



