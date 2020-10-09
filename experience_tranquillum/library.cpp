#include "framework.h"
#include "aura/application.h"


namespace experience
{


   namespace tranquillum

   {


      library::library()
      {
      }


      library::~library()
      {

      }


      ::element * library::new_object(::layered * pobjectContext,const char * lpszClass)
      {

         if(string(lpszClass) == "experience")
         {

            return new experience;

         }
         else if(string(lpszClass) == "control_box")
         {

            return new control_box;

         }
         else if(string(lpszClass) == "button")
         {

            return new button;

         }
         else if(string(lpszClass) == "user_theme")
         {

            return new style;

         }
         else
         {

            return nullptr;

         }

      }


      __namespace_library_factory("experience_tranquillum");


   } // namespace tranquillum


} // namespace experience



