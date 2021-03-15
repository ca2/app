// Created on 2021-03-14 18:24 BRT <3ThomasBS_
#pragma once


namespace core
{


   inline ::core::system* application::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::core::system*> (m_psystem) : nullptr;

   }


   inline ::core::system* session::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::core::system*> ((::acme::system *)m_psystem) : nullptr;

   }


   inline ::core::user* application::user() const
   {
      
      return get_session() ? get_session()->user() : nullptr; 
   
   }


} // namespace core




