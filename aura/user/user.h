#pragma once


class keyboard;
class front_end_schema;

//#include "user_window_map.h"
//#include "user_style.h"

namespace core
{

   class user;

} //namespace core


namespace user
{


   class CLASS_DECL_AURA user :
      virtual public ::acme::department
   {
   public:

      ::axis::user* m_paxisuser;
      ::base::user* m_pbaseuser;
      ::bred::user* m_pbreduser;
      ::core::user* m_pcoreuser;

      __pointer(::user::primitive)              m_pmousefocusLButtonDown;
      __pointer(::user::primitive)              m_pmousefocusRButtonDown;
      string_array                              m_straEscape;
      ::user::style_pointer                     m_puserstyle;
      string_map < ::user::style_pointer >      m_mapUserStyle;

      __composite(::html::html)                 m_phtml; // defined in upper level

      ::type                                    m_typeHtmlDocument;
      ::type                                    m_typeHtmlView;
      
      __pointer_array(::user::interaction)      m_uiptraToolWindow;

      __composite(::windowing::windowing)       m_pwindowing;

      ::mutex                                   m_mutexRunnable;

      ::list < __pointer(::matter) >            m_listRunnable;

      __composite(::user::shell)                m_pshell;

      bool                                      m_bOnInitializeWindowObject;


      user();
      ~user() override;


      virtual ::e_status initialize(::object * pobject) override;


      virtual ::e_status on_initialize_window_object();
      virtual ::e_status _on_initialize_window_object();


      inline ::windowing::windowing * windowing() { return m_pwindowing; }
      inline ::aura::application* get_application();
      inline ::aura::session * get_session();
      inline ::aura::system* get_system();


      ::user::shell* shell();



      

      virtual ::user::interaction * interaction(oswindow oswindow);

      virtual ::user::interaction * get_mouse_capture(::thread * pthread);

      virtual ::user::interaction * get_keyboard_focus(::thread * pthread);

      virtual ::user::interaction * get_active_window(::thread * pthread);

      virtual ::e_status set_active_window(::user::interaction *);

      
      virtual ::user::interaction * get_foreground_window();
      virtual ::e_status set_foreground_window(::user::interaction *);


      virtual ::user::style* user_style();

      //::user::style * get_user_style();

      //virtual ::e_status create_user_shell();



      virtual ::e_status init1() override;
      virtual ::e_status init2() override;
      virtual ::e_status init() override;


      ::e_status destroy() override;


      virtual ::e_status create_windowing();




      inline ::html::html* html() { return m_phtml; } // defined in upper level

      inline ::type get_html_document_type() { return m_typeHtmlDocument; }
      inline ::type get_html_view_type() { return m_typeHtmlView; }

      virtual ::e_status create_user_shell();

      virtual ::user::primitive * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual void defer_erase_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual ::user::primitive * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus);

      virtual bool on_ui_mouse_message(::message::mouse_base * pmouse);

      virtual void SendMessageToWindows(const ::id & id, wparam wParam, lparam lParam);

      virtual ::e_status term() override;

      virtual ::type controltype_to_typeinfo(::user::enum_control_type econtroltype);

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style * pstyle, menu_item * pitem);


      virtual bool runnable_step();



   };




} // namespace user



