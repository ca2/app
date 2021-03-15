#pragma once


namespace base
{


   inline ::base::system* application::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr;

   }


   inline ::base::session* application::get_session() const
   {

      return ::is_set(m_psession) ? m_psession.cast < ::base::session >() : nullptr;

   }


   inline ::base::system* session::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr;

   }


} // namespace base



