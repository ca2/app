#pragma once


#include "menu.h"


namespace user
{


   class CLASS_DECL_BASE menu_list_window :
      virtual public ::user::menu
   {
   public:

      bool                                m_bAutoClose;
      bool                                m_bAutoDelete;


      menu_list_window();
      menu_list_window(::menu::item * pitem);
      ~menu_list_window() override;


      //void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      
      void _001OnTimer(::timer * ptimer) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void calc_size(::menu::item * pitemParent, ::draw2d::graphics_pointer & pgraphics, int & iMaxWidth, int & iMaxHeight);

      virtual void layout_buttons(::menu::item * pitemParent, int iMaxWidth, ::int_rectangle * prectangle, const ::int_rectangle & lpcrectBound);

      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace user







