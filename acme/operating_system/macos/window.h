// Created by camilo on 2024-09-13 15:55 <3ThomasBorregaardSorensen
// From windows/window.h by camilo on 2026-02-28 21:17 <3ThomasBorregaardSørensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/window.h"


namespace operating_system
{


   struct macos_window_t
   {


      //::u64 m_uCgwindowidMacosWindow;
      union
      {
         ::u64 m_uNSWindow;
         ::u64 m_uNSImpact;
      };
      //::u64 m_uTag;


      void Null() { m_uNSWindow = 0; //m_uTag = 0;
      }
      
      
      bool is_set() const{
         return this->m_uNSWindow != 0;
      }
      bool is_null() const
      {
         return !this->is_set();
      }


   };


   class macos_window : public ::operating_system::a_window<::windowing::e_operating_ambient_macos, macos_window_t>
   {
   public:


      using BASE_TYPE = ::operating_system::a_window<::windowing::e_operating_ambient_macos, macos_window_t>;


      using BASE_TYPE::BASE_TYPE;


//      macos_window(::uptr uptr)
//      {
//
//         this->operator=(uptr);
//      
//      }

      macos_window(::uptr uptr, ::windowing::enum_operating_ambient eoperatingambient)
      {

         m_eoperatingambient = eoperatingambient;
         m_window.m_uNSWindow = uptr;
         //m_window.m_uTag = uTag;
         m_pacmewindowingwindow = nullptr;
         m_opaque.m_ulla[2]= 0;
      
      }

      ::uptr window_uptr() const
      {
         
         if(this->m_eoperatingambient == ::windowing::e_operating_ambient_macos)
         {

            return this->m_window.m_uNSWindow;

         }
         else if(this->m_eoperatingambient == ::windowing::e_operating_ambient_macos_impact_by_tag)
         {

            return this->m_window.m_uNSWindow;

         }
         else
         {
            
            return NULL;
            
         }
      
      }

      ::uptr impact_uptr() const
      {
         
         if(this->m_eoperatingambient == ::windowing::e_operating_ambient_macos_impact2)
         {

            return this->m_window.m_uNSImpact;

         }
         else
         {
            
            return NULL;
            
         }
      
      }

  
      macos_window & operator=(::uptr uNSWindow)
      {

         if (!uNSWindow)
         {

            this->Null();

         }
         else
         {

            this->m_eoperatingambient = ::windowing::e_operating_ambient_macos;
            this->m_window.m_uNSWindow = uNSWindow;

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
//      ::f64 m_dVelocity;
//      class ::time m_timeLastSizeMove;
//      ::i32_point m_pointSizeMoveStart;
//      bool m_bMovingNow;
//      bool m_bDefaultSystemMenu;
//      bool m_bSizeMoveMode;
//      //CGWindowID m_cgwindowid;
//      HMENU m_hmenuSystem;
//      ::i32 m_iDebugAtom = 0;
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



