#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_list_window :
      virtual public ::user::menu
   {
   public:

      bool                                m_bAutoClose;
      bool                                m_bAutoDelete;


      menu_list_window();
      menu_list_window(menu_item * pitem);
      virtual ~menu_list_window();


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void install_message_routing(::channel * pchannel) override;

      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnClose);
      
      void _001OnTimer(::timer * ptimer) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void calc_size(menu_item * pitemParent, ::draw2d::graphics_pointer & pgraphics, i32 & iMaxWidth, i32 & iMaxHeight);

      virtual void layout_buttons(menu_item * pitemParent, i32 iMaxWidth, RECTANGLE_I32 * prectangle, const ::rectangle_i32 & lpcrectBound);



   };


} // namespace user







