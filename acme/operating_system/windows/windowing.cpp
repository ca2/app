//
// Created by camilo on 2024-12-05 17:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing.h"


namespace windows
{

   
   windowing * g_pwindowing = nullptr;


   windowing::windowing()
   {

      if (!g_pwindowing)
      {

         g_pwindowing = this;

      }

   }


   windowing::~windowing()
   {



   }


} // namespace windows



