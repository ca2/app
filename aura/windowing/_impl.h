#pragma once


namespace windowing
{


   inline ::aura::application* cursor_manager::get_application() const
   {

      return m_papplication ? m_papplication.cast < ::aura::application >() : nullptr;

   }


   inline ::aura::session* cursor_manager::get_session() const
   {

      return m_psession ? m_psession.cast < ::aura::session >() : nullptr;

   }


   inline ::aura::system* cursor_manager::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr;

   }


   inline ::aura::application* windowing::get_application() const
   {

      return m_papplication ? m_papplication.cast < ::aura::application >() : nullptr;

   }


   inline ::aura::session* windowing::get_session() const
   {

      return m_psession ? m_psession.cast < ::aura::session >() : nullptr;

   }


   inline ::aura::system* windowing::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr;

   }


   inline ::aura::application* window::get_application() const
   {

      return m_papplication ? m_papplication.cast < ::aura::application >() : nullptr;

   }


   inline ::aura::session* window::get_session() const
   {

      return m_psession ? m_psession.cast < ::aura::session >() : nullptr;

   }


   inline ::aura::system* window::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr;

   }


} // namespace windowing



