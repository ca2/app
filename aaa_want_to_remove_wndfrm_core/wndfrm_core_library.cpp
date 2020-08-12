#include "framework.h"


namespace user
{


   namespace experience
   {


      namespace experience_core
      {


         library::library(::object * pobject):
            object(pobject),
            ::aura::library(pobject,0,"")
         {
         }


         library::~library()
         {
         }


         //bool library::is_uinteraction_library()
         //{

         //   return true;

         //}


         __pointer(::context_object) library::alloc(::object * pobject,const char * pszClass, object * p)
         {

            if(string(pszClass) == "experience")
            {

               return new interaction(pobject);

            }
            else if(string(pszClass) == "control_box")
            {

               return new MetaControlBox(pobject);

            }
            else if(string(pszClass) == "control_box_button")
            {

               return new ::user::meta_button(pobject);

            }
            else if(string(pszClass) == "user_style")
            {

               return new ::experience_core::user_style(get_object());

            }
            else
            {

               return nullptr;

            }

         }


      } // namespace experience_core


   } // namespace experience


} // namespace user


#ifdef CUBE

extern "C"
::aura::library * experience_core_get_new_library(::object * pobject)
{

   return new ::user::experience::experience_core::library(pobject);

}


#else


extern "C"
::aura::library * get_new_library(::object * pobject)
{
   return new ::user::experience::experience_core::library (pobject);
}

#endif


