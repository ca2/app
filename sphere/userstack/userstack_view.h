#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE view :
      virtual public ::user::show < ::user::interaction >
   {
   public:


      
      typedef ::user::show < ::user::interaction > BASE;

      __pointer(pane_view)    m_ppaneview;

      i32 m_iV;
      i32 m_iVH;
      i32 m_iVW;
      ::image_pointer m_pimageV;
      i32 m_i_veriwell;
      i32 m_i_veriwell_h;
      i32 m_i_veriwell_w;
      ::image_pointer m_pimage_veriwell;
      i32 m_i_winactionarea;
      i32 m_i_winactionarea_h;
      i32 m_i_winactionarea_w;
      ::image_pointer m_pimage_winactionarea;


      ::image_pointer m_pimageBk;

      oswindow                   m_oswindowWinactionarea;
      oswindow                   m_oswindowCommand;
      oswindow                   m_oswindowWinutil;
      oswindow                   m_oswindowWinservice1;
      oswindow                   m_oswindowBergedge;


      ::draw2d::font_pointer          m_font;
      ::file::listing            m_straImagePath;
      string                     m_strCurrentImagePath;
      bool                       m_bDestroy;
      rect_array                 m_rectaUpdate;
      millis                       m_millisLastUpdate;
      ::mutex                      m_mutexDraw;


      view(::layered * pobjectContext);
      virtual ~view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::create_struct& cs) override;
      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void on_apply(::action * paction) override;

      ::user::document * get_document();

      void GetAreaThumbRect(LPRECT32 lprect, i32 iArea);

      void on_hit_test(::user::item & item) override;

      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      void _001OnTimer(::timer * ptimer) override;
      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual void _001OnTabClick(i32 iTab);

      void check_apps();

      void mt_show_window(oswindow oswindow, i32 iShow);

      static ::u32 c_cdecl ThreadProcShowWindow(LPVOID lpparam);

      void _000OnMouse(::message::mouse * pmouse) override;

   };


} // namespace userstack


