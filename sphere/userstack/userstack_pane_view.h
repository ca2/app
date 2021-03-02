#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE pane_view :
      public ::userex::pane_tab_view,
      public ::filemanager::callback,
      public ::userstack::form_callback
   {
   public:


      

      __pointer(::user::form)                          m_pformOptions;
      ::image_pointer                         m_pimageBk;
      i32                                m_iNewArea;
      i32                                m_iArea;
      i32                                m_iDisplay;
      filemanager::file_properties_form *    m_ppropform;
      ::file::item_array                       m_itema;



      pane_view(::layered * pobjectContext);
      virtual ~pane_view();

      using ::user::tab_view::on_change_cur_sel;
      using ::userstack::form_callback::update;

      void rotate() override;

      void on_create_impact(::user::impact_data * pimpactdata) override;
      void on_change_cur_sel() override;

      virtual void install_message_routing(::channel * pchannel) override;

      void check_3click_dir(const ::file::path & psz);
      void check_menu_dir(const ::file::path & psz);
      void check_desktop_dir(const ::file::path & psz);

      void _001InitializeFormPreData(::user::form * pform) override;
      void on_control_event(::user::control_event * pevent) override;

      /*   virtual void OnFileManagerOpenContextMenuFolder(
            ::filemanager::data * pdata,
            ::file::item & item);*/
      virtual void OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::file::item_array & itema);
      virtual void OnFileManagerOpenContextMenu(::filemanager::data * pdata);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void set_display(i32 iDisplay);

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      DECL_GEN_SIGNAL(_001OnMenuMessage);
      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnRButtonUp);
      DECL_GEN_SIGNAL(_001OnProperties);

   };


} // namespace userstack

