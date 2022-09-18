#pragma once


#include "axis/user/user/user.h"
#include "base/user/user/document_manager_container.h"

class keyboard;
class front_end_schema;


namespace base
{


   class CLASS_DECL_BASE user :
      virtual public ::axis::user,
      virtual public ::user::document_manager_container
   {
   public:


      ::user::primitive *                             m_pmousefocusLButtonDown;
      ::user::primitive *                             m_pmousefocusRButtonDown;
      string_array                                    m_straEscape;

      //__composite(::user::shell)                    m_pshell;

      //::type                                        m_typeHtmlDocument;
      //::type                                        m_typeHtmlImpact;

      __composite(::user::menu_central)               m_pmenucentral;

      __composite(::experience::department)           m_pexperience;
      ::user::impact_system * m_ptemplateHtmlChildForm1;




      user();
      ~user() override;


      inline ::base::application* get_app() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }


      virtual void initialize(::object * pobject) override;




      //inline ::user::shell* shell() { return m_pshell; }

      //::user::style * get_user_style();

      //virtual void create_user_shell();

      inline ::user::menu_central* menu() { return m_pmenucentral; }

      inline ::experience::department* experience() { return m_pexperience; }


      virtual void init1() override;
      virtual void init2() override;
      virtual void init() override;

  
      inline ::type get_html_document_type() { return m_typeHtmlDocument; }
      inline ::type get_html_impact_type() { return m_typeHtmlImpact; }

      virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);


      virtual ::user::primitive * get_mouse_focus_LButtonDown() override;
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus) override;
      virtual ::user::primitive * get_mouse_focus_RButtonDown() override;
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus) override;


      virtual void initialize1_experience();

      virtual void destroy() override;

      virtual void SendMessageToWindows(const ::atom & atom, wparam wParam, lparam lParam) override;

      virtual void term() override;

      virtual ::type controltype_to_typeinfo(::user::enum_control_type econtroltype) override;


      virtual __pointer(::user::menu_interaction) create_menu_button(::user::style * pstyle, ::user::menu_item * pitem);


      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, ::channel* pchannelNotify = nullptr);
      virtual __pointer(::user::menu) track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::channel* pchannelNotify = nullptr);
      virtual __pointer(::user::menu) track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, ::channel* pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, ::message::message* pmessage, ::channel* pchannelNotify = nullptr);
      virtual __pointer(::user::menu) track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::message::message* pmessage, ::channel* pchannelNotify = nullptr);
      virtual __pointer(::user::menu) track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, ::message::message* pmessage, ::channel* pchannelNotify = nullptr);
      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, const ::point_i32& point, ::channel* pchannelNotify = nullptr);
      virtual __pointer(::user::menu) track_popup_xml_menu(::user::interaction* pinteraction, const ::payload& varXml, i32 iFlags, const ::point_i32& point, const ::size_i32& sizeMinimum = ::size_i32(), ::channel * pchannelNotify = nullptr);
      virtual __pointer(::user::menu) track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, const ::point_i32& pointParam, ::channel* pchannelNotify = nullptr);
      virtual __pointer(::user::menu) track_popup_xml_menu_file(::user::interaction* pinteraction, ::payload varXmlFile, i32 iFlags, const ::point_i32& point, const ::size_i32& sizeMinimum = ::size_i32(), ::channel* pchannelNotify = nullptr);


      virtual void defer_instantiate_user_style(const ::string & strExperience = nullptr);
      ::user::style_pointer instantiate_user_style(const ::string & strExperience, ::apex::application* papp = nullptr);
      ::user::style_pointer get_user_style(const ::string & strExperience, ::apex::application* papp = nullptr);


      //virtual ::type get_pane_tab_impact_type_info();
      virtual ::type get_simple_frame_window_type_info();
      virtual ::type get_simple_child_frame_type_info();


      virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha);


      virtual void initialize_html();


   };


} // namespace base



