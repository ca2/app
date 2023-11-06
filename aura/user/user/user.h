#pragma once


#include "acme/platform/department.h"
#include "acme/primitive/collection/list.h"
//#include "acme/primitive/collection/string_array.h"
#include "acme/primitive/collection/string_map.h"

//class keyboard;
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


      //__creatable(user);


      ::axis::user* m_paxisuser;
      ::base::user* m_pbaseuser;
      ::bred::user* m_pbreduser;
      ::core::user* m_pcoreuser;

      ::pointer<::user::primitive>             m_pmousefocusLButtonDown;
      ::pointer<::user::primitive>             m_pmousefocusRButtonDown;
      string_array                              m_straEscape;
      ::user::style_pointer                     m_puserstyle;
      string_map < ::user::style_pointer >      m_mapUserStyle;

      ::pointer<::html::html>                m_phtml; // defined in upper level

      ::type_atom                               m_typeatomHtmlDocument;
      ::type_atom                               m_typeatomHtmlImpact;
      
      pointer_array < ::user::interaction >      m_uiptraToolWindow;

      ::pointer<::windowing::windowing>      m_pwindowing;
      ::pointer <::mutex  >                     m_pmutexUser;

      ::pointer < ::mutex >                                   m_pmutexRunnable;

      ::list < ::pointer<::matter >>           m_listRunnable;

      ::pointer<::user::shell>               m_pshell;

      ::pointer<::windowing::desktop_environment> m_pdesktopenvironment;

      bool                                      m_bOnInitializeWindowObject;


      user();
      ~user() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void on_initialize_window_object();
      virtual void _on_initialize_window_object();


      inline ::windowing::windowing * windowing() { return m_pwindowing; }
      inline ::aura::application* get_app();
      inline ::aura::session * get_session();
      //inline ::aura::system* acmesystem();


      ::user::shell* shell();



      

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



      virtual void init1() override;
      virtual void init2() override;
      virtual void init() override;


      void destroy() override;


      virtual void create_windowing();




      inline ::html::html* html() { return m_phtml; } // defined in upper level

      inline ::type_atom get_html_document_type() { return m_typeatomHtmlDocument; }
      inline ::type_atom get_html_impact_type() { return m_typeatomHtmlImpact; }

      virtual void create_user_shell();

      virtual ::user::primitive * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual void defer_erase_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual ::user::primitive * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus);

      virtual bool on_ui_mouse_message(::message::mouse_base * pmouse);

      virtual void SendMessageToWindows(const ::atom & atom, wparam wParam, lparam lParam);

      virtual void term() override;

      virtual ::type_atom controltype_to_typeinfo(::user::enum_control_type econtroltype);

      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style * pstyle, menu_item * pitem);


      virtual bool runnable_step();

      virtual ::pointer<::user::plain_edit>create_calculator_edit();



   };




} // namespace user



