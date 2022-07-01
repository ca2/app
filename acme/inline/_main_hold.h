

#ifdef CUBE

DO_FACTORY(DECLARE_FACTORY)

#endif


#include "acme/platform/_main_hold_base.h"


struct main_hold :
   public main_hold_base
{


#ifdef SYSTEM_NAMESPACE
   ::static_object_factory < ::SYSTEM_NAMESPACE::system > m_factorySystem{ ::system_setup::flag_system };
#else
   ::static_object_factory < class ::system > m_factorySystem{ ::system_setup::flag_system };
#endif
#ifdef APPLICATION
   ::static_application_factory < ::APPLICATION::application > m_factoryApplication{ __APP_ID };
#endif
#if defined(CUBE) && defined(HAS_AUDIO) && HAS_AUDIO
   ::system_setup m_factoryAudio{ &::audio_factory, "audio" };
#endif
#if defined(CUBE) && defined(USES_ESTAMIRA) && USES_ESTAMIRA
   ::system_setup m_factoryEstamira{ &::estamira_factory, "estamira" };
#endif
#ifdef CLASS_DECL_VERIWELL_MULTIMEDIA
   ::static_object_factory < ::veriwell::multimedia::multimedia > m_systemsetupMultimedia{::system_setup::flag_multimedia, "veriwell_multimedia"
};
#elif defined(CLASS_DECL_MULTIMEDIA)
   ::static_object_factory < ::multimedia::multimedia > m_systemsetupMultimedia{ ::system_setup::flag_multimedia, "multimedia" };
#endif
#ifdef CLASS_DECL_CORE
   ::static_object_factory < ::core::user > m_factoryUser{::system_setup::flag_object_user};
#elif defined(CLASS_DECL_BASE)
   ::static_object_factory < ::base::user > m_factoryUser{ ::system_setup::flag_object_user };
#elif defined(CLASS_DECL_AXIS)
   ::static_object_factory < ::axis::user > m_factoryUser{ ::system_setup::flag_object_user };
#elif defined(CLASS_DECL_AURA)
   ::static_object_factory < ::user::user > m_factoryUser{ ::system_setup::flag_object_user };
#endif

#ifdef CUBE

   DO_FACTORY(SETUP_FACTORY)

#endif

      main_hold()
   {

#if defined(HAS_AUDIO)
      enable_audio(HAS_AUDIO);
#endif

   }


};


static main_hold g_mainhold;
