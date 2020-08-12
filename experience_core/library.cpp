#include "framework.h"
#include "aura/platform/static_setup.h"


namespace experience
{

   namespace aura
   {

      library::library()
      {

      }


      library::~library()
      {

      }


      ::generic_object * library::new_object(::object * pobject, const char * pszClass)
      {

         if(string(pszClass) == "experience")
         {

            return new experience;

         }
         else if(string(pszClass) == "control_box")
         {

            return new control_box;

         }
         else if(string(pszClass) == "button")
         {

            return new button;

         }
         else if(string(pszClass) == "user_theme")
         {

            return new theme;

         }
         else
         {

            return nullptr;

         }

      }

   
      __namespace_library_factory("experience_core");
      __namespace_library_factory("experience_aura");
   

   } // namespace aura


} // namespace experience


//#ifdef CUBE
//extern "C" ::aura::library * experience_get_new_library()
//#else
//extern "C" ::aura::library * experience_core_get_new_library()
//#endif
//{
//
//   return new ::experience::aura::library;
//
//}

//
//__namespace_library_factory2(experience, aura, "experience_core");
//
//
//
