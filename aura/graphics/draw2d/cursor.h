#pragma once


namespace draw2d
{
   
   
   class CLASS_DECL_AURA cursor :
      virtual public ::matter
   {
   public:


      e_cursor                m_ecursor;
      bool                    m_bDefaultCursor;
      ::image_pointer         m_pimage;
      ::image_pointer         m_pimageCursor;
      size                    m_szHotspotOffset;


      HCURSOR                 m_hcursor;


      cursor();
      virtual ~cursor();


      //bool to(::draw2d::graphics_pointer & pgraphics, const ::point & point);

      bool initialize_system_default();

      virtual void finalize() override;

      HCURSOR get_HCURSOR(::user::interaction * pinteraction);

      bool set_current(::user::interaction * pinteraction, ::aura::session * psession);

      static bool reset(::user::interaction * pinteraction, ::aura::session * psession);

      inline ::draw2d::graphics * g() const { return m_pimage->g(); }
      inline ::draw2d::graphics * g(const ::sized & sizeHint) { return m_pimage->g(sizeHint); }
      inline ::sized size(const ::sized & sizeHint) { return m_pimage->size(sizeHint); }
      inline ::sized origin() const { return m_szHotspotOffset; }


   };


   typedef __pointer(cursor) cursor_pointer;


   CLASS_DECL_AURA void cursor_alloc(::object * pobject, cursor_pointer & image,int xHotspot,int yHotspot);
   CLASS_DECL_AURA image_pointer cursor_get_image(cursor * pcursor);


} // namespace draw2d


#ifdef WINDOWS_DESKTOP


// Derived from Microsoft KB318876!!
// on 2014-06-29!! During World Cup Games 2014!! Oitavas de Final, third game between Nederland and Mexico!!
// Thank you God!!
// Thank you Microsoft!!
// Thank you Pappi!! Pelo passeio no Mercado Municipal de Curitiba com a Mummi e pelo almoo com o-bento de sushi e onigiri delicioso!!
// Obrigado Mummi por tudo!! E por hoje tambm e por propiciar isso tudo!! Por falar to profundamente do Chico Xavier mesmo com muitas dvidas minhas!!
// Meu Deus me ajude!!


CLASS_DECL_AURA HBITMAP CreateAlphaBitmapV5(const ::image * pimage);
CLASS_DECL_AURA HICON CreateAlphaIcon(const ::image * pimage,bool bIcon = true,int xHotSpot = 0,int yHotSpot = 0);


#endif


//CLASS_DECL_AURA HCURSOR CreateAlphaCursor(oswindow oswindow, const ::image * pimage,int xHotSpot,int yHotSpot);



