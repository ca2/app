#pragma once


class keyboard;
class front_end_schema;

//#include "user_window_map.h"
//#include "user_style.h"


namespace user
{


   class CLASS_DECL_BASE user :
      virtual public ::aura::department
   {
   public:



      ::user::primitive *                          m_pmousefocusLButtonDown;
      ::user::primitive *                          m_pmousefocusRButtonDown;
      string_array                                 m_straEscape;
      //::user::style_pointer                      m_puserstyle;

      ::type                                       m_typeHtmlDocument;
      ::type                                       m_typeHtmlView;




      user();
      virtual ~user();



      //::user::style * get_user_style();


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


   };


} // namespace user



