//
// Created by camilo on 2024-10-28 03:32 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "user_aura.h"


namespace user
{


   //   class CLASS_DECL_AURA aura_user_layer
   //   {
   //   public:

   void aura_user_layer::on_initialize_window_object()
   {
   }


   void aura_user_layer::_on_initialize_window_object()
   {
   }


   //::windowing::windowing* windowing(){}
   // inline ::aura::application* get_app(){}
   // inline ::aura::session * get_session(){}
   //inline ::aura::system* system(){}
   ::windowing::desktop_environment* aura_user_layer::desktop_environment()
   {
      return nullptr;
   }


   ::user::shell* aura_user_layer::shell()
   {
      return nullptr;
   }


   ::user::interaction* aura_user_layer::interaction(oswindow oswindow)
   {
      return nullptr;
   }


   ::user::interaction* aura_user_layer::get_mouse_capture(::thread* pthread)
   {
      return nullptr;
   }


   ::user::interaction* aura_user_layer::get_keyboard_focus(::thread* pthread)
   {
      return nullptr;
   }


   ::user::interaction* aura_user_layer::get_active_window(::thread* pthread)
   {
      return nullptr;
   }


   void aura_user_layer::set_active_window(::user::interaction*)
   {
   }


   ::user::interaction* aura_user_layer::get_foreground_window()
   {
      return nullptr;
   }


   void aura_user_layer::set_foreground_window(::user::interaction*)
   {
   }


   ::user::style* aura_user_layer::user_style()
   {
      return nullptr;
   }


   //::user::style * get_user_style(){}

   //void create_user_shell(){}


   //      void init1() override{}
   //      void init2() override{}
   //      void init() override{}
   //
   //
   //      void destroy() override{}
   //

   //void create_windowing(){}


   ::html::html* aura_user_layer::html()
   {
      return nullptr;
   } // { return m_phtml{} } // defined in upper level

   ::type_atom aura_user_layer::get_html_document_type()
   {
      return {};
   } // { return m_typeatomHtmlDocument{} }
   ::type_atom aura_user_layer::get_html_impact_type()
   {
      return {};
   } // { return m_typeatomHtmlImpact{} }

   void aura_user_layer::create_user_shell()
   {
   }


   ::user::interaction_base* aura_user_layer::get_mouse_focus_LButtonDown()
   {
      return nullptr;
   }


   void aura_user_layer::set_mouse_focus_LButtonDown(::user::interaction_base* pmousefocus)
   {
   }


   void aura_user_layer::defer_erase_mouse_focus_LButtonDown(::user::interaction_base* pmousefocus)
   {
   }


   ::user::interaction_base* aura_user_layer::get_mouse_focus_RButtonDown()
   {
      return nullptr;
   }


   void aura_user_layer::set_mouse_focus_RButtonDown(::user::interaction_base* pmousefocus)
   {
   }


   bool aura_user_layer::on_ui_mouse_message(::message::mouse_base* pmouse)
   {
      return false;
   }


   void aura_user_layer::SendMessageToWindows(const ::atom& atom, wparam wParam, lparam lParam)
   {
   }


   //void term() override{}

   ::type_atom aura_user_layer::controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {
      return {};
   }


   //::pointer<::user::menu_interaction>create_menu_button(::user::style * pstyle, ::menu::item * pitem){}


   bool aura_user_layer::runnable_step()
   {
      return false;
   }


   ::pointer<::user::plain_edit> aura_user_layer::create_calculator_edit()
   {
      return {};
   }


   void aura_user_layer::add_impact_system(const ::atom& atom, ::user::impact_system* pimpactsystem)
   {
   }


   ::pointer<::user::impact_system> aura_user_layer::impact_system(const ::atom& atom)
   {
      return {};
   }


   ::pointer<::menu::menu> aura_user_layer::menu_from_xml(::particle* pparticleContext,
                                                          const ::scoped_string& scopedstrXml)
   {
      return {};
   }


   //}{}


} // namespace user
