
#ifdef CUBE

DO_FACTORY_EXCHANGE(DECLARE_FACTORY_EXCHANGE)

#endif


struct main_hold
{

#ifdef SYSTEM_NAMESPACE
   ::static_object_factory < ::SYSTEM_NAMESPACE::system > m_factorySystem{ ::static_setup::flag_system };
#else
   ::static_object_factory < class ::system > m_factorySystem{ ::static_setup::flag_system };
#endif
#ifdef APPLICATION
   ::static_application_factory < ::APPLICATION::application > m_factoryApplication{ __APP_ID };
#endif
#ifdef CLASS_DECL_CORE
   ::static_object_factory < ::core::user > m_factoryUser{::static_setup::flag_object_user};
#elif defined(CLASS_DECL_BASE)
   ::static_object_factory < ::base::user > m_factoryUser{ ::static_setup::flag_object_user };
#elif defined(CLASS_DECL_AXIS)
   ::static_object_factory < ::axis::user > m_factoryUser{ ::static_setup::flag_object_user };
#elif defined(CLASS_DECL_AURA)
   ::static_object_factory < ::user::user > m_factoryUser{ ::static_setup::flag_object_user };
#endif

#ifdef CUBE

   DO_FACTORY_EXCHANGE(SETUP_FACTORY_EXCHANGE)

#endif

};


static main_hold g_mainhold;
