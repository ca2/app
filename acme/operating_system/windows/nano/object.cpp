//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "object.h"
//#include "acme/user/nano/_nano.h"
//#include "_nano.h"


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

         ::DeleteObject(m_hgdiobj);

         m_hgdiobj = nullptr;

      }

   }


   void * nano_object::operating_system_data()
   {

      return m_hgdiobj;

   }


   void nano_object::destroy()
   {
    
      if (m_hgdiobj)
      {

         ::DeleteObject(m_hgdiobj);

         m_hgdiobj = nullptr;

      }

   }


} // namespace windows



