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



      pane_view(::object * pobject);
      virtual ~pane_view();

      using ::user::tab_view::on_change_cur_sel;
      using ::userstack::form_callback::update;

      void rotate() override;

      void on_create_impact(::user::impact_data * pimpactdata) override;
      void on_change_cur_sel() override;

      void install_message_routing(::channel * pchannel) override;

      void check_3click_dir(const ::file::path & psz);
      void check_menu_dir(const ::file::path & psz);
      void check_desktop_dir(const ::file::path & psz);

      void _001InitializeFormPreData(::user::form * pform) override;
      void handle(::topic * ptopic, ::context * pcontext) override;

      /*   virtual void OnFileManagerOpenContextMenuFolder(
            ::filemanager::data * pdata,
            ::file::item & item);*/
      virtual void OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::file::item_array & itema);
      virtual void OnFileManagerOpenContextMenu(::filemanager::data * pdata);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void set_display(i32 iDisplay);

      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(_001OnMenuMessage);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      DECLARE_MESSAGE_HANDLER(_001OnProperties);

   };


} // namespace userstack

