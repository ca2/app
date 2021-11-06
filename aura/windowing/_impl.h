#pragma once


namespace windowing
{


   inline ::aura::application* cursor_manager::get_application() const
   {

      return m_pcontext && m_pcontext->m_papexapplication ? m_pcontext->m_papexapplication->m_pauraapplication : nullptr;

   }


   inline ::aura::session* cursor_manager::get_session() const
   {

      return m_pcontext && m_pcontext->m_papexsession ? m_pcontext->m_papexsession->m_paurasession : nullptr;

   }


   inline ::aura::system* cursor_manager::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr;

   }


   inline ::aura::application* windowing::get_application() const
   {

      return m_pcontext && m_pcontext->m_papexapplication ? m_pcontext->m_papexapplication->m_pauraapplication : nullptr;

   }


   inline ::aura::session* windowing::get_session() const
   {

      return m_pcontext && m_pcontext->m_papexsession ? m_pcontext->m_papexsession->m_paurasession : nullptr;

   }


   inline ::aura::system* windowing::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr;

   }


   inline ::aura::application* window::get_application() const
   {

      return m_pcontext && m_pcontext->m_papexapplication ? m_pcontext->m_papexapplication->m_pauraapplication : nullptr;

   }


   inline ::aura::session* window::get_session() const
   {

      return m_pcontext && m_pcontext->m_papexsession ? m_pcontext->m_papexsession->m_paurasession : nullptr;

   }


   inline ::aura::system* window::get_system() const
   {

      return m_psystem ? m_psystem->m_paurasystem : nullptr;

   }


} // namespace windowing



