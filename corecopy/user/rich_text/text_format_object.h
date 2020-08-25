#pragma once


namespace user
{


   class CLASS_DECL_CORE text_format_object :
      virtual public object
   {
   public:


      string            m_str = "Night1";

      ::rect          m_rect;


      text_format_object();
      virtual ~text_format_object();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user