#pragma once


class image_list;


class CLASS_DECL_CORE simple_static : 
   public ::user::static_control
{
public:
   
   
   bool                          m_bTransparent;
   ::draw2d::brush_pointer       m_brushBkg;
   __pointer(::image_list)       m_pimagelist;
   

   simple_static();

   virtual void pre_subclass_window();
   
   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
   virtual ~simple_static();

   //LRESULT OnSetIcon(WPARAM wparam, LPARAM lparam);

};

