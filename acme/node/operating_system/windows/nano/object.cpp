//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSørensen!!
//
#include "framework.h"


namespace windows
{


   nano_object::nano_object()
   {

      m_hgdiobj = nullptr;

   }


   nano_object::~nano_object()
   {

      if(m_hgdiobj)
      {

         ::DelectObject(m_hgdiobj);

         m_hgdiobj = nullptr;

      }

   }


}



