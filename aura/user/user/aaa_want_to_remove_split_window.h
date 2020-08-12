#pragma once

class CLASS_DECL_AURA BaseSplitWnd :
   virtual public ::user::split_layout
{
public:
   BaseSplitWnd(::object * pobject);

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   virtual bool pre_create_window(::user::create_struct& cs);

   virtual ~BaseSplitWnd();

};

