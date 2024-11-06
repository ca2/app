#pragma once



namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD application :
      virtual public ::hellobase::application,
      virtual public ::aura::application
   {
   public:


      enum enum_type
      {

         type_normal,
         type_mili,

      };

      enum_type                                 m_etype;
      string                                 m_strHelloWorld;
      string                                 m_strHelloWorldDefault;
      string                                 m_strAlternateHelloWorld;
      string                                 m_strAlternateHelloWorldDefault;

      bool                                   m_bWorldChat;

      ::user::document *                     m_pdocMenu;
//      ::calculator::plain_edit_impact *        m_prollfps;
      ::user::plain_edit_impact *              m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloWorldMain;
      ::user::single_document_template *     m_ptemplateHelloWorldImpact;
      ::user::single_document_template *     m_ptemplateHelloWorldSwitcher;


      //::user::split_impact *                             m_ptopviewLast;
      //impact *                                 m_pimpactLast;

      //::user::split_impact *                             m_ptopviewMain;
      //impact *                                 m_pviewMain;
      //::user::button_impact *                          m_ptoggleimpactMain;
      //::user::plain_edit_impact *              m_peditMain;

      //::user::split_impact *                             m_ptopviewSwitcher;
      //impact *                                 m_pviewSwitcher;
      //::user::button_impact *                          m_ptoggleimpactSwitcher;
      //::user::plain_edit_impact *              m_peditSwitcher;

      //::user::split_impact *                             m_ptopviewFont;
      //::user::font_list_impact *               m_pfontlistview;
      //::user::button_impact *                          m_ptoggleimpactFontSel;
      //::user::plain_edit_impact *              m_peditFontSel;

      ::pointer < ::mutex >                                  m_pmutexAiFont;
      int                                m_iErrorAiFont;
      bool                                   m_bLoadAiFont;
      void *                                 m_faceAi; // FT_Face m_faceAi;

      application(::particle * pparticle);
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      virtual string preferred_experience() override;
      virtual void init_instance() override;
      virtual int  exit_application() override;

      virtual void on_request(::request * prequest) override;

      virtual i64 increment_reference_count() override;
      virtual i64 decrement_reference_count() override;

   };


} // namespace helloworld



