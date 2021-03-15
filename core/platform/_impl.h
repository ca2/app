// Created on 2021-03-14 18:24 BRT <3ThomasBS_
#pragma once


namespace core
{


   inline ::base::system* application::get_system()
   {

      return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr;

   }


   inline ::base::system* session::get_system() const
   {

      return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr;

   }


} // namespace core




