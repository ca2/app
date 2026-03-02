// Created by camilo on 2024-09-13 15:55 <3ThomasBorregaardSorensen
// From windows/window.h by camilo on 2026-02-28 21:17 <3ThomasBorregaardSørensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/window.h"


namespace operating_system
{


   union macos_window_t
   {


      CGWindowID m_cgwindowidMacosWindow;


      void Null() { m_cgwindowidMacosWindow = NULL; }

   };


   class macos_window : public ::operating_system::a_window<e_operating_system_macos, macos_window_t>
   {
   public:


      using BASE_TYPE = ::operating_system::a_window<e_operating_system_macos, macos_window_t>;


      using BASE_TYPE::BASE_TYPE;


      macos_window(CGWindowID cgwindowid)
      {

         this->operator=(cgwindowid);
      
      }


      CGWindowID as_CGWindowID() const
      {
         
         if(this->m_eoperatingsystem == e_operating_system_macos)
         {

            if (!this->m_window.m_cgwindowidMacosWindow)
            {

               throw ::exception(error_wrong_state);

            }

            return this->m_window.m_cgwindowidMacosWindow;

         }
         else if (this->m_window.m_cgwindowidMacosWindow)
         {

            throw ::exception(error_wrong_state);

         }
         else
         {

            return NULL;

         }
      
      }


      using BASE_TYPE::operator=;

      macos_window & operator=(CGWindowID cgwindowid)
      {

         if (!cgwindowid)
         {

            this->Null();

         }
         else
         {

            this->m_eoperatingsystem = e_operating_system_macos;
            this->m_window.m_cgwindowidMacosWindow = cgwindowid;

         }

         return *this;

      }

   };


} // namespace operating_system


namespace macos
{


//   class CLASS_DECL_ACME window :
//      virtual public ::acme::windowing::window
//   {
//   public:
//
//
//      ::operating_system::macos_window m_macoswindow;
//      double m_dVelocity;
//      class ::time m_timeLastSizeMove;
//      ::int_point m_pointSizeMoveStart;
//      bool m_bMovingNow;
//      bool m_bDefaultSystemMenu;
//      bool m_bSizeMoveMode;
//      //CGWindowID m_cgwindowid;
//      HMENU m_hmenuSystem;
//      int m_iDebugAtom = 0;
//
//      window();
//      ~window() override;
//
//      virtual bool on_window_procedure(LRESULT & lresult, UINT message, WPARAM wparam, LPARAM lparam);
//      virtual bool _on_default_system_menu_init_menu(LRESULT & lresult,  WPARAM wparam);
//      virtual bool _on_default_system_menu_command(LRESULT & lresult, WPARAM wparam, LPARAM lparam);
//      virtual void _defer_show_system_menu(::user::mouse * ppmouse);
//
//
//      virtual CGWindowID _CGWindowID() const;
//
//
//   };
//
//
//   CLASS_DECL_ACME LRESULT CALLBACK window_procedure(CGWindowID cgwindowid, UINT msg, WPARAM wParam, LPARAM lParam);
//   CLASS_DECL_ACME HINSTANCE get_window_procedure_hinstance();


} // namespace macos



