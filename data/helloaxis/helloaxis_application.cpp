﻿#include "framework.h"
int my_main(::object * pobject);

namespace helloaxis
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject) :
      m_mutexAiFont(this)
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


   ::e_status application::init_instance()
   {

      ::aura::session * pcoression = get_application()->m_psession;

      if (!::axis::application::init_instance())
      {

         return false;

      }

      string str = m_varTopicQuery["helloaxis"];

      if (str.has_char())
      {

         m_strHelloAxis = str;

      }

      set_local_data_key_modifier();



      return true;

   }


   i32 application::exit_application()
   {

      return ::axis::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bAxisChat = !m_varTopicQuery["no_hello_edit"].is_set();

      output_debug_string("\nfinished helloaxis::on_request");

      fork([&]()
      {
         my_main(this);
      }
          );

   }





   i64 application::increment_reference_count()
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 application::decrement_reference_count()
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   void application::paint(HWND hwnd, HDC hdc)
   {
      ::draw2d::graphics_pointer g(e_create);

      g->Attach(hdc);

      paint(hwnd, g);

   }

   void application::paint(HWND hwnd, ::draw2d::graphics_pointer & pgraphics)
   {
      ::rectangle_i32 rcClient;
      ::get_client_rect(hwnd, rcClient);
      auto pbrush = __create < ::draw2d::brush > ();

      pbrush->create_solid(argb(255, 255, 0, 0));
      pgraphics->SelectObject(br);
      pgraphics->FillEllipse(rcClient);
   }

} // namespace helloaxis




extern "C"
::acme::library * app_helloaxis_get_new_library(::object * pobject)
{

   return new ::apex::single_application_library < ::helloaxis::application > (pobject, "app/helloaxis");

}




