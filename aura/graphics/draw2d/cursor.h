#pragma once


using hcursor = void *;


namespace draw2d
{
   
   
   class CLASS_DECL_AURA cursor :
      virtual public ::matter
   {
   public:


      enum_cursor                         m_ecursor;
      bool                                m_bDefaultCursor;
      ::image_pointer                     m_pimage;
      ::image_pointer                     m_pimageCursor;
      ::size_i32                          m_szHotspotOffset;


      __pointer(::windowing::cursor)      m_pcursor;


      cursor();
      virtual ~cursor();


      //virtual bool initialize_system_default();

      
      


      virtual ::e_status finalize() override;

      //::windowing::cursor * get_cursor(::user::interaction * pinteraction);

      virtual ::windowing::cursor * get_cursor();

      //bool set_current(::user::interaction * pinteraction, ::aura::session * psession);

      //static bool reset(::user::interaction * pinteraction, ::aura::session * psession);

      inline ::draw2d::graphics * g() const { return m_pimage->g(); }
      inline ::draw2d::graphics * g(const ::size_f64 & sizeHint) { return m_pimage->g(sizeHint); }

      
      inline ::image * get_image(const concrete < ::size_i32 > & concreteSize) { return m_pimage->get_image(concreteSize); }


      inline concrete < ::size_i32 > size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const { return m_pimage->size(sizeDst, eimageselection); }
      inline concrete < ::size_i32 > size() const { return m_pimage->size(); }


   };


   typedef __pointer(cursor) cursor_pointer;


   CLASS_DECL_AURA void cursor_alloc(::object * pobject, cursor_pointer & image,int xHotspot,int yHotspot);
   CLASS_DECL_AURA image_pointer cursor_get_image(cursor * pcursor);


} // namespace draw2d



//CLASS_DECL_AURA hcursor CreateAlphaCursor(::windowing::window * pwindow, const ::image * pimage,int xHotSpot,int yHotSpot);



