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

      bool is_null() const { return !m_hwndWindowsWindow; }

   };


   class windows_window : public ::operating_system::a_window<::windowing::e_operating_ambient_windows, windows_window_t>
   {
   public:


      using BASE_TYPE = ::operating_system::a_window<::windowing::e_operating_ambient_windows, windows_window_t>;


      using BASE_TYPE::BASE_TYPE;


      windows_window(HWND hwnd) 
      { 

         this->operator=(hwnd);
      
      }


      HWND as_HWND() const 
      { 
         
         if(this->m_eoperatingambient == ::windowing::e_operating_ambient_windows)
         {

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

         this->m_eoperatingambient = ::windowing::e_operating_ambient_windows;

         this->m_window.m_hwndWindowsWindow = hwnd;

         return *this;

      }

   };


} // namespace operating_system

#define WIN32_COLOR_WINDOW 5 // WinUser.h (windows.h) COLOR_WINDOW
#define WIN32_CW_USEDEFAULT ((::i32)0x80000000) // WinUser.h (windows.h) CW_USEDEFAULT

namespace windows
{


   class CLASS_DECL_ACME window : 
      virtual public ::acme::windowing::window
   {
   public:


      static const ::i32 ID_SHOW_ABOUT_BOX = 64800;


      ::operating_system::windows_window m_windowswindow;
      ::f64 m_dVelocity;
      class ::time m_timeLastSizeMove;
      ::i32_point m_pointSizeMoveStart;
      bool m_bMovingNow;
      bool m_bDefaultSystemMenu;
      bool m_bSizeMoveMode;
      //HWND m_hwnd;
      HMENU m_hmenuSystem;
      ::i32 m_iDebugAtom = 0;
      WNDPROC       m_wndprocDefault;

      window();
      ~window() override;


      //virtual bool on_window_procedure(LRESULT & lresult, UINT message, WPARAM wparam, LPARAM lparam);
      virtual bool call_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam);
      virtual bool on_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam);
      virtual bool _on_default_system_menu_init_menu(::lresult & lresult,  ::wparam wparam);
      virtual bool _on_default_system_menu_command(::lresult & lresult, ::wparam wparam, ::lparam lparam);
      virtual void _defer_show_system_menu(::user::mouse * ppmouse);

      virtual bool is_window_class_registered(const_char_pointer pszWindowClassName);
      virtual bool register_window_class(const_char_pointer pszWindowClassName, ::i32 iWindowClassStyle = 0, void * pHCURSOR = nullptr, void * pHBRUSH_Background = (void *) (HBRUSH)WIN32_COLOR_WINDOW);
      virtual bool _register_window_class(WNDCLASSEXW &wndclassexw, const_char_pointer pszWindowClassName);


      virtual ::operating_system::window _create_window_ex(
         ::u32 dwExStyle,
         const ::scoped_string & scopedstrWindowClassName,
         const ::scoped_string & scopedstrWindowName,
         ::u32 dwStyle,
         const ::i32_origin_size & originsize = {WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT},
         const ::operating_system::window & operatingsystemwindowParent = nullptr,
         void * pHMENU = nullptr,
         ::hinstance hinstance = nullptr,
         void * pLPARAM = nullptr);

      inline ::operating_system::window _create_window(
         const ::scoped_string & scopedstrWindowClassName,
         const ::scoped_string & scopedstrWindowName,
         ::u32 dwStyle,
         const ::i32_origin_size & originsize = {WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT},
         const ::operating_system::window & operatingsystemwindowParent = nullptr,
         void * pHMENU = nullptr,
         ::hinstance hinstance = nullptr,
         void * pLPARAM = nullptr)
      {
         return _create_window_ex(
            0,
            scopedstrWindowClassName,
            scopedstrWindowName,
            dwStyle,
            originsize,
            operatingsystemwindowParent,
            pHMENU,
            hinstance,
            pLPARAM);
      }

      virtual void createWindowEx(
         ::u32 dwExStyle,
         const ::scoped_string & scopedstrWindowClassName,
         const ::scoped_string & scopedstrWindowName,
         ::u32 dwStyle,
         const ::i32_origin_size & originsize = {WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT},
         const ::operating_system::window & operatingsystemwindowParent = nullptr,
         void * pHMENU = nullptr);

      inline void createWindow(
              const ::scoped_string & scopedstrWindowClassName,
              const ::scoped_string & scopedstrWindowName,
              ::u32 dwStyle,
              const ::i32_origin_size & originsize = {WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT,WIN32_CW_USEDEFAULT},
              const ::operating_system::window & operatingsystemwindowParent = nullptr,
              void * pHMENU = nullptr)
      {
         createWindowEx(
            0,
            scopedstrWindowClassName,
            scopedstrWindowName,
            dwStyle,
            originsize,
            operatingsystemwindowParent,
            pHMENU);
      }

      virtual void * _HWND() const;
      virtual void * _WNDPROC_default() const;

      static LRESULT CALLBACK s_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
      static HINSTANCE s_window_procedure_hinstance();

      virtual void postMessage(::user::enum_message emessage, ::wparam wparam = 0, ::lparam lparam = 0);


      bool is_window_visible() override;
      bool is_window_iconic() override;
      ::f32 get_window_scale() override;


      ::i32_point screen_to_window_client(const ::i32_point & point);
      ::i32_rectangle screen_to_window_client(const ::i32_rectangle & rectangle);
      ::i32_point window_client_to_screen(const ::i32_point & point);
      ::i32_rectangle window_client_to_screen(const ::i32_rectangle & rectangle);



      void show_window(::i32 iShowFlags) override;
      void set_window_style(::i32 iStyle) override;
      ::i64 get_window_style() override;

      void post_message(user::enum_message eusermessage, wparam wparam = {}, lparam lparam = {}) override;

      void set_active_window() override;
      void set_window_text(const scoped_string &scopedstr) override;
      void set_window_position(const ::operating_system::window & operatingsystemwindow, const ::i32_point & point, const ::i32_size & size, ::i32 iSetWindowPosFlags) override;
      void window_invalidate_rect(const i32_rectangle *prectangle, bool bErase) override;
      void update_window() override;
      void redraw_window(const i32_rectangle *prectangle, void *pHRGN, ::i32 iRedrawFlags) override;
      void window_set_focus() override;
      void set_foreground_window(::user::activation_token *puseractivationtoken) override;
      ::i32_rectangle window_get_client_rect() override;
      ::i32_rectangle get_window_rect() override;
      bool defer_update_system_menu() override;
      void dump_operating_system_child_window_hierarchy() override;


      virtual ::i32 _on_non_client_hit_test(const ::i32_point &point);


   };


   //CLASS_DECL_ACME LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


} // namespace windows






