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
#if REFERENCING_DEBUGGING
   reference_referer m_referer;
#endif
   
   ptr()
   {

      m_p = nullptr;

   }
   
   
   ptr(TYPE * p REFERENCING_DEBUGGING_COMMA_PARAMS)
   {

      m_p = p;
      
      if(m_p)
      {

         m_referer = referer;

         m_p->increment_reference_count(REFERENCING_DEBUGGING_ARGS);

      }
      
   }
   
   
   ptr(const ptr & ptr REFERENCING_DEBUGGING_COMMA_PARAMS)
   {
      
      m_p = ptr.m_p;
      
      if(m_p)
      {

         m_referer = referer;

         m_p->increment_reference_count(REFERENCING_DEBUGGING_ARGS);
    
      }
      
   }
   
   
   ptr(ptr && ptr REFERENCING_DEBUGGING_COMMA_PARAMS)
   {
      
      m_p = ptr.m_p;
      
      ptr.m_p = nullptr;

      m_referer = referer;

//#if REFERENCING_DEBUGGING
//
//      m_p->replace_reference(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);
//
//#endif

   }
   
   
   ptr(enum_pointer_transfer, TYPE * p REFERENCING_DEBUGGING_COMMA_PARAMS)
   {
   
      m_p = p;
      m_referer = referer;
      
   }

   
   ~ptr()
   {

      if(m_p)
      {

         m_p->release(REFERENCING_DEBUGGING_P(m_referer));
         
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

         auto refererNew = reference_referer(this, __FUNCTION_FILE_LINE__);
       
         p->increment_reference_count(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);
         
         m_p = p;
         
         if(__pointer_is_set(pOld))
         {
         
            pOld->release(m_referer);
         
         }

         m_referer = refererNew;
         
      }
      
      return *this;
      
   }
   
   
   ::ptr < TYPE > & operator = (const ::ptr < TYPE > & p)
   {
      
      auto pOld = m_p;
         
      if(pOld != p.m_p)
      {
          
         auto refererNew = reference_referer(this, __FUNCTION_FILE_LINE__);

         p.m_p->increment_reference_count(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);
            
         m_p = p.m_p;
            
         if (__pointer_is_set(pOld))
         {

            pOld->release(m_referer);

         }

         m_referer = refererNew;

      }
      
      return *this;
      
   }
   
   
   ::ptr < TYPE > & operator = (::ptr < TYPE > && p)
   {

      auto pOld = m_p;

      if (pOld != p.m_p)
      {

         auto refererNew = ::transfer(p.m_referer);

         m_p = p.m_p;

         p.m_p = nullptr;

         if (__pointer_is_set(pOld))
         {

            pOld->release(m_referer);

         }

         m_referer = ::transfer(refererNew);

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
   void release()
   {
      
      auto p = m_p;
      
      m_p = nullptr;
      
      if(__pointer_is_set(p))
      {
   
         p->release(REFERENCING_DEBUGGING_P(m_referer));
         
      }
      
   }
   
   
   void operator()() const
   {
    
      ((TYPE *)m_p)->call_run();
      
   }
   

   //operator u32hash() const { return { (::u32)(::uptr)m_p }; }

};



