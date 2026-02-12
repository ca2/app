#pragma once


#include "acme/platform/department.h"
#include "aura/user/user/user_aura.h"
#include "aura/user/user/user_axis.h"
#include "aura/user/user/user_base.h"
#include "aura/user/user/user_bred.h"
#include "aura/user/user/user_core.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/collection/string_map.h"
//#include "acme/user/user/user.h"

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
      virtual public ::platform::department,
      virtual public ::user::aura_user_layer_t,
      virtual public ::user::axis_user_layer_t,
      virtual public ::user::base_user_layer_t,
   virtual public ::user::bred_user_layer_t,
   virtual public ::user::core_user_layer_t,
      virtual public ::user::aura_user_layer,
      virtual public ::user::axis_user_layer,
      virtual public ::user::base_user_layer,
   virtual public ::user::bred_user_layer,
   virtual public ::user::core_user_layer
   {
   public:


      //__creatable(user);


      //::axis::user* m_paxisuser;
      //::berg::user* m_pbaseuser;
      //::bred::user* m_pbreduser;
      //::core::user* m_pcoreuser;

      // ::pointer<::user::interaction_base>             m_pmousefocusLButtonDown;
      // ::pointer<::user::interaction_base>             m_pmousefocusRButtonDown;
      // string_array_base                              m_straEscape;
      // ::user::style_pointer                     m_puserstyle;
      // string_map_base < ::user::style_pointer >      m_mapUserStyle;
      //
      // ::pointer<::html::html>                m_phtml; // defined in upper level
      //
      // ::platform::type                          m_typeHtmlDocument;
      // ::platform::type                          m_typeHtmlImpact;
      //
      // pointer_array < ::user::interaction >      m_uiptraToolWindow;
      //
      // //::pointer<::windowing::windowing>      m_pwindowing;
      // ::pointer <::mutex  >                     m_pmutexUser;
      //
      // ::pointer < ::mutex >                                   m_pmutexRunnable;
      //
      // ::list_base < ::pointer<::matter >>           m_listRunnable;
      //
      // ::pointer<::user::shell>               m_pshell;
      //
      // ::pointer<::windowing::desktop_environment> m_pdesktopenvironment;
      //
      // bool                                      m_bOnInitializeWindowObject;


      user();
      ~user() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void on_initialize_window_object(::acme::windowing::window* pacmewindowingwindow) override;
      virtual void _on_initialize_window_object(::acme::windowing::window* pacmewindowingwindow) override;


      //::windowing::windowing* windowing();
      // inline ::aura::application* get_app();
      // inline ::aura::session * get_session();
      //inline ::aura::system* system();
      //::windowing::desktop_environment * desktop_environment() override;

      ::user::shell* shell() override;





      //virtual ::user::interaction * interaction(::acme::windowing::window * pacmewindowingwindow) override;

      virtual ::user::interaction * get_mouse_capture(::thread * pthread) override;

      virtual ::user::interaction * get_keyboard_focus(::thread * pthread) override;

      virtual ::user::interaction * get_active_window(::thread * pthread) override;

      virtual void set_active_window(::user::interaction *) override;


      virtual ::user::interaction * get_foreground_window() override;
      //virtual void set_foreground_window(::user::interaction *) override;


      virtual ::user::style* user_style() override;

      //::user::style * get_user_style();

      //virtual void create_user_shell();



      virtual void init1() override;
      virtual void init2() override;
      virtual void init() override;


      void destroy() override;


      //virtual void create_windowing();




       ::html::html* html() override ;//  defined in upper level

       ::platform::type get_html_document_type() override;
       ::platform::type get_html_impact_type()  override;

      virtual void create_user_shell() override;

      virtual ::user::interaction_base * get_mouse_focus_LButtonDown() override;
      virtual void set_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus) override;
      virtual void defer_erase_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus) override;
      virtual ::user::interaction_base * get_mouse_focus_RButtonDown() override;
      virtual void set_mouse_focus_RButtonDown(::user::interaction_base * pmousefocus) override;

      virtual bool on_ui_mouse_message(::message::mouse_base * pmouse) override;

      virtual void SendMessageToWindows(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam) override;

      virtual void term() override;

      virtual ::platform::type controltype_to_typeinfo(::user::enum_control_type econtroltype) override;

      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style * pstyle, ::menu::item * pitem);


      virtual bool runnable_step() override;

      virtual ::pointer<::user::plain_edit>create_calculator_edit() override;

      virtual void add_impact_system(const ::atom & atom, ::user::impact_system * pimpactsystem) override;

      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom) override;

      virtual ::pointer < ::menu::menu > menu_from_xml(::particle * pparticleContext, const ::scoped_string & scopedstrXml) override;

   };




} // namespace user



