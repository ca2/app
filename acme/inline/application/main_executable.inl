// From main.inl to main_executable.inl by
// camilo on 2025-07-31 14:17 <3ThomasBorregaardSørensen!!
#define CLASS_DECL_APPLICATION_NAMESPACE CLASS_DECL_IMPORT
#include "acme/inline/application/main.h"


#ifdef CUBE
#include "acme/platform/factory_function.h"
#include "operating_system/appconfig.h"
#include "_static_factory_.inl"
#endif




#ifdef CUBE

DO_FACTORY(DECLARE_FACTORY)



#include "acme/platform/_main_hold_base.h"


class main_hold :
   virtual public main_hold_base
{
public:

//#ifdef SYSTEM_NAMESPACE
//   ::static_object_factory < ::SYSTEM_NAMESPACE::system > m_factorySystem{ ::system_setup::flag_system };
//#else
//   ::static_object_factory < ::platform::system > m_factorySystem{ ::system_setup::flag_system };
//#endif


//#ifdef APPLICATION
//   ::static_application_factory < ::APPLICATION::application > m_factoryApplication{ __APP_ID };
//#endif
//#if defined(CUBE) && defined(HAS_AUDIO) && HAS_AUDIO
//   ::system_setup m_factoryAudio{ &::audio_factory, "audio" };
//#endif
//#if defined(CUBE) && defined(USES_ESTAMIRA) && USES_ESTAMIRA
//   ::system_setup m_factoryEstamira{ &::estamira_factory, "estamira" };
//#endif
//#ifdef CLASS_DECL_VERIWELL_MULTIMEDIA
//   ::static_object_factory < ::veriwell::multimedia::multimedia > m_systemsetupMultimedia{::system_setup::flag_multimedia, "veriwell_multimedia"
//};
//#elif defined(CLASS_DECL_MULTIMEDIA)
//   ::static_object_factory < ::multimedia::multimedia > m_systemsetupMultimedia{ ::system_setup::flag_multimedia, "multimedia" };
//#endif
//#ifdef CLASS_DECL_CORE
//   ::static_object_factory < ::core::user > m_factoryUser{::system_setup::flag_object_user};
//#elif defined(CLASS_DECL_BERG)
//   ::static_object_factory < ::berg::user > m_factoryUser{ ::system_setup::flag_object_user };
//#elif defined(CLASS_DECL_AXIS)
//   ::static_object_factory < ::axis::user > m_factoryUser{ ::system_setup::flag_object_user };
//#elif defined(CLASS_DECL_AURA)
//   ::static_object_factory < ::user::user > m_factoryUser{ ::system_setup::flag_object_user };
//#endif

#ifdef CUBE

   DO_FACTORY(SETUP_FACTORY)

#endif

      main_hold()
   {


////#ifdef SYSTEM_NAMESPACE
////         //::static_object_factory < ::SYSTEM_NAMESPACE::system > m_factorySystem{ ::system_setup::flag_system };
////      factory()->add_factory_item< ::SYSTEM_NAMESPACE::system, ::platform::system >();
////#else
////      factory()->add_factory_item< ::platform::system >();
////#endif
////
////#if defined(HAS_AUDIO)
////      enable_audio(HAS_AUDIO);
////#endif

   }


};





#endif



#ifdef CUBE
DO_FACTORY(REFERENCE_FACTORY)
#endif


#ifdef WINDOWS

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#endif


#if defined(WINDOWS)
int WINAPI wWinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, WCHAR* pCmdLine, int nCmdShow)
#else
extern "C" int main(int argc, char* argv[], char* envp[])
#endif
{

   APPLICATION_NAMESPACE_MAIN(create_system)();

#if defined(WINDOWS)
   APPLICATION_NAMESPACE_MAIN(initialize_system)(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);
#elif defined(__ANDROID__)
   const char * p1 = nullptr; //_todo_begin;
   const char * p2 = nullptr; //_todo_end;
   APPLICATION_NAMESPACE_MAIN(initialize_system)(argc, argv, envp, p1, p2);
#else
   APPLICATION_NAMESPACE_MAIN(initialize_system)(argc, argv, envp);
#endif

   auto iExitCode = APPLICATION_NAMESPACE_MAIN(main)();

   return iExitCode;

}



