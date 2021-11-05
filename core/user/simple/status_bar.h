#pragma once


class CLASS_DECL_CORE simple_status_bar :
   public ::user::status_bar
{
public:
   
   
   simple_status_bar();


   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
   virtual ~simple_status_bar();


};



