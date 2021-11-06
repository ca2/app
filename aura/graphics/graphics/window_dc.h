#pragma once


namespace graphics
{



   class CLASS_DECL_AURA device_context :
      virtual public graphics
   {
   public:


      ::draw2d::graphics_pointer         m_spgraphics;


      window_dc();
      virtual ~window_dc();


      virtual bool update_window();


      ::draw2d::graphics * on_begin_draw();


   };


} // namespace graphics



