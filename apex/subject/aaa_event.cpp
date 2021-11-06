// From aura by camilo on ThomasBirthday2021 21:12 BRT
#include "framework.h"
//#include "aura/user/_user.h"

//
//namespace user
//{
//
//
//   control_event::control_event()
//   {
//
//      m_bOk                = true;
//
//      m_bRet               = false;
//
//      m_puserprimitive     = nullptr;
//
//      m_ptab               = nullptr;
//
//   }
//
//
//   control_event::~control_event()
//   {
//
//   }
//
//
//   ::user::form * control_event::get_form()
//   {
//
//      auto puserprimitive = m_puserprimitive;
//
//      if (::is_null(puserprimitive))
//      {
//
//         return nullptr;
//
//      }
//
//      return puserprimitive->get_form();
//
//   }
//
//
//   ::user::form * control_event::get_parent_form()
//   {
//
//      auto puserprimitive = m_puserprimitive;
//
//      if (::is_null(puserprimitive))
//      {
//
//         return nullptr;
//
//      }
//
//      return puserprimitive->get_parent_form();
//
//   }
//
//
//   ::user::interaction * control_event::user_interaction()
//   {
//
//      if (::is_null(m_puserprimitive))
//      {
//
//         return nullptr;
//
//      }
//
//      return m_puserprimitive->m_puserinteraction;
//
//   }
//
//
//   void control_event::Nok()
//   {
//
//      m_bOk = false;
//
//      m_bRet = true;
//
//   }
//
//   void control_event::Ret()
//   {
//
//      m_bRet = true;
//
//   }
//
//   void control_event::Ok()
//   {
//
//      m_bOk = true;
//
//      m_bRet = true;
//
//   }
//
//   impact * control_event::get_view()
//   {
//
//      return dynamic_cast <::user::impact *> (m_puserinteraction);
//
//   }
//
//   document * control_event::get_document()
//   {
//
//      impact * pimpact = get_view();
//
//      if(pimpact == nullptr)
//         return nullptr;
//
//      return pimpact->get_document();
//
//   }
//
//   impact_system * control_event::get_impact_system()
//   {
//
//      document * pdocument = get_document();
//
//      if(pdocument == nullptr)
//         return nullptr;
//
//      return pdocument->get_document_template();
//
//   }
//
//   string control_event::get_impact_matter()
//   {
//
//      impact_system * psystem = get_impact_system();
//
//      if(psystem == nullptr)
//         return "";
//
//      return psystem->m_strMatter;
//
//   }
//
//} // namespace user
//
//
//
//
