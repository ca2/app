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
//      ::calculator::plain_edit_view *        m_prollfps;
      ::user::plain_edit_view *              m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloWorldMain;
      ::user::single_document_template *     m_ptemplateHelloWorldView;
      ::user::single_document_template *     m_ptemplateHelloWorldSwitcher;


      //::user::split_view *                             m_ptopviewLast;
      //impact *                                 m_pviewLast;

      //::user::split_view *                             m_ptopviewMain;
      //impact *                                 m_pviewMain;
      //::user::button_view *                          m_ptoggleviewMain;
      //::user::plain_edit_view *              m_peditMain;

      //::user::split_view *                             m_ptopviewSwitcher;
      //impact *                                 m_pviewSwitcher;
      //::user::button_view *                          m_ptoggleviewSwitcher;
      //::user::plain_edit_view *              m_peditSwitcher;

      //::user::split_view *                             m_ptopviewFont;
      //::user::font_list_view *               m_pfontlistview;
      //::user::button_view *                          m_ptoggleviewFontSel;
      //::user::plain_edit_view *              m_peditFontSel;

      ::mutex                                  m_mutexAiFont;
      i32                                m_iErrorAiFont;
      bool                                   m_bLoadAiFont;
      void *                                 m_faceAi; // FT_Face m_faceAi;

      application(::object * pobject);
      virtual ~application();

      virtual string preferred_experience() override;
      virtual ::e_status init_instance() override;
      virtual i32  exit_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

   };


} // namespace helloworld



