#pragma once


namespace base
{


   inline ::base::system* application::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr;

   }


   inline ::base::session* application::get_session() const
   {

      return m_pcontext ? m_pcontext->m_pbasesession : nullptr;

   }


   inline ::base::system* session::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr;

   }


} // namespace base



