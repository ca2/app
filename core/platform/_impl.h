// Created on 2021-03-14 18:24 BRT <3ThomasBS_
#pragma once


namespace core
{


   //inline ::core::system* application::get_system() const
   //{

   //   return ::is_set(m_psystem) ? dynamic_cast <::core::system*> (m_psystem) : nullptr;

   //}


   inline ::core::system* session::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::core::system*> ((class ::system *)m_psystem) : nullptr;

   }


   template < typename CORE_OBJECT >
   inline ::core::application* core < CORE_OBJECT >::get_application() const 
   {
      
      return this->m_pcontext ? this->m_pcontext->m_pcoreapplication : nullptr;
   
   }

   
   template < typename CORE_OBJECT >
   inline ::core::session* core < CORE_OBJECT >::get_session() const
   { 
      
      return this->m_pcontext ? this->m_pcontext->m_pcoresesion : nullptr;
   
   }


   template < typename CORE_OBJECT >
   inline ::core::system* core < CORE_OBJECT >::get_system() const 
   { 
      
      return ::is_set(this->m_psystem) ? this->m_psystem->m_pcoresystem : nullptr;
   
   }

   
   template < typename CORE_OBJECT >
   inline ::core::user* core < CORE_OBJECT >::user() const 
   {
      
      return this->get_session() ? this->get_session()->user() : nullptr;
   
   }



} // namespace core




