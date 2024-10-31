// Created on 2021-03-14 18:24 BRT <3ThomasBS_
#pragma once


namespace core
{


   //inline ::core::system* applicationacmesystem() const
   //{

   //   return ::is_set(system()) ? dynamic_cast <::core::system*> (system()) : nullptr;

   //}


   inline ::core::system* sessionacmesystem() const
   {

      return ::is_set(system()) ? dynamic_cast <::core::system*> ((::platform::system *)system()) : nullptr;

   }


   template < typename CORE_OBJECT >
   inline ::core::application* core < CORE_OBJECT >::get_app() const
   {
      
      return this->m_papplication ? this->m_papplication : nullptr;
   
   }

   
   template < typename CORE_OBJECT >
   inline ::core::session* core < CORE_OBJECT >::get_session() const
   { 
      
      return this->m_papplication ? this->m_papplication->m_pcoresesion : nullptr;
   
   }


   template < typename CORE_OBJECT >
   inline ::core::system* core < CORE_OBJECT >system() const 
   { 
      
      return ::is_set(this->system()) ? this->system() : nullptr;
   
   }

   
   template < typename CORE_OBJECT >
   inline ::core::user* core < CORE_OBJECT >::user() const 
   {
      
      return this->get_session() ? this->get_session()->user() : nullptr;
   
   }



} // namespace core




