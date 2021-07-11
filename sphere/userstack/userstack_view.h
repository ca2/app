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


      ::write_text::font_pointer          m_font;
      ::file::listing            m_straImagePath;
      string                     m_strCurrentImagePath;
      bool                       m_bDestroy;
      rectangle_i32_array                 m_rectaUpdate;
      millis                       m_millisLastUpdate;
      ::mutex                      m_mutexDraw;


      view(::object * pobject);
      virtual ~view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      ::user::document * get_document();

      void GetAreaThumbRect(RECTANGLE_I32 * lprect, i32 iArea);

      void on_hit_test(::user::item & item) override;

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      virtual void _001OnTabClick(i32 iTab);

      void check_apps();

      void mt_show_window(oswindow oswindow, i32 iShow);

      static ::u32 c_cdecl ThreadProcShowWindow(LPVOID lpparam);

      void _000OnMouse(::message::mouse * pmouse) override;

   };


} // namespace userstack


