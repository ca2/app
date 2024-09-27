#pragma once


#include "aura/graphics/draw2d/host.h"
#include "acme/user/user/item.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


namespace user
{


   class CLASS_DECL_AURA drawable:
      virtual public ::draw2d::host
   {
   public:


      drawable();
      ~drawable() override;


      virtual void _000DrawImpl(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool _000OnBeforeDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);
      virtual ::graphics::graphics * get_window_graphics();

      
      virtual oswindow _oswindow() const;


      virtual bool is_composite();

      //virtual ::item_pointer hit_test(::user::mouse * pmouse, e_zorder ezorder);

      virtual ::item_pointer parent_client_hit_test(const ::point_i32 & point, e_zorder ezorder);

      virtual ::item_pointer parent_client_on_hit_test(const ::point_i32 & point, e_zorder ezorder);


   };


   //class CLASS_DECL_AURA draw_interface :
   //   virtual public drawable
   //{
   //public:




   //   draw_interface();
   //   virtual ~draw_interface();




   //   //virtual bool _get_client_rect(::rectangle_i32 * prectangle) = 0;
   //   //virtual bool _get_window_rect(::rectangle_i32 * prectangle) = 0;
   //   
   //   //virtual ::point_i32 _client_parent_top_left() = 0;
   //   //virtual ::point_i32 _client_screen_top_left() = 0;


   //   //mutable size_i32      m_sizeClient;
   //   //mutable size_i32      m_sizeScreen;

   //   //mutable point_i32     m_pointClient;
   //   //mutable point_i32     m_pointScreen;
   //   //mutable point_i32     m_pointParentWindow;
   //   //mutable point_i32     m_pointParentClient;

   //   //inline auto get_client_rect64() { ::rectangle_i64 rectangle; this->rectangle(rectangle); return rectangle; }
   //   //inline auto get_window_rect64() { ::rectangle_i64 rectangle; window_rectangle(rectangle); return rectangle; }


   //};


} // namespace user


