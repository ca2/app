#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE impact :
      virtual public ::user::show < ::user::interaction >
   {
   public:


      
      typedef ::user::show < ::user::interaction > BASE;

      ::pointer<pane_impact>   m_ppaneimpact;

      int m_iV;
      int m_iVH;
      int m_iVW;
      ::image::image_pointer m_pimageV;
      int m_i_veriwell;
      int m_i_veriwell_h;
      int m_i_veriwell_w;
      ::image::image_pointer m_pimage_veriwell;
      int m_i_winactionarea;
      int m_i_winactionarea_h;
      int m_i_winactionarea_w;
      ::image::image_pointer m_pimage_winactionarea;


      ::image::image_pointer m_pimageBk;

      oswindow                   m_oswindowWinactionarea;
      oswindow                   m_oswindowCommand;
      oswindow                   m_oswindowWinutil;
      oswindow                   m_oswindowWinservice1;
      oswindow                   m_oswindowBergedge;


      ::write_text::font_pointer          m_pfont;
      ::file::listing            m_straImagePath;
      string                     m_strCurrentImagePath;
      bool                       m_bDestroy;
      int_rectangle_array                 m_rectangleaUpdate;
      class ::time                       m_timeLastUpdate;
      ::pointer < ::mutex >                      m_pmutexDraw;


      impact(::particle * pparticle);
      virtual ~impact();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void pre_translate_message(::message::message * pmessage) override;

      void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      ::user::document * get_document();

      void GetAreaThumbRect(::int_rectangle * lprect, int iArea);

      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      //DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      void on_timer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      virtual void _001OnTabClick(int iTab);

      void check_apps();

      void mt_show_window(oswindow oswindow, int iShow);

      static unsigned int c_cdecl ThreadProcShowWindow(LPVOID lpparam);

      void _000OnMouse(::message::mouse * pmouse) override;

   };


} // namespace userstack


