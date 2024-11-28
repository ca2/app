// created by Camilo <3CamiloSasukeThomasBorregaardSoerens
// en
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// Adapted by Camilo for android 2022-01-05 04:34 <3TBS (Thomas likes number 5), Mummi and bilbo!!
// Adapted by Camilo for cached/simulation of mouse-capture/keyboard-focus state information and
// a few other things present in sandboxed applications (mobile/tablet/small devices)
//     - 2022-06-02 12:44 PM <3TBS (Thomas likes number 5), Mummi and bilbo!!
// Created by camilo on 2022-06-02 12:41 PM <3ThomasBorregaardSorensen!!
// as acme::sandbox_windowing on 2024-11-25 23:24 by
// camilo <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/collection/string_list.h"
#include "acme/windowing/windowing.h"

namespace acme
{

namespace sandbox_windowing
{ 


class window;



class CLASS_DECL_ACME windowing :
virtual public ::acme::windowing::windowing
{
public:
   
   
   ::pointer<::acme::sandbox_windowing::window>         m_pwindowKeyboardFocus;
   //::pointer<::acme::sandbox_windowing::window>         m_pwindowMouseCapture;
   ::pointer<::acme::sandbox_windowing::window>         m_pwindowActive;
   
   
   ::pointer<::acme::sandbox_windowing::host_interaction>                    m_phostinteraction;
   
   ::pointer<::acme::windowing::window>                 m_pwindowApplicationHost;
   
   itask_t                                         m_itask;
   
   ::procedure_list                                m_procedurelist;
   
   
   windowing();
   ~windowing() override;
   
   
   void initialize(::particle * pparticle) override;
   
   
   bool is_branch_current() const override;
   
   
   void initialize_windowing() override;
   
   void finalize_windowing() override;
   
   void defer_initialize_host_window(const ::int_rectangle* lpcrect) override;
   
   ::acme::windowing::window* get_application_host_window() override;
   
   
   void _will_finish_launching() override;
   
   //::windowing::display* display() override;
   
   
   //virtual ::pointer<::windowing::cursor>load_default_cursor(enum_cursor ecursor) override;
   ::pointer < ::acme::windowing::window > get_new_window() override;
   
   //      ::windowing::window* new_window(::windowing::window* pimpl) override;
   //
   void erase_window(::acme::windowing::window* pwindow) override;
   
   ::acme::windowing::window* window(oswindow oswindow) override;
   
   virtual void _message_handler(void* p) override;
   
   ::acme::windowing::window * get_keyboard_focus(::thread* pthread) override;
   
   ::acme::windowing::window * get_mouse_capture(::thread* pthread) override;
   
   
   bool defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow) override;
   
   
   void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr) override;
   
   
   //void windowing_post(const ::procedure& procedure) override;
   
   //virtual bool aaa_x11_runnable_step();
   
   
   //::windowing::text_editor_interface* get_text_editor_interface() override;
   
   
   //using ::acme::windowing::windowing::get_cursor;
   
   
   //::pointer<::windowing::cursor>get_cursor(enum_cursor ecursor) override;
   
   
   
   
};


} // namespace sandbox_windowing


} // namespace acme
