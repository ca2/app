#pragma once


#include "aura/user/user/still.h"


class image_list;


class CLASS_DECL_CORE simple_still : 
   public ::user::still
{
public:
   
   
   bool                          m_bTransparent;
   ::draw2d::brush_pointer       m_pbrushBkg;
   __pointer(::image_list)       m_pimagelist;
   

   simple_still();
   ~simple_still() override;


   void pre_subclass_window() override;
   
   void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   //virtual ~simple_still();

   //LRESULT OnSetIcon(wparam wparam, lparam lparam);

};

