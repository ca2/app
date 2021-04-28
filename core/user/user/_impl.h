#pragma once


namespace core
{


   inline ::core::user* session::user()
   {

      return m_puser ? m_puser.cast < ::core::user >() : nullptr;
   
   }




} // namespace core



