//
// Created by camilo on 2024-10-28 03:18 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/prototype/collection/list.h"


namespace user
{


   struct CLASS_DECL_AURA aura_user_layer_t
   {

      ::pointer<::user::interaction_base>             m_pmousefocusLButtonDown;
      ::pointer<::user::interaction_base>             m_pmousefocusRButtonDown;
      string_array                              m_straEscape;
      ::user::style_pointer                     m_puserstyle;
      string_map < ::user::style_pointer >      m_mapUserStyle;

      ::pointer<::html::html>                m_phtml; // defined in upper level

      ::type_atom                               m_typeatomHtmlDocument;
      ::type_atom                               m_typeatomHtmlImpact;

      pointer_array < ::user::interaction >      m_uiptraToolWindow;

      //::pointer<::windowing::windowing>      m_pwindowing;
      ::pointer <::mutex  >                     m_pmutexUser;

      ::pointer < ::mutex >                                   m_pmutexRunnable;

      ::list < ::pointer<::matter >>           m_listRunnable;

      ::pointer<::user::shell>               m_pshell;

      //::pointer<::windowing::desktop_environment> m_pdesktopenvironment;

      bool                                      m_bOnInitializeWindowObject;

   };


   class CLASS_DECL_AURA aura_user_layer
   {
   public:

      virtual void on_initialize_window_object(::acme::windowing::window* pacmewindowingwindow);
      virtual void _on_initialize_window_object(::acme::windowing::window* pacmewindowingwindow);


      //::windowing::windowing* windowing();
      // inline ::aura::application* get_app();
      // inline ::aura::session * get_session();
      //inline ::aura::system* system();
      //virtual ::windowing::desktop_environment * desktop_environment();

      virtual ::user::shell* shell();





      virtual ::user::interaction * interaction(oswindow oswindow);

      virtual ::user::interaction * get_mouse_capture(::thread * pthread);

      virtual ::user::interaction * get_keyboard_focus(::thread * pthread);

      virtual ::user::interaction * get_active_window(::thread * pthread);

      virtual void set_active_window(::user::interaction *);


      virtual ::user::interaction * get_foreground_window();
      virtual void set_foreground_window(::user::interaction *);


      virtual ::user::style* user_style();

      //::user::style * get_user_style();

      //virtual void create_user_shell();



//      virtual void init1() override;
//      virtual void init2() override;
//      virtual void init() override;
//
//
//      void destroy() override;
//

      //virtual void create_windowing();




      virtual ::html::html* html();// { return m_phtml; } // defined in upper level

      virtual ::type_atom get_html_document_type();// { return m_typeatomHtmlDocument; }
      virtual ::type_atom get_html_impact_type();// { return m_typeatomHtmlImpact; }

      virtual void create_user_shell();

      virtual ::user::interaction_base * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus);
      virtual void defer_erase_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus);
      virtual ::user::interaction_base * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::interaction_base * pmousefocus);

      virtual bool on_ui_mouse_message(::message::mouse_base * pmouse);

      virtual void SendMessageToWindows(::enum_message emessage, ::wparam wparam, ::lparam lparam);

      //virtual void term() override;

      virtual ::type_atom controltype_to_typeinfo(::user::enum_control_type econtroltype);

      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style * pstyle, ::menu::item * pitem);


      virtual bool runnable_step();

      virtual ::pointer<::user::plain_edit>create_calculator_edit();

      virtual void add_impact_system(const ::atom & atom, ::user::impact_system * pimpactsystem);

      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom);

      virtual ::pointer < ::menu::menu > menu_from_xml(::particle * pparticleContext, const ::scoped_string & scopedstrXml);

   };


} // namespace user



