// Created by camilo on 2024-09-13 15:55 <3ThomasBorregaardSorensen
// From windows/window.h by camilo on 2026-02-28 21:17 <3ThomasBorregaardSørensen!!
// From macos/window.h by camilo on 2026-03-19 08:35 <3ThomasBorregaardSørensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/window.h"


namespace operating_system
{

   union ios_window_t
   {


      void * m_pUIWindow;


      void Null() { m_pUIWindow = nullptr; }

   };


   class ios_window : public ::operating_system::a_window<::windowing::e_operating_ambient_ios, ios_window_t>
   {
   public:


      using BASE_TYPE = ::operating_system::a_window<::windowing::e_operating_ambient_ios, ios_window_t>;


      using BASE_TYPE::BASE_TYPE;

      
      ios_window(void * pUIWindow, ::windowing::enum_operating_ambient eoperatingambient)
      {

         m_eoperatingambient = eoperatingambient;
         m_window.m_pUIWindow = pUIWindow;
         //m_window.m_uTag = uTag;
         m_pacmewindowingwindow = nullptr;
         m_opaque.m_ulla[2]= 0;
      
      }

      void * as_UIWindow() const
      {
         
         if(this->m_eoperatingambient == e_operating_system_ios)
         {

            if (!this->m_window.m_pUIWindow)
            {

               throw ::exception(error_wrong_state);

            }

            return this->m_window.m_pUIWindow;

         }
         else if (this->m_window.m_pUIWindow)
         {

            throw ::exception(error_wrong_state);

         }
         else
         {

            return NULL;

         }
      
      }


      using BASE_TYPE::operator=;

      ios_window & operator=(void * pUIWindow)
      {

         if (!pUIWindow)
         {

            this->Null();

         }
         else
         {

            this->m_eoperatingambient = ::windowing::e_operating_ambient_ios;
            this->m_window.m_pUIWindow = pUIWindow;

         }

         return *this;

      }

   };


} // namespace operating_system


