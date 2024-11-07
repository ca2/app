//
// Created by camilo on 2024-10-28 04:49 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "user_base.h"


namespace user
{


   //   class CLASS_DECL_AURA base_user_layer
   //   {
   //   public:
   //
   //
   //      //virtual ::pointer < ::user::interaction > create_menu_button(::user::menu * pusermenu, ::draw2d::graphics_pointer & pgraphics, ::menu::item * pmenuitem){}
   //


   ::user::menu_central* base_user_layer::menu()
   {

return nullptr;

   } // { return m_pmenucentral{} }


   ::experience::department* base_user_layer::experience()
   {

      return nullptr;

   } // { return m_pexperience{} }


   //      void init1() override{}
   //      void init2() override{}
   //      void init() override{}


   ::type_atom base_user_layer::get_html_document_type()
   {

return {};

   } // { return m_typeatomHtmlDocument{} }


   ::type_atom base_user_layer::get_html_impact_type()
   {

return {};

   } // { return m_typeatomHtmlImpact{} }


   ::type_atom base_user_layer::user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {

return {};

   }


   //      ::user::interaction_base * get_mouse_focus_LButtonDown() override{}
   //      void set_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus) override{}
   //      ::user::interaction_base * get_mouse_focus_RButtonDown() override{}
   //      void set_mouse_focus_RButtonDown(::user::interaction_base * pmousefocus) override{}


   void base_user_layer::initialize1_experience()
   {


   }


   //void destroy() override{}

   //void SendMessageToWindows(const ::atom & atom, wparam wParam, lparam lParam) override{}

   //void term() override{}

   //::type_atom controltype_to_typeinfo(::user::enum_control_type econtroltype) override{}


//    ::pointer<::user::menu_interaction> base_user_layer::create_menu_button(::user::style* pstyle, ::menu::item* pitem)
//    {
//
// return {};
//
//    }


   ::pointer<::menu::item> base_user_layer::menu_item_from_application_menu(
      ::application_menu* papplicationmenu, ::user::menu* pmenu)
   {

return {};

   }


   ::pointer<::menu::item> base_user_layer::popup_menu_item_from_application_menu(
      ::application_menu* papplicationmenu, ::user::menu* pmenu)
   {

return {};

   }


   void base_user_layer::from_application_menu(::menu::item* pmenuitem, ::application_menu* papplicationmenu,
                                               ::user::menu* pmenu)
   {

   }


   //
   //      ::pointer<::user::menu> _track_popup_menu(::user::interaction * pinteraction, ::menu::item * pmenuitem, int iFlags, const ::int_point & point, const ::int_size & sizeMinimum = ::int_size(), ::channel * pchannelNotify){}
   //

   void base_user_layer::popup_from_application_menu(::menu::item* pmenuitem, ::application_menu* papplicationmenu,
                                                     ::user::menu* pmenu)
   {


   }


   void base_user_layer::track_popup_menu(::menu::track_popup* popup)
   {


   }


   ::pointer<::user::menu> base_user_layer::user_menu_from_menu(::menu::menu* pmenu)
   {

return {};

   }


   //::pointer < ::menu::menu > menu_from_xml(::particle * pparticleContext, const ::scoped_string & scopedstrXml) override{}


   void base_user_layer::defer_instantiate_user_style(const ::string& strExperience)
   {
   }


   ::user::style_pointer base_user_layer::instantiate_user_style(const ::string& strExperience,
                                                                 ::platform::application* papp)
   {

return {};

   }


   ::user::style_pointer base_user_layer::get_user_style(const ::string& strExperience, ::platform::application* papp)
   {

return {};

   }


   //::type_atom get_pane_tab_impact_type_info(){}


   ::type_atom base_user_layer::get_simple_frame_window_type_info()
   {

return {};

   }


   ::type_atom base_user_layer::get_simple_child_frame_type_info()
   {

return {};

   }


   void base_user_layer::on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha)
   {


   }


   void base_user_layer::initialize_html()
   {


   }


   ::pointer<::form_document> base_user_layer::create_typed_form(::particle* pparticle, const ::type_atom& typeatom,
                                                                 ::user::element* puserelementParent,
                                                                 const ::payload& payload, const ::payload& payloadArgs)
   {

return {};

   }


   //::pointer<::form_document>  create_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs){}


   ::pointer<::form_document> base_user_layer::create_form(::particle* pparticle, ::user::form* pform,
                                                           ::user::form_callback* pformcallback,
                                                           ::user::element* puserelementParent,
                                                           const ::payload& payload, const ::payload& payloadArgs)
   {

return {};

   }


   //::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs){}


   ::pointer<::form_document> base_user_layer::create_typed_child_form(::particle* pparticle,
                                                                       const ::type_atom& typeatom,
                                                                       ::user::element* puserelementParent,
                                                                       const ::payload& payload,
                                                                       const ::payload& payloadArgs)
   {

return {};

   }


   ::pointer<::form_document> base_user_layer::create_child_form(::particle* pparticle, ::user::form* pform,
                                                                 ::user::form_callback* pformcallback,
                                                                 ::user::element* puserelementParent,
                                                                 const ::payload& payload, const ::payload& payloadArgs)
   {

return {};

   }


   // template < typename FORM >
   // ::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::impact_data * pimpactdata, ::payload payload = ::payload(::e_type_empty_argument))
   // {
   //
   //    return create_typed_child_form(pparticle, ::type < FORM >(), pimpactdata->m_pplaceholder, payload){}
   //
   // }


   //::pointer<::user::plain_edit> create_calculator_edit() override{}


   //void add_impact_system(const ::atom & atom, ::user::impact_system * pimpactsystem) override{}

   ::pointer<::form_document>  base_user_layer::create_typed_child_form(::particle * pparticle, const ::type_atom & typeatom, ::user::impact_data * pimpactdata, ::payload payload)
   {

      return {};

   }


   bool base_user_layer::create_impact_system(const ::atom& atom)
   {

return false;

   }


   //::pointer<::user::impact_system> impact_system(const ::atom & atom) override{}

   //::pointer < ::user::interaction > create_menu_button(::user::menu * pusermenu, ::draw2d::graphics_pointer & pgraphics, ::menu::item * pmenuitem) override{}


   //   }{}


} // namespace user
