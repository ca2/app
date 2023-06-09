// From design/text_format/user_text_format_object.h by camilo on
// 2022-09-04 00:13 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
#include "axis/user/user/object.h"


namespace user
{


   class CLASS_DECL_CORE text_format_object :
      virtual public ::user::object
   {
   public:


      string               m_str;

      ::rectangle_i32      m_rectangle;


      text_format_object();
      ~text_format_object() override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user
