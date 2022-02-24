#pragma once



namespace app_core_build
{


   class CLASS_DECL_APP_CORE_BUILD application :
      virtual public ::core::application
   {
   public:


      enum enum_type
      {

         type_normal,
         type_mili,

      };


      enum_type                              m_etype;
      string                                 m_strHelloMultiverse;
      string                                 m_strHelloMultiverseDefault;
      string                                 m_strAlternateHelloMultiverse;
      string                                 m_strAlternateHelloMultiverseDefault;

      bool                                   m_bMultiverseChat;

      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_view *              m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseView;
      pane_view *                            m_ppaneview;


      ::file::path_array                          m_pathaCommandLineSlide;


      application();
      ~application() override;


      void set_finish() override;


      virtual string preferred_experience() override;
      virtual void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;



   };


} // namespace app_core_build



