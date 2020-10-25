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
      virtual public ::apex::department
   {
   public:


      ::base::user *                         m_pbaseuser;
      ::core::user *                         m_pcoreuser;
      ::user::primitive *                    m_pmousefocusLButtonDown;
      ::user::primitive *                    m_pmousefocusRButtonDown;
      string_array                           m_straEscape;
      ::user::style_pointer                  m_puserstyle;
      string_map < ::user::style_pointer >   m_mapUserStyle;

      __composite(::html::html)              m_phtml; // defined in upper level

      ::type                                 m_typeHtmlDocument;
      ::type                                 m_typeHtmlView;
      
      __pointer_array(::user::interaction)   m_uiptraToolWindow;

      user();
      virtual ~user();



      virtual ::user::style* get_user_style();

      //::user::style * get_user_style();

      //virtual ::estatus create_user_shell();


      virtual ::estatus init1() override;
      virtual ::estatus init2() override;
      virtual ::estatus init() override;



      inline ::html::html* html() { return m_phtml; } // defined in upper level

      inline ::type get_html_document_type() { return m_typeHtmlDocument; }
      inline ::type get_html_view_type() { return m_typeHtmlView; }



      virtual ::user::primitive * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual ::user::primitive * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus);

      virtual bool on_ui_mouse_message(::message::mouse* pmouse);

      virtual void SendMessageToWindows(const ::id & id, WPARAM wParam, LPARAM lParam);

      virtual void term() override;

      virtual ::type controltype_to_typeinfo(::user::e_control_type econtroltype);

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style * pstyle, menu_item * pitem);


      


   };


} // namespace user



