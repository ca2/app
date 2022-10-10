#include "framework.h"





   namespace experience
   {


      namespace lite

      {


         library::library(::object * pobject):
            object(pobject),
            ::acme::library(pobject,0,"")
         {
         }


         library::~library()
         {
         }


         ::pointer<::object>library::alloc(::object * pobject, const ::string & pszClass, object * p)
         {

            if(string(pszClass) == "experience")
            {

               return memory_new experience(pobject);

            }
            else if(string(pszClass) == "control_box")
            {

               return memory_new control_box(pobject);

            }
            else if(string(pszClass) == "control_box_button")
            {

               return memory_new button(pobject);

            }
            else if(string(pszClass) == "user_theme")
            {

               return memory_new ::experience_lite::theme(pobject);

            }
            else
            {

               return nullptr;

            }

         }


      } // namespace lite



   } // namespace experience





#ifdef CUBE

extern "C"
::acme::library * experience_lite_get_new_library(::object * pobject)
{

   return memory_new ::user::experience::experience_lite::library(pobject);

}


#else


extern "C"
::acme::library * get_new_library(::object * pobject)
{
   return memory_new ::user::experience::experience_lite::library (pobject);
}

#endif


