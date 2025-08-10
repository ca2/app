#pragma once


#include "berg/user/user/impact_data.h"
#include "axis/user/user/user.h"
#include "berg/user/user/document_manager_container.h"
#include "acme/prototype/geometry2d/size.h"


class keyboard;
class front_end_schema;


namespace berg
{


   class CLASS_DECL_BERG user :
      virtual public ::axis::user,
      virtual public ::user::document_manager_container
   {
   public:


      // //::pointer < ::user::impact_system >                m_ptemplateForm;
      // //::pointer < ::user::impact_system >                m_ptemplateChildForm;
      //
      //
      // ::pointer < ::user::interaction_base >                    m_pmousefocusLButtonDown;
      // ::pointer < ::user::interaction_base >                    m_pmousefocusRButtonDown;
      // string_array_base                                       m_straEscape;
      //
      // //::pointer<::user::shell>                         m_pshell;
      //
      // //::type_atom                                      m_typeatomHtmlDocument;
      // //::type_atom                                      m_typeatomHtmlImpact;
      //
      // ::pointer < ::user::menu_central >                 m_pmenucentral;
      //
      // ::pointer < ::experience::department >             m_pexperience;
      //
      // //atom_map < ::pointer < ::user::impact_system > >   m_mapimpactsystem;
      //
      // //::user::impact_system * m_ptemplateHtmlChildForm1;


      user();
      ~user() override;


      //::berg::application* get_app();
      //::berg::session* get_session();
      //::berg::system* get_system();


      void initialize(::particle * pparticle) override;




      //inline ::user::shell* shell() { return m_pshell; }

      //::user::style * get_user_style();

      //virtual void create_user_shell();

      ::user::menu_central* menu() override;

      ::experience::department* experience() override;

      void init1() override;
      void init2() override;
      void init() override;

  
      ::type_atom get_html_document_type() override;
      ::type_atom get_html_impact_type() override;

      ::type_atom user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype) override;


      ::user::interaction_base * get_mouse_focus_LButtonDown() override;
      void set_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus) override;
      ::user::interaction_base * get_mouse_focus_RButtonDown() override;
      void set_mouse_focus_RButtonDown(::user::interaction_base * pmousefocus) override;


      void initialize1_experience() override;

      void destroy() override;

      void SendMessageToWindows(::enum_message emessage, ::wparam wparam, ::lparam lparam) override;

      void term() override;

      ::type_atom controltype_to_typeinfo(::user::enum_control_type econtroltype) override;


      virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style * pstyle, ::menu::item * pitem);

      
      ::pointer<::menu::item > menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu) override;

      
      ::pointer<::menu::item > popup_menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu) override;


      void from_application_menu(::menu::item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu) override;
      
//      
//      virtual ::pointer<::user::menu> _track_popup_menu(::user::interaction * pinteraction, ::menu::item * pmenuitem, int iFlags, const ::int_point & point, const ::int_size & sizeMinimum = ::int_size(), ::channel * pchannelNotify = nullptr);
//

      void popup_from_application_menu(::menu::item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu) override;

      void track_popup_menu(::menu::track_popup * popup) override;

      
      ::pointer < ::user::menu > user_menu_from_menu(::menu::menu * pmenu) override;

      
      ::pointer < ::menu::menu > menu_from_xml(::particle * pparticleContext, const ::scoped_string & scopedstrXml) override;


      void defer_instantiate_user_style(const ::scoped_string & scopedstrExperience = nullptr) override;
      ::user::style_pointer instantiate_user_style(const ::scoped_string & scopedstrExperience, ::platform::application* papp = nullptr) override;
      ::user::style_pointer get_user_style(const ::scoped_string & scopedstrExperience, ::platform::application* papp = nullptr) override;


      //virtual ::type_atom get_pane_tab_impact_type_info();
      ::type_atom get_simple_frame_window_type_info() override;
      ::type_atom get_simple_child_frame_type_info() override;


      void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array_base& patha) override;


      void initialize_html() override;


      ::pointer<::form_document>  create_typed_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument) override;
      //::pointer<::form_document>  create_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::e_type_empty_argument);
      ::pointer<::form_document>  create_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pformcallback, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument) override;
      //::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::e_type_empty_argument);
      ::pointer<::form_document>  create_typed_child_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument) override;
      ::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pformcallback, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument) override;

      //template < typename FORM >
      //::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::impact_data * pimpactdata, ::payload payload = ::payload(::e_type_empty_argument))
      //{

      //   return create_typed_child_form(pparticle, ::type < FORM >(), pimpactdata->m_pplaceholder, payload);

      //}

      virtual ::pointer<::form_document>  create_typed_child_form(::particle * pparticle, const ::type_atom & typeatom, ::user::impact_data * pimpactdata, ::payload payload = ::payload(::e_type_empty_argument));


      
      ::pointer<::user::plain_edit> create_calculator_edit() override;


      void add_impact_system(const ::atom & atom, ::user::impact_system * pimpactsystem) override;


      bool create_impact_system(const ::atom & atom) override;


      ::pointer<::user::impact_system> impact_system(const ::atom & atom) override;

      ::pointer < ::user::interaction > create_menu_button(::user::menu * pusermenu, ::draw2d::graphics_pointer & pgraphics, ::menu::item * pmenuitem) override;

   };


} // namespace berg



