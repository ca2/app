//
//  _impl_ptr.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 
//  2024-06-25 18:50 <3ThomasBorregaardSorensen!! ThomasLikesNumber5!
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


template < typename TYPE >
inline ::ptr < TYPE > & ptr < TYPE >::operator = (const ::pointer < TYPE > & p)
{
   
   auto pOld = m_p;
      
   if(pOld != p.m_p)
   {
#if REFERENCING_DEBUGGING

      auto prefererOld = m_preferer;
       
      auto prefererNew = ::allocator::defer_add_referer({this, __FUNCTION_FILE_LINE__});
#endif
      p.m_p->increment_reference_count();
         
      m_p = p.m_p;
         
      if (__pointer_is_set(pOld))
      {
#if REFERENCING_DEBUGGING

         ::allocator::add_releaser(prefererOld);
#endif
         pOld->release();

      }
#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;
#endif
   }
   
   return *this;
   
}


template < typename TYPE >
inline ::ptr < TYPE > & ptr < TYPE >::operator = (::pointer < TYPE > && p)
{

   auto pOld = m_p;

   if (pOld != p.m_p)
   {
#if REFERENCING_DEBUGGING

      auto prefererOld = m_preferer;

      auto prefererNew = p.m_preferer;
#endif
      m_p = p.m_p;
      
      p.m_p = nullptr;
      
      p.m_pparticle = nullptr;

      if (__pointer_is_set(pOld))
      {
#if REFERENCING_DEBUGGING

         ::allocator::add_releaser(prefererOld);
#endif
         pOld->release();

      }
#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;
#endif
   }

   return *this;

}


template < typename TYPE >
template < typename TYPE2 >
inline ::ptr < TYPE > & ptr < TYPE >::operator = (const ::pointer < TYPE2 > & p)
{
   
   if(is_null(p))
   {
    
      this->release();
      
      return * this;
      
   }
   
   auto pOld = m_p;
   
   auto pNew = dynamic_cast < TYPE >(p.m_pparticle);
      
   if(pOld != pNew)
   {
#if REFERENCING_DEBUGGING

      auto prefererOld = m_preferer;
       
      auto prefererNew = ::allocator::defer_add_referer({this, __FUNCTION_FILE_LINE__});
#endif
      pNew->increment_reference_count();
         
      m_p = pNew;
         
      if (__pointer_is_set(pOld))
      {
#if REFERENCING_DEBUGGING

         ::allocator::add_releaser(prefererOld);
#endif
         pOld->release();

      }
#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;
#endif
   }
   
   return *this;
   
}


template < typename TYPE >
template < typename TYPE2 >
inline ::ptr < TYPE > & ptr < TYPE >::operator = (::pointer < TYPE2 > && p)
{

   if(::is_null(p))
   {
    
      this->release();
      
      return * this;
      
   }
   
   auto pOld = m_p;
   
   auto pNew = dynamic_cast < TYPE * >(p.m_psubparticle);
      
   if(pOld != pNew)
   {
#if REFERENCING_DEBUGGING

      auto prefererOld = m_preferer;

      auto prefererNew = p.m_preferer;
#endif
      m_p = pNew;
      
      p.m_p = nullptr;
      
      p.m_psubparticle = nullptr;

      if (__pointer_is_set(pOld))
      {
#if REFERENCING_DEBUGGING

         ::allocator::add_releaser(prefererOld);
#endif
         pOld->release();

      }
#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;
#endif
   }

   return *this;

}




