#pragma once



namespace helloaura
{


   class CLASS_DECL_APP_CORE_HELLOAURA application :
      virtual public ::aura::application
   {
   public:


      enum e_type
      {

         type_normal,
         type_mili,

      };

      double                                 m_dFps;
      e_type                                 m_etype;
      string                                 m_strHelloAura;
      string                                 m_strHelloAuraDefault;
      string                                 m_strAlternateHelloAura;
      string                                 m_strAlternateHelloAuraDefault;

      //bool                                   m_bAuraChat;

      //::user::document *                     m_pdocMenu;

      //::mutex                                  m_mutexAiFont;
      //i32                                m_iErrorAiFont;
      //bool                                   m_bLoadAiFont;
      //void *                                 m_faceAi; // FT_Face m_faceAi;
      render *                               m_prender;

      application(::object * pobject);
      virtual ~application();

      virtual ::estatus init_instance() override;
      virtual i32  exit_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;

      virtual string get_helloaura();

   };


   CLASS_DECL_AURA int main_window(::helloaura::render * prender);


} // namespace helloaura



