#pragma once


#include "base/user/user/impact.h"


namespace user
{


   class CLASS_DECL_BASE menu_impact :
      virtual public ::user::impact
   {
   public:


      ::image_pointer                     m_pimageMem;
      ::pointer<::xml::document>       m_pxmldoc;
      ::image_pointer                     m_pimageLogo;
      ::write_text::font_pointer          m_pfontTitle;
      ::write_text::font_pointer          m_pfont;
      ::draw2d::brush_pointer             m_pbrushBkSel;
      ::draw2d::brush_pointer             m_pbrushBkHoverSel;
      ::draw2d::pen_pointer               m_ppenBkSel;
      ::draw2d::pen_pointer               m_ppen;
      string_map < ::image_pointer >      m_pimageMap;
      string_map < ::image_pointer >      m_pimageMapGray;
      int_array                           m_iaPopup;


      menu_impact();
      ~menu_impact() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG

      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }

#endif

      void install_message_routing(::channel * pchannel) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      bool load_xml(::payload payloadFile);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);

      virtual bool get_item_rect(index i, RECTANGLE_I32 * prectangle);


      ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;


      bool on_click(::item * pitem) override;

      virtual void draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point1, const ::point_i32& point2);
      virtual void draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32& point1, const ::point_i32& point2);


   };


} // namespace user


