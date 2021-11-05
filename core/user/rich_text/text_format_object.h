#pragma once


namespace user
{


   class CLASS_DECL_CORE text_format_object :
      virtual public object
   {
   public:


      string            m_str = "Night1";

      ::rectangle_i32          m_rectangle;


      text_format_object();
      virtual ~text_format_object();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user
