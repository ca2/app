

DO_FACTORY_EXCHANGE(DECLARE_FACTORY_EXCHANGE)


struct main_hold
{

   ::static_object_factory < ::SYSTEM::system > m_factorySystem{ ::static_setup::flag_system };
   ::static_application_factory < ::APPLICATION::application > m_factoryApplication{ _APP_ID };
   ::static_object_factory < ::core::user > m_factoryUser{::static_setup::flag_object_user};

   DO_FACTORY_EXCHANGE(SETUP_FACTORY_EXCHANGE)


};
