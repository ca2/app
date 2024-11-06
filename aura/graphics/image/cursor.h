#pragma once


#include "aura/graphics/image/source.h"


using hcursor = void *;


namespace image
{
   
   
   class CLASS_DECL_AURA cursor :
      virtual public ::image::image_source_interface
   {
   public:


      enum_cursor                         m_ecursor;
      bool                                m_bDefaultCursor;
      ::image::image_pointer                     m_pimage;
      ::image::image_pointer                     m_pimageCursor;
      ::int_size                          m_szHotspotOffset;


      ::pointer<::windowing::cursor>     m_pcursor;


      cursor();
      ~cursor() override;


      //virtual bool initialize_system_default();

      
      


      virtual void destroy() override;

      //::windowing::cursor * get_cursor(::user::interaction * pinteraction);

      virtual ::windowing::cursor * get_cursor();

      //bool set_current(::user::interaction * pinteraction, ::aura::session * psession);

      //static bool reset(::user::interaction * pinteraction, ::aura::session * psession);

      ::draw2d::graphics * g() const;
      ::draw2d::graphics * g(const ::double_size & sizeHint);

      
      ::image::image_pointer image_source_image(const ::int_size & size) override;

      ::int_size image_source_size(const ::double_size & sizeDst, enum_image_selection eimageselection) const override;

      ::int_size image_source_size() const override;


   };


   typedef ::pointer<cursor>cursor_pointer;


   CLASS_DECL_AURA void cursor_alloc(::particle * pparticle, cursor_pointer & image,int xHotspot,int yHotspot);
   CLASS_DECL_AURA ::image::image_pointer cursor_get_image(cursor * pcursor);


} // namespace image



//CLASS_DECL_AURA hcursor CreateAlphaCursor(::windowing::window * pwindow, const ::image::image *pimage,int xHotSpot,int yHotSpot);



