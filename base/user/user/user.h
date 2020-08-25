#pragma once


class keyboard;
class front_end_schema;


namespace base
{


   class CLASS_DECL_BASE user :
      virtual public ::user::user,
      virtual public ::user::document_manager_container
   {
   public:


      ::user::primitive *                             m_pmousefocusLButtonDown;
      ::user::primitive *                             m_pmousefocusRButtonDown;
      string_array                                    m_straEscape;

      //__composite(::user::shell)                    m_pshell;

      //::type                                        m_typeHtmlDocument;
      //::type                                        m_typeHtmlView;

      __pointer(::user::menu_central)                 m_pmenucentral2;

      __composite(::experience::department)           m_pexperience;


      user();
      virtual ~user();


      virtual ::estatus initialize(::object* pobjectContext) override;


      //inline ::user::shell* shell() { return m_pshell; }

      //::user::style * get_user_style();

      //virtual ::estatus create_user_shell();

      ::user::menu_central* menu();

      inline ::experience::department* experience() { return m_pexperience; }


      virtual ::estatus init1() override;
      virtual ::estatus init2() override;
      virtual ::estatus init() override;

  
      inline ::type get_html_document_type() { return m_typeHtmlDocument; }
      inline ::type get_html_view_type() { return m_typeHtmlView; }

      virtual ::type user_default_controltype_to_typeinfo(::user::e_control_type econtroltype);


      virtual ::user::primitive * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual ::user::primitive * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus);


      virtual ::estatus initialize1_experience();


      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      virtual void term() override;

      virtual ::type controltype_to_typeinfo(::user::e_control_type econtroltype);


      virtual __pointer(::user::menu_interaction) create_menu_button(::user::style * pstyle, ::user::menu_item * pitem);


      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags);
      virtual __pointer(::user::menu) track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags);
      virtual __pointer(::user::menu) track_popup_xml_matter_menu(::user::interaction* pinteraction, const char* pszMatter, i32 iFlags);
      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, ::message::message* pmessage);
      virtual __pointer(::user::menu) track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::message::message* pmessage);
      virtual __pointer(::user::menu) track_popup_xml_matter_menu(::user::interaction* pinteraction, const char* pszMatter, i32 iFlags, ::message::message* pmessage);
      virtual bool track_popup_menu(::user::interaction* pinteraction, ::user::menu_item* pitem, i32 iFlags, const ::point& point);
      virtual __pointer(::user::menu) track_popup_xml_menu(::user::interaction* pinteraction, const var& varXml, i32 iFlags, const ::point& point, const ::size& sizeMinimum = ::size());
      virtual __pointer(::user::menu) track_popup_xml_matter_menu(::user::interaction* pinteraction, const char* pszMatter, i32 iFlags, const ::point& pointParam);
      virtual __pointer(::user::menu) track_popup_xml_menu_file(::user::interaction* pinteraction, var varXmlFile, i32 iFlags, const ::point& point, const ::size& sizeMinimum = ::size());


      virtual void defer_instantiate_user_style(const char* pszUiInteractionLibrary = nullptr);
      ::user::style_pointer instantiate_user_style(const char* pszExperienceLibrary, ::aura::application* papp = nullptr);
      ::user::style_pointer get_user_style(const char* pszExperienceLibrary, ::aura::application* papp = nullptr);


      //virtual ::type get_pane_tab_view_type_info();
      virtual ::type get_simple_frame_window_type_info();
      //virtual ::type get_simple_child_frame_type_info();


      virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::patha& patha);



   };


} // namespace base



