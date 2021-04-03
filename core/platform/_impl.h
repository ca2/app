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

      return ::is_set(m_psystem) ? dynamic_cast <::core::system*> ((::acme::system *)m_psystem) : nullptr;

   }


   inline ::core::user* application::user() const
   {
      
      return get_session() ? get_session()->user() : nullptr; 
   
   }


   template < typename CORE_OBJECT >
   inline ::core::application* core < CORE_OBJECT >::get_application() const 
   {
      
      return this->m_papplication ? this->m_papplication.cast < ::core::application >() : nullptr;
   
   }

   
   template < typename CORE_OBJECT >
   inline ::core::session* core < CORE_OBJECT >::get_session() const
   { 
      
      return this->m_psession ? this->m_psession.cast < ::core::session >() : nullptr;
   
   }


   template < typename CORE_OBJECT >
   inline ::core::system* core < CORE_OBJECT >::get_system() const 
   { 
      
      return ::is_set(this->m_psystem) ? dynamic_cast <::core::system*> (this->m_psystem) : nullptr;
   
   }

   
   template < typename CORE_OBJECT >
   inline ::core::user* core < CORE_OBJECT >::user() const 
   {
      
      return this->get_session() ? this->get_session()->user() : nullptr;
   
   }



} // namespace core




