#pragma once


#include "base/user/user/impact_data.h"
#include "axis/user/user/user.h"
#include "base/user/user/document_manager_container.h"
#include "acme/primitive/geometry2d/size.h"


class keyboard;
class front_end_schema;


namespace base
{


   class CLASS_DECL_BASE user :
      virtual public ::axis::user,
      virtual public ::user::document_manager_container
   {
   public:


      //::pointer < ::user::impact_system >                m_ptemplateForm;
      //::pointer < ::user::impact_system >                m_ptemplateChildForm;


      ::pointer < ::user::primitive >                    m_pmousefocusLButtonDown;
      ::pointer < ::user::primitive >                    m_pmousefocusRButtonDown;
      string_array                                       m_straEscape;

      //::pointer<::user::shell>                         m_pshell;

      //::type_atom                                      m_typeatomHtmlDocument;
      //::type_atom                                      m_typeatomHtmlImpact;

      ::pointer < ::user::menu_central >                 m_pmenucentral;

      ::pointer < ::experience::department >             m_pexperience;

      //atom_map < ::pointer < ::user::impact_system > >   m_mapimpactsystem;

      //::user::impact_system * m_ptemplateHtmlChildForm1;


      user();
      ~user() override;


      ::base::application* get_app();
      ::base::session* get_session();
      ::base::system* get_system();


      virtual void initialize(::particle * pparticle) override;




      //inline ::user::shell* shell() { return m_pshell; }

      //::user::style * get_user_style();

      //virtual void create_user_shell();

      inline ::user::menu_central* menu() { return m_pmenucentral; }

      inline ::experience::department* experience() { return m_pexperience; }


      virtual void init1() override;
      virtual void init2() override;
      virtual void init() override;

  
      inline ::type_atom get_html_document_type() { return m_typeatomHtmlDocument; }
      inline ::type_atom get_html_impact_type() { return m_typeatomHtmlImpact; }

      virtual ::type_atom user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);


      virtual ::user::primitive * get_mouse_focus_LButtonDown() override;
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus) override;
      virtual ::user::primitive * get_mouse_focus_RButtonDown() override;
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus) override;


      virtual void initialize1_experience();

      virtual void destroy() override;

      virtual void SendMessageToWindows(const ::atom & atom, wparam wParam, lparam lParam) override;

      virtual void term() override;

      virtual ::type_atom controltype_to_typeinfo(::user::enum_control_type econtroltype) override;


      virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style * pstyle, ::user::menu_item * pitem);

      
      virtual ::pointer<::user::menu_item > menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu);

      
      virtual ::pointer<::user::menu_item > popup_menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu);


      virtual void from_application_menu(::user::menu_item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu);

      virtual void popup_from_application_menu(::user::menu_item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu);


      virtual bool track_popup_menu(::user::interaction * pinteraction, ::application_menu * papplicationmenu, i32 iFlags, ::channel * pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction * pinteraction, ::application_menu * papplicationmenu, i32 iFlags, ::message::message * pmessage, ::channel * pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction * pinteraction, ::application_menu * papplicationmenu, i32 iFlags, const ::point_i32 & point, ::channel * pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction * pinteraction, ::application_menu * papplicationmenu, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum = ::size_i32(), ::channel * pchannelNotify = nullptr);

      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, ::channel* pchannelNotify = nullptr);
      //virtual ::pointer<::user::menu>track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::channel* pchannelNotify = nullptr);
      //virtual ::pointer<::user::menu>track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, ::channel* pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, ::message::message* pmessage, ::channel* pchannelNotify = nullptr);
      //virtual ::pointer<::user::menu>track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::message::message* pmessage, ::channel* pchannelNotify = nullptr);
      //virtual ::pointer<::user::menu>track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, ::message::message* pmessage, ::channel* pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, const ::point_i32& point, ::channel* pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction * pinteraction, ::user::menu_item * pitem, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum, ::channel * pchannelNotify = nullptr);
      virtual ::pointer<::user::menu>track_popup_xml_menu(::user::interaction* pinteraction, const ::string & strXml, i32 iFlags, const ::point_i32& point, const ::size_i32& sizeMinimum = ::size_i32(), ::channel * pchannelNotify = nullptr);
      //virtual ::pointer<::user::menu>track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, const ::point_i32& pointParam, ::channel* pchannelNotify = nullptr);
      //virtual ::pointer<::user::menu>track_popup_xml_menu_file(::user::interaction* pinteraction, ::payload varXmlFile, i32 iFlags, const ::point_i32& point, const ::size_i32& sizeMinimum = ::size_i32(), ::channel* pchannelNotify = nullptr);


      virtual void defer_instantiate_user_style(const ::string & strExperience = nullptr);
      ::user::style_pointer instantiate_user_style(const ::string & strExperience, ::apex::application* papp = nullptr);
      ::user::style_pointer get_user_style(const ::string & strExperience, ::apex::application* papp = nullptr);


      //virtual ::type_atom get_pane_tab_impact_type_info();
      virtual ::type_atom get_simple_frame_window_type_info();
      virtual ::type_atom get_simple_child_frame_type_info();


      virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha);


      virtual void initialize_html();


      ::pointer<::form_document>  create_typed_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);
      //::pointer<::form_document>  create_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::e_type_empty_argument);
      ::pointer<::form_document>  create_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pformcallback, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);
      //::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::e_type_empty_argument);
      ::pointer<::form_document>  create_typed_child_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);
      ::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pformcallback, ::user::element * puserelementParent, const ::payload & payload = ::e_type_empty_argument, const ::payload & payloadArgs = ::e_type_empty_argument);

      template < typename FORM >
      ::pointer<::form_document>  create_child_form(::particle * pparticle, ::user::impact_data * pimpactdata, ::payload payload = ::payload(::e_type_empty_argument))
      {

         return create_typed_child_form(pparticle, ::type < FORM >(), pimpactdata->m_pplaceholder, payload);

      }

      
      ::pointer<::user::plain_edit> create_calculator_edit() override;


   };


} // namespace base



