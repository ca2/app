#pragma once


#include "aura/graphics/draw2d/host.h"
#include "acme/user/user/container.h"
#include "acme/user/user/item.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


namespace user
{


   class CLASS_DECL_AURA drawable :
      virtual public ::draw2d::host,
      virtual public ::user::acme_container
   {
   public:


      drawable();
      ~drawable() override;


      void destroy() override;


      virtual void _000DrawImpl(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool _000OnBeforeDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);
      virtual ::graphics::graphics * get_window_graphics();

      
      //virtual oswindow _oswindow() const;

      virtual ::acme::windowing::window * acme_windowing_window();


      virtual bool is_composite();

      //virtual ::item_pointer hit_test(::user::mouse * pmouse, e_zorder ezorder);

      virtual ::item_pointer parent_client_hit_test(const ::int_point & point, e_zorder ezorder);

      virtual ::item_pointer parent_client_on_hit_test(const ::int_point & point, e_zorder ezorder);


   };


   //class CLASS_DECL_AURA draw_interface :
   //   virtual public drawable
   //{
   //public:




   //   draw_interface();
   //   virtual ~draw_interface();




   //   //virtual bool _get_client_rect(::int_rectangle * prectangle) = 0;
   //   //virtual bool _get_window_rect(::int_rectangle * prectangle) = 0;
   //   
   //   //virtual ::int_point _client_parent_top_left() = 0;
   //   //virtual ::int_point _client_screen_top_left() = 0;


   //   //mutable int_size      m_sizeClient;
   //   //mutable int_size      m_sizeScreen;

   //   //mutable int_point     m_pointClient;
   //   //mutable int_point     m_pointScreen;
   //   //mutable int_point     m_pointParentWindow;
   //   //mutable int_point     m_pointParentClient;

   //   //inline auto get_client_rect64() { ::long_long_rectangle rectangle; this->rectangle(rectangle); return rectangle; }
   //   //inline auto get_window_rect64() { ::long_long_rectangle rectangle; window_rectangle(rectangle); return rectangle; }


   //};


} // namespace user


