#pragma once


#include "aura/graphics/image/source.h"


using hcursor = void *;


namespace draw2d
{
   
   
   class CLASS_DECL_AURA cursor :
      virtual public ::image_source_interface
   {
   public:


      enum_cursor                         m_ecursor;
      bool                                m_bDefaultCursor;
      ::image_pointer                     m_pimage;
      ::image_pointer                     m_pimageCursor;
      ::size_i32                          m_szHotspotOffset;


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
      ::draw2d::graphics * g(const ::size_f64 & sizeHint);

      
      ::image_pointer image_source_image(const concrete < ::size_i32 > & concreteSize) override;

      concrete < ::size_i32 > image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const override;

      concrete < ::size_i32 > image_source_size() const override;


   };


   typedef ::pointer<cursor>cursor_pointer;


   CLASS_DECL_AURA void cursor_alloc(::object * pobject, cursor_pointer & image,int xHotspot,int yHotspot);
   CLASS_DECL_AURA image_pointer cursor_get_image(cursor * pcursor);


} // namespace draw2d



//CLASS_DECL_AURA hcursor CreateAlphaCursor(::windowing::window * pwindow, const ::image * pimage,int xHotSpot,int yHotSpot);



