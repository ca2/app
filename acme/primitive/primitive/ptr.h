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
   reference_referer * m_preferer;
#endif
   
   ptr()
   {

      m_p = nullptr;

      m_preferer = nullptr;

   }
   
   
   /// consumes a referer
   ptr(TYPE * p)
   {

      if(p)
      {

         m_preferer = ::allocator::defer_get_referer(p, {this, __FUNCTION_FILE_LINE__});

         p->increment_reference_count();

         m_p = p;

      }
      else
      {

         m_p = nullptr;

         m_preferer = nullptr;

      }
      
   }
   
   
   /// consumes a referer
   ptr(const ptr & ptr)
   {
      
      if(ptr.m_p)
      {

         m_preferer = ::allocator::defer_get_referer(ptr.m_p, {this, __FUNCTION_FILE_LINE__});

         ptr.m_p->increment_reference_count();

         m_p = ptr.m_p;
    
      }
      else
      {

         m_preferer = nullptr;

         m_p = nullptr;

      }
      
   }
   
   
   /// referer is transferred ?
   ptr(ptr && ptr)
   {
      
      m_p = ptr.m_p;

      m_preferer = ptr.m_preferer;
      
      ptr.m_p = nullptr;

      ptr.m_preferer = nullptr;

   }
   
   
   ///// referer is transferred ?
   //ptr(transfer_t, TYPE * p)
   //{
   //
   //   m_p = p;
   //   
   //}

   ptr(const ::pointer < TYPE > & p);

   ptr(::pointer < TYPE > && p);

   template < typename T2 >
   ptr(const ::pointer < T2 > & p);

   template < typename T2 >
   ptr(::pointer < T2 > && p);


   ~ptr()
   {

      release();
      
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

         auto prefererOld = m_preferer;

         //auto refererNew = reference_referer(this, __FUNCTION_FILE_LINE__);

         auto prefererNew = ::allocator::defer_get_referer(p, { this, __FUNCTION_FILE_LINE__ });
       
         p->increment_reference_count();
         
         m_p = p;
         
         if(__pointer_is_set(pOld))
         {

            ::allocator::add_releaser(prefererOld);
         
            pOld->release();
         
         }

         m_preferer = prefererNew;
         
      }
      
      return *this;
      
   }
   
   
   ::ptr < TYPE > & operator = (const ::ptr < TYPE > & p)
   {
      
      auto pOld = m_p;
         
      if(pOld != p.m_p)
      {

         auto prefererOld = m_preferer;
          
         auto prefererNew = ::allocator::defer_add_referer({this, __FUNCTION_FILE_LINE__});

         p.m_p->increment_reference_count();
            
         m_p = p.m_p;
            
         if (__pointer_is_set(pOld))
         {

            ::allocator::add_releaser(prefererOld);

            pOld->release();

         }

         m_preferer = prefererNew;

      }
      
      return *this;
      
   }
   
   
   ::ptr < TYPE > & operator = (::ptr < TYPE > && p)
   {

      auto pOld = m_p;

      if (pOld != p.m_p)
      {

         auto prefererOld = m_preferer;

         auto prefererNew = p.m_preferer;

         m_p = p.m_p;

         p.m_p = nullptr;

         if (__pointer_is_set(pOld))
         {

            ::allocator::add_releaser(prefererOld);

            pOld->release();

         }

         m_preferer = prefererNew;

      }

      return *this;

   }

   ptr & operator = (const ::pointer < TYPE > & p);

   ptr & operator = (::pointer < TYPE > && p);

   template < typename T2 >
   ptr & operator = (const ::pointer < T2 > & p);

   template < typename T2 >
   ptr & operator = (::pointer < T2 > && p);

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

      if (__pointer_is_set(p))
      {

         auto prefererReleaser = m_preferer;

         m_p = nullptr;

         m_preferer = nullptr;

         if (__pointer_is_set(p))
         {

            ::allocator::add_releaser(prefererReleaser);

            p->release();

         }

      }
      
   }
   
   
   void operator()() const
   {
    
      ((TYPE *)m_p)->call_run();
      
   }
   

   operator u32hash() const { return { (::u32)(::uptr)m_p }; }

};



