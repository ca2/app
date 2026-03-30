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


      UIWindow_uptr m_uiwindowuptrIosWindow;


      void Null() { m_uiwindowuptrIosWindow = 0; }

   };


   class ios_window : public ::operating_system::a_window<e_operating_system_ios, ios_window_t>
   {
   public:


      using BASE_TYPE = ::operating_system::a_window<e_operating_system_ios, ios_window_t>;


      using BASE_TYPE::BASE_TYPE;


      ios_window(UIWindow_uptr uiwindowuptr)
      {

         this->operator=(uiwindowuptr);
      
      }


      UIWindow_uptr as_UIWindow_uptr() const
      {
         
         if(this->m_eoperatingsystem == e_operating_system_macos)
         {

            if (!this->m_window.m_uiwindowuptrIosWindow)
            {

               throw ::exception(error_wrong_state);

            }

            return this->m_window.m_uiwindowuptrIosWindow;

         }
         else if (this->m_window.m_uiwindowuptrIosWindow)
         {

            throw ::exception(error_wrong_state);

         }
         else
         {

            return NULL;

         }
      
      }


      using BASE_TYPE::operator=;

      ios_window & operator=(UIWindow_uptr uiwindowuptr)
      {

         if (!uiwindowuptr)
         {

            this->Null();

         }
         else
         {

            this->m_eoperatingsystem = e_operating_system_macos;
            this->m_window.m_uiwindowuptrIosWindow = uiwindowuptr;

         }

         return *this;

      }

   };


} // namespace operating_system


