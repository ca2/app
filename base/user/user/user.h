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
      virtual public ::aura::department
   {
   public:


      ::core::user* m_pcoreuser;
      ::user::primitive *           m_pmousefocusLButtonDown;
      ::user::primitive *           m_pmousefocusRButtonDown;
      string_array                       m_straEscape;
      //::user::style_pointer              pstyle;

      __composite(::user::shell)                   m_pshell;


      ::type                                       m_typeHtmlDocument;
      ::type                                       m_typeHtmlView;
      
      
      


      user();
      virtual ~user();



      inline ::user::shell* shell() { return m_pshell; }

      //::user::style * get_user_style();

      virtual ::estatus create_user_shell();


      virtual ::estatus init1() override;
      virtual ::estatus init2() override;
      virtual ::estatus init() override;

  
      inline ::type get_html_document_type() { return m_typeHtmlDocument; }
      inline ::type get_html_view_type() { return m_typeHtmlView; }



      virtual ::user::primitive * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual ::user::primitive * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus);



      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      virtual void term() override;

      virtual ::type controltype_to_typeinfo(::user::e_control_type econtroltype);


      virtual __pointer(::user::menu_interaction) create_menu_button(::user::style * pstyle, menu_item * pitem);


   };


} // namespace user



