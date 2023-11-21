//
//  simple_pointer.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 31/05/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#define __pointer_is_null(p) (((uptr)(void *) p) < 4096)

#define __pointer_is_set(p) (!__pointer_is_null(p))


template < typename TYPE >
class ptr
{
  public:
   TYPE * m_p;
   
   ptr()
   {
      m_p = nullptr;
   }
   
   
   ptr(TYPE * p)
   {
      m_p = p;
      
      if(m_p)
      {
         m_p->increment_reference_count();
      }
      
   }
   
   
   ptr(const ptr & ptr)
   {
      
      m_p = ptr.m_p;
      
      if(m_p)
      {

         m_p->increment_reference_count();
    
      }
      
   }
   
   
   ptr(ptr && ptr)
   {
      
      m_p = ptr.m_p;
      
      ptr.m_p = nullptr;

   }
   
   
   ptr(enum_pointer_transfer, TYPE * p)
   {
   
      m_p = p;
      
   }

   
   ~ptr()
   {

      if(m_p)
      {

         m_p->release();
         
      }
      
   }
   
   
   TYPE * operator ->() {return m_p; }
   TYPE * operator ->() const {return m_p; }
   operator TYPE *() {return m_p; }
   operator TYPE *() const {return m_p; }
   TYPE * get() { return m_p; }
   TYPE * get() const { return m_p; }
   
   ptr & operator = (TYPE * p)
   {
      
      auto pOld = m_p;
      
      if(pOld != p)
      {
       
         p->increment_reference_count();
         
         m_p = p;
         
         if(__pointer_is_set(pOld))
         {
         
            pOld->release();
         
         }
         
      }
      
      return *this;
      
   }
   
   
   ::ptr < TYPE > & operator = (const ::ptr < TYPE > & p)
   {
      
      auto pOld = m_p;
         
      if(pOld != p.m_p)
      {
          
         p.m_p->increment_reference_count();
            
         m_p = p.m_p;
            
         if(__pointer_is_set(pOld))
         {
            
            pOld->release();
               
         }
            
      }
      
      return *this;
      
   }
   
   
   ::ptr < TYPE > & operator = (::ptr < TYPE > && p)
   {

      auto pOld = m_p;

      if (pOld != p.m_p)
      {

         m_p = p.m_p;

         p.m_p = nullptr;

         if (__pointer_is_set(pOld))
         {

            pOld->release();

         }

      }

      return *this;

   }


   //ptr & transfer(TYPE * p)
   //{
   //   
   //   m_p = p;
   //   
   //   return *this;
   //   
   //}
   //
   //
   void release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {
      
      auto p = m_p;
      
      m_p = nullptr;
      
      if(__pointer_is_set(p))
      {
   
         p->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
         
      }
      
   }
   
   
   void operator()() const
   {
    
      ((TYPE *)m_p)->call_run();
      
   }
   

   //operator u32hash() const { return { (::u32)(::uptr)m_p }; }

};



