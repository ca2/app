#include "framework.h"

int my_main(::particle * pparticle);

namespace helloaxis
{


   application::application(::particle * pparticle) :
      ::object(this),
      ::thread(this),
      ::aura::application(pparticle),
      ::axis::application(pparticle),
      ::berg::application(pparticle),
      ::aura::application(pparticle),
      ::sphere::application(pparticle) :
      m_pmutexAiFont(this)
   {

      m_strAppName = "app/helloaxis";
      m_strLibraryName = "app/helloaxis";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloAxisDefault = "Hello Axis!!";
      m_strAlternateHelloAxisDefault = "Hello!!";

      m_strHelloAxis = m_strHelloAxisDefault;
      m_strAlternateHelloAxis = m_strAlternateHelloAxisDefault;

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_faceAi = nullptr; // FT_Face m_faceAi;

      m_bAxisChat = true;



   }


   application::~application()
   {
   }


   void application::init_instance()
   {

      ::aura::session * pcoression = get_app()->m_psession;

      if (!::axis::application::init_instance())
      {

         return false;

      }

      string str = m_varTopicQuery["helloaxis"];

      if (str.has_character())
      {

         m_strHelloAxis = str;

      }

      set_local_data_key_modifier();



      return true;

   }


   int application::exit_application()
   {

      return ::axis::application::exit_application();

   }


   void application::on_request(::request * prequest)
   {

#if 0

#ifdef _DEBUG

      informationf("_DEBUG build? (basis)");

      ASSERT(false);

#else

      informationf("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bAxisChat = !m_varTopicQuery["no_hello_edit"].is_set();

      informationf("----> finished helloaxis::on_request");

      fork([&]()
      {
         my_main(this);
      }
          );

   }





   long long application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }

   long long application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }

   void application::paint(HWND hwnd, HDC hdc)
   {
      ::draw2d::graphics_pointer g(e_create);

      g->Attach(hdc);

      paint(hwnd, g);

   }

   void application::paint(HWND hwnd, ::draw2d::graphics_pointer & pgraphics)
   {
      ::int_rectangle rcClient;
      ::this->rectangle(hwnd, rcClient);
      auto pbrush = øcreate < ::draw2d::brush > ();

      pbrush->create_solid(argb(255, 255, 0, 0));
      pgraphics->SelectObject(br);
      pgraphics->FillEllipse(rcClient);
   }

} // namespace helloaxis




extern "C"
::acme::library * app_helloaxis_get_new_library(::particle * pparticle)
{

   return ___new ::apex::single_application_library < ::helloaxis::application >  (pparticle, "app/helloaxis");

}




