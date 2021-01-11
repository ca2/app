#include "framework.h"
#include "apex/platform/static_setup.h"


namespace experience
{


   namespace anthill
   {


      library::library() 
      {

      }


      library::~library()
      {

      }


      ::matter * library::new_object(const char * pszClass)
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

            return new style;

         }
         else
         {

            return nullptr;

         }

      }


      __namespace_library_factory("experience_anthill");


   } // namespace anthill


} // namespace experience



