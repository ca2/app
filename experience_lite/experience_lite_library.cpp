#include "framework.h"





   namespace experience
   {


      namespace lite

      {


         library::library(::particle * pparticle):
            object(pparticle),
            ::acme::library(pparticle,0,"")
         {
         }


         library::~library()
         {
         }


         ::pointer<::object>library::alloc(::particle * pparticle, const ::scoped_string & scopedstrClass, object * p)
         {

            if(string(scopedstrClass) == "experience")
            {

               return ___new experience(pparticle);

            }
            else if(string(scopedstrClass) == "control_box")
            {

               return ___new control_box(pparticle);

            }
            else if(string(scopedstrClass) == "control_box_button")
            {

               return ___new button(pparticle);

            }
            else if(string(scopedstrClass) == "user_theme")
            {

               return ___new ::experience_lite::theme (pparticle);

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
::acme::library * experience_lite_get_new_library(::particle * pparticle)
{

   return ___new ::user::experience::experience_lite::library (pparticle);

}


#else


extern "C"
::acme::library * get_new_library(::particle * pparticle)
{
   return ___new ::user::experience::experience_lite::library  (pparticle);
}

#endif


