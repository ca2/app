//
// Created by camilo on 2024-10-28 04:06 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace user
{


   struct CLASS_DECL_AURA base_user_layer_t
   {


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

      ::pointer < ::user::menu_central >                 m_pmenucentral;

      ::pointer < ::experience::department >             m_pexperience;

      //atom_map < ::pointer < ::user::impact_system > >   m_mapimpactsystem;

      //::user::impact_system * m_ptemplateHtmlChildForm1;


   };


   class CLASS_DECL_AURA base_user_layer
   {
   public:


      //virtual ::pointer < ::user::interaction > create_menu_button(::user::menu * pusermenu, ::draw2d::graphics_pointer & pgraphics, ::menu::item * pmenuitem);



      virtual ::user::menu_central* menu();// { return m_pmenucentral; }

      virtual ::experience::department* experience();// { return m_pexperience; }


//      virtual void init1() override;
//      virtual void init2() override;
//      virtual void init() override;


      virtual ::type_atom get_html_document_type();// { return m_typeatomHtmlDocument; }

      virtual ::type_atom get_html_impact_type();// { return m_typeatomHtmlImpact; }

      virtual ::type_atom user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);


//      virtual ::user::interaction_base * get_mouse_focus_LButtonDown() override;
//      virtual void set_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus) override;
//      virtual ::user::interaction_base * get_mouse_focus_RButtonDown() override;
//      virtual void set_mouse_focus_RButtonDown(::user::interaction_base * pmousefocus) override;


      virtual void initialize1_experience();


      //virtual void destroy() override;

      //virtual void SendMessageToWindows(::enum_message emessage, ::wparam wparam, ::lparam lparam) override;

      //virtual void term() override;

      //virtual ::type_atom controltype_to_typeinfo(::user::enum_control_type econtroltype) override;


      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style * pstyle, ::menu::item * pitem);


      virtual ::pointer<::menu::item > menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu);


      virtual ::pointer<::menu::item > popup_menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu);


      virtual void from_application_menu(::menu::item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu);

//
//      virtual ::pointer<::user::menu> _track_popup_menu(::user::interaction * pinteraction, ::menu::item * pmenuitem, int iFlags, const ::int_point & point, const ::int_size & sizeMinimum = ::int_size(), ::channel * pchannelNotify = nullptr);
//

      virtual void popup_from_application_menu(::menu::item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu);


      virtual void track_popup_menu(::menu::track_popup * popup);


      virtual ::pointer < ::user::menu > user_menu_from_menu(::menu::menu * pmenu);


      //::pointer < ::menu::menu > menu_from_xml(::particle * pparticleContext, const ::scoped_string & scopedstrXml) override;


      virtual void defer_instantiate_user_style(const ::scoped_string & scopedstrExperience = nullptr);


      virtual ::user::style_pointer instantiate_user_style(const ::scoped_string & scopedstrExperience, ::platform::application* papp = nullptr);


      virtual ::user::style_pointer get_user_style(const ::scoped_string & scopedstrExperience, ::platform::application* papp = nullptr);


      //virtual ::type_atom get_pane_tab_impact_type_info();


      virtual ::type_atom get_simple_frame_window_type_info();


      virtual ::type_atom get_simple_child_frame_type_info();


      virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array_base& patha);


      virtual void initialize_html();


      virtual ::pointer<::form_document>  create_typed_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);


      //::pointer<::form_document>  create_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::e_type_empty_argument);


      virtual ::pointer<::form_document>  create_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pformcallback, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);


      //::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::e_type_empty_argument);


      virtual ::pointer<::form_document>  create_typed_child_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);


      virtual ::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pformcallback, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);


      // template < typename FORM >
      // ::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::impact_data * pimpactdata, ::payload payload = ::payload(::e_type_empty_argument))
      // {
      //
      //    return create_typed_child_form(pparticle, ::type < FORM >(), pimpactdata->m_pplaceholder, payload);
      //
      // }

      ::pointer<::form_document>  create_typed_child_form(::particle * pparticle, const ::type_atom & typeatom, ::user::impact_data * pimpactdata, ::payload payload = ::payload(::e_type_empty_argument));


      //::pointer<::user::plain_edit> create_calculator_edit() override;


      //void add_impact_system(const ::atom & atom, ::user::impact_system * pimpactsystem) override;


      virtual bool create_impact_system(const ::atom & atom);


      //::pointer<::user::impact_system> impact_system(const ::atom & atom) override;

      //::pointer < ::user::interaction > create_menu_button(::user::menu * pusermenu, ::draw2d::graphics_pointer & pgraphics, ::menu::item * pmenuitem) override;


   };


} // namespace user



