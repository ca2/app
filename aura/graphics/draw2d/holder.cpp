// Created by camilo on 2022-06-23 20:53 <3ThomasBorregaardSoerensen!!
#include "platform.h"
#include "holder.h"


namespace draw2d
{


   holder::holder()
   {

   }


   holder::~holder()
   {


   }


   void holder::destroy()
   {

      m_pholdee.defer_destroy_and_release();

   }


} // namespace draw2d



 
