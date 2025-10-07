#pragma once


#include "berg/user/user/impact.h"


namespace user
{


   class CLASS_DECL_BERG menu_impact :
      virtual public ::user::impact
   {
   public:


      ::image::image_pointer                     m_pimageMem;
      //::pointer<::xml::document>          m_pxmldoc;
      ::image::image_pointer                     m_pimageLogo;
      ::write_text::font_pointer          m_pfontTitle;
      ::write_text::font_pointer          m_pfont;
      ::draw2d::brush_pointer             m_pbrushBkSel;
      ::draw2d::brush_pointer             m_pbrushBkHoverSel;
      ::draw2d::pen_pointer               m_ppenBkSel;
      ::draw2d::pen_pointer               m_ppen;
      string_map_base < ::image::image_pointer >      m_pimageMap;
      string_map_base < ::image::image_pointer >      m_pimageMapGray;
      //::int_array_base                         m_iaPopup;
      ::pointer < ::menu::item >             m_pmenuitem;


      menu_impact();
      ~menu_impact() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG

      long long increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      
      long long decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }

#endif

      void install_message_routing(::channel * pchannel) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      ::user::document * get_document();

      bool load_xml(::payload payloadFile);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);

      virtual ::user::item * layout_user_item_by_index(::collection::index iMenuItemIndex);


      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


      bool on_click(::item * pitem, ::user::mouse * pmouse) override;


      virtual void draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      virtual void draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::int_point & point1, const ::int_point& point2);
      virtual void draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      virtual void draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      virtual void draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      virtual void draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      virtual void draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      virtual void draw_item_separator(::draw2d::graphics_pointer & pgraphics, const ::int_point& point1, const ::int_point& point2);


   };


} // namespace user


