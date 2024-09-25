// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
#pragma once


////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/geometry2d/point.h"
//#include "acme/primitive/geometry2d/size.h"
#include "acme/primitive/geometry2d/rectangle.h"

namespace nano
{

   namespace user
   {
   


class child :
   virtual public ::object
{
public:


   string                  m_strText;
   ::atom                  m_atom;
   rectangle_i32           m_rectangle;
   ::nano::user::window *           m_pnanowindow;


   virtual void on_draw(::nano::user::device * pnanodevice) = 0;
   virtual void on_char(int iChar) = 0;
   virtual void set_focus();
   virtual bool is_focusable() const;
   virtual void on_mouse_move(::user::mouse * pmouse);
   virtual void set_capture();
   virtual bool has_capture() const;
   virtual void release_capture();


   virtual void resize_to_fit();


   //virtual void display_temporary_file_with_text(const ::string & str);


};






   } // namespace user


} // namespace nano



