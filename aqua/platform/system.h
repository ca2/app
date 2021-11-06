#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA system :
      virtual public ::apex::system
   {
   public:


      __composite(::aqua::audio)                         m_paudio;

      __composite(::aqua::multimedia)                    m_pmultimedia;

      __composite(::aqua::estamira)                      m_pestamira;


      system();
      ~system() override;


      void aqua_construct();


      void common_construct();


      virtual ::e_status initialize(::object * pobject) override;


      virtual void on_add_session(::apex::session* papexsession) override;

      //virtual ::e_status initialize_rich_text();

      ::xml::xml* _xml() override;


      virtual ::e_status create_audio();

      virtual ::e_status defer_audio() override;

      virtual ::e_status defer_multimedia();

      virtual ::aqua::multimedia* defer_get_multimedia();


      inline ::aqua::audio * audio() { return m_paudio; }

      inline bool has_audio() const { return ::is_set(m_paudio); }

      inline ::aqua::multimedia * multimedia() { return m_pmultimedia; }


   };


} // namespace aqua




