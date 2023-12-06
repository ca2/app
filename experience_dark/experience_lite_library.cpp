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


         ::pointer<::object>library::alloc(::particle * pparticle, const ::string & pszClass, object * p)
         {

            if(string(pszClass) == "experience")
            {

               return __new< experience >(pparticle);

            }
            else if(string(pszClass) == "control_box")
            {

               return __new< control_box >(pparticle);

            }
            else if(string(pszClass) == "control_box_button")
            {

               return __new< button >(pparticle);

            }
            else if(string(pszClass) == "user_theme")
            {

               return __new< ::experience_lite::theme >(pparticle);

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

   return __new< ::user::experience::experience_lite::library >(pparticle);

}


#else


extern "C"
::acme::library * get_new_library(::particle * pparticle)
{
   return __new< ::user::experience::experience_lite::library  >(pparticle);
}

#endif


