#pragma once


namespace user
{

   class item;

}

namespace apex
{

   class CLASS_DECL_APEX drawable:
      virtual public ::object
   {
   public:



      drawable();
      virtual ~drawable();

      virtual ::draw2d::graphics_pointer create_memory_graphics();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool _000OnBeforeDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);
      virtual ::graphics::graphics * get_window_graphics();
      virtual oswindow get_handle() const;

      virtual bool is_composite();

      virtual void hit_test(::user::item & item, const ::point & point);
      virtual void on_hit_test(::user::item & item);

      virtual void hit_test(::user::item & item, ::message::mouse * pmouse);

      virtual ::user::item hit_test(const ::point & point);

      virtual ::user::item hit_test(::message::mouse * pmouse);



   };

   //class CLASS_DECL_APEX draw_interface :
   //   virtual public drawable
   //{
   //public:




   //   draw_interface();
   //   virtual ~draw_interface();




   //   //virtual bool _get_client_rect(RECT * prect) = 0;
   //   //virtual bool _get_window_rect(RECT * prect) = 0;
   //   
   //   //virtual ::point _client_parent_top_left() = 0;
   //   //virtual ::point _client_screen_top_left() = 0;


   //   //mutable size      m_sizeClient;
   //   //mutable size      m_sizeScreen;

   //   //mutable point     m_pointClient;
   //   //mutable point     m_pointScreen;
   //   //mutable point     m_pointParentWindow;
   //   //mutable point     m_pointParentClient;

   //   //inline auto get_client_rect64() { ::rect64 rect; get_client_rect(rect); return rect; }
   //   //inline auto get_window_rect64() { ::rect64 rect; get_window_rect(rect); return rect; }


   //};


} // namespace apex


