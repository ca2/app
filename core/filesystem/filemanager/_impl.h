#pragma once


namespace filemanager
{



   inline ::core::session* component::get_session() const
   {

      return m_psession ? m_psession.cast < ::core::session >() : nullptr;

   }

   
   inline ::core::user* component::user() const 
   {
      
      return get_session()->user(); 
   
   }



} // namespace filemanager



