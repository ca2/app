#pragma once


#include "apex/platform/system.h"


namespace aqua
{


   class CLASS_DECL_AQUA system :
      virtual public ::apex::system
   {
   public:


      ::pointer<::aqua::audio>                        m_paudio;

      ::pointer<::aqua::multimedia>                   m_pmultimedia;

      ::pointer<::aqua::estamira>                     m_pestamira;


      system();
      ~system() override;


      void aqua_construct();


      void common_construct();


      virtual void initialize(::particle * pparticle) override;


      virtual void on_add_session(::acme::session* papexsession) override;

      //virtual void initialize_rich_text();

      ::xml::xml* _xml() override;


      virtual void create_audio();

      void defer_audio() override;

      virtual void defer_multimedia();

      bool has_audio() override;

      virtual ::aqua::multimedia* defer_get_multimedia();


      inline ::aqua::audio * audio() { return m_paudio; }

      inline bool has_audio() const { return ::is_set(m_paudio); }

      inline ::aqua::multimedia * multimedia() { return m_pmultimedia; }


   };


} // namespace aqua




