//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "object.h"
//#include "acme/nano/user/_nano.h"
//#include "_nano.h"


namespace windows
{


   namespace nano
   {


      namespace user
      {


         object::object()
         {

            m_hgdiobj = nullptr;

         }


         object::~object()
         {

            if (m_hgdiobj)
            {

               ::DeleteObject(m_hgdiobj);

               m_hgdiobj = nullptr;

            }

         }


         void* object::operating_system_data()
         {

            return m_hgdiobj;

         }


         void object::destroy()
         {

            if (m_hgdiobj)
            {

               ::DeleteObject(m_hgdiobj);

               m_hgdiobj = nullptr;

            }

         }



      } // namespace user


   } // namespace nano


} // namespace windows



