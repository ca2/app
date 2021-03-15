#include "framework.h"





   namespace experience
   {


      namespace lite

      {


         library::library(::context_object * pcontextobject):
            object(pobject),
            ::apex::library(pobject,0,"")
         {
         }


         library::~library()
         {
         }


         __pointer(::context_object) library::alloc(::object * pobject, const char * pszClass, object * p)
         {

            if(string(pszClass) == "experience")
            {

               return new experience(pobject);

            }
            else if(string(pszClass) == "control_box")
            {

               return new control_box(pobject);

            }
            else if(string(pszClass) == "control_box_button")
            {

               return new button(pobject);

            }
            else if(string(pszClass) == "user_theme")
            {

               return new ::experience_lite::theme(pobject);

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
::apex::library * experience_lite_get_new_library(::context_object * pcontextobject)
{

   return new ::user::experience::experience_lite::library(pobject);

}


#else


extern "C"
::apex::library * get_new_library(::context_object * pcontextobject)
{
   return new ::user::experience::experience_lite::library (pobject);
}

#endif


