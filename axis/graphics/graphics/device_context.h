#pragma once


namespace graphics
{


   class CLASS_DECL_AURA device_context :
      virtual public graphics
   {
   public:


      ::draw2d::graphics_pointer         m_spgraphics;


      device_context();
      virtual ~device_context();


      virtual bool update_window();


      ::draw2d::graphics * on_begin_draw();


   };


} // namespace graphics



