#pragma once


namespace filemanager
{



   inline ::core::session* component::get_session() const
   {

      return m_pcontext ? m_pcontext->m_pcoresession : nullptr;

   }

   
   inline ::core::user* component::user() const 
   {
      
      return get_session()->user(); 
   
   }



} // namespace filemanager



