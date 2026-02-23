// Created by camilo on 2024-09-13 15:55 <3ThomasBorregaardSorensen
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/window.h"


namespace operating_system
{


   union windows_window_t
   {


      HWND m_hwndWindowsWindow;


      void Null() { m_hwndWindowsWindow = nullptr; }

   };


   class windows_window : public ::operating_system::a_window<e_operating_system_windows, windows_window_t>
   {
   public:


      using BASE_TYPE = ::operating_system::a_window<e_operating_system_windows, windows_window_t>;


      using BASE_TYPE::BASE_TYPE;


      windows_window(HWND hwnd) 
      { 

         this->operator=(hwnd);
      
      }


      HWND as_HWND() const 
      { 
         
         if(this->m_eoperatingsystem == e_operating_system_windows)
         {

            if (!this->m_window.m_hwndWindowsWindow)
            {

               throw ::exception(error_wrong_state);

            }

            return this->m_window.m_hwndWindowsWindow;

         }
         else if (this->m_window.m_hwndWindowsWindow)
         {

            throw ::exception(error_wrong_state);

         }
         else
         {

            return nullptr;

         }
      
      }


      using BASE_TYPE::operator=;

      windows_window & operator=(HWND hwnd)
      {

         if (::is_null(hwnd) || hwnd == INVALID_HANDLE_VALUE)
         {

            this->Null();

         }
         else
         {

            this->m_eoperatingsystem = e_operating_system_windows;
            this->m_window.m_hwndWindowsWindow = hwnd;

         }

         return *this;

      }

   };


} // namespace operating_system


namespace windows
{


   class CLASS_DECL_ACME window : 
      virtual public ::acme::windowing::window
   {
   public:


      ::operating_system::windows_window m_windowswindow;
      double m_dVelocity;
      class ::time m_timeLastSizeMove;
      ::int_point m_pointSizeMoveStart;
      bool m_bMovingNow;
      bool m_bDefaultSystemMenu;
      bool m_bSizeMoveMode;
      //HWND m_hwnd;
      HMENU m_hmenuSystem;
      int m_iDebugAtom = 0;

      window();
      ~window() override;

      virtual bool on_window_procedure(LRESULT & lresult, UINT message, WPARAM wparam, LPARAM lparam);
      virtual bool _on_default_system_menu_init_menu(LRESULT & lresult,  WPARAM wparam);
      virtual bool _on_default_system_menu_command(LRESULT & lresult, WPARAM wparam, LPARAM lparam);
      virtual void _defer_show_system_menu(::user::mouse * ppmouse);


      virtual HWND _HWND() const;


   };


   CLASS_DECL_ACME LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
   CLASS_DECL_ACME HINSTANCE get_window_procedure_hinstance();


} // namespace windows



