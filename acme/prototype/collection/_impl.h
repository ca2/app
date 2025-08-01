//
// Created by camilo on 23/12/2022 16:26 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_impl_generic_map.h"
#include "_impl_numeric_array.h"


template<typename ITERATOR_TYPE>
inline auto & range < ITERATOR_TYPE >::first() { return ::get(this->begin()); }
template<typename ITERATOR_TYPE>
inline auto & range < ITERATOR_TYPE >::first() const { return (CONST_ITEM &) ::get(this->begin()); }






#include "acme/handler/sequence_continuation.h"


inline sequence_continuation particle::user_send(const ::procedure & procedure)
{
   return { this, e_dispatch_user_send, procedure };
}
inline sequence_continuation particle::user_send()
{
   return { this, e_dispatch_user_send };
}
inline sequence_continuation particle::user_sync()
{
   return { this, e_dispatch_user_send, this };
}




inline sequence_continuation particle::user_post(const ::procedure & procedure)
{
   return { this, e_dispatch_user_post, procedure };
}
inline sequence_continuation particle::user_post()
{
   return { this, e_dispatch_user_post };
}
inline sequence_continuation particle::user_async()
{
   return { this, e_dispatch_user_post, this };
}


inline sequence_continuation particle::main_send(const ::procedure & procedure)
{
   return { this, e_dispatch_main_send, procedure };
}
inline sequence_continuation particle::main_send()
{
   return { this, e_dispatch_main_send };
}
inline sequence_continuation particle::main_sync()
{
   return { this, e_dispatch_main_send, this };
}

inline sequence_continuation particle::main_post(const ::procedure & procedure)
{
   return { this, e_dispatch_main_post, procedure };
}
inline sequence_continuation particle::main_post()
{
   return { this, e_dispatch_main_post };
}
inline sequence_continuation particle::main_async()
{
   return { this, e_dispatch_main_post, this };
}


inline sequence_continuation particle::send(const ::procedure & procedure)
{
   return { this, e_dispatch_send, procedure };
}
inline sequence_continuation particle::send()
{
   return { this, e_dispatch_send };
}


inline sequence_continuation particle::sync(const class ::time & timeTimeout)
{
   
   ::procedure procedure;

   procedure.m_pbase = this;
   
   if (!timeTimeout.is_null())
   {

      procedure.set_timeout(timeTimeout);

   }

   return { this, e_dispatch_send, procedure, should_create_sequence_on_synchronicity()};

}


inline sequence_continuation particle::post(const ::procedure & procedure)
{
   return { this, e_dispatch_post, procedure };
}
inline sequence_continuation particle::post()
{

   return { this, e_dispatch_post };
}
inline sequence_continuation particle::async()
{

   return { this, e_dispatch_post, this };
}

#include "acme/exception/cancel.h"




   template < typename CONTEXT_TYPE >
   void procedure_array_with_context<CONTEXT_TYPE>::run()
   {

      try
      {

         ::procedure_array::run();

      }
      catch (const ::cancel_exception<CONTEXT_TYPE> & cancelexception)
      {

         informationf("procedure_array : cancel_exception(%s) : %s", cancelexception.m_strContext.c_str(), cancelexception.m_strMessage.c_str());

      }


   }





   template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
::collection::count array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::_allocate(::collection::count nNewSize, bool bShrink, bool bRaw, const TYPE * ptype)
{

   if (this->m_eflagElement & e_flag_preallocated)
   {

      if (nNewSize > this->m_countAllocation)
      {

         throw ::exception(error_wrong_state);

      }

      if (ptype)
      {

         auto nOldSize = this->size();

         TYPED::copy_construct_count(this->m_begin + nOldSize, nNewSize - nOldSize, *ptype);

      }

      this->m_end = this->m_begin + nNewSize;

      return nNewSize;

   }

   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
   {

      throw_exception(error_bad_argument);

   }

   ::collection::count countOld = get_count();

   if(nNewSize == countOld)
   {

      return countOld;

   }

   if(nNewSize == 0)
   {

      if(this->m_begin != nullptr)
      {

         TYPED::destruct_count(this->m_begin, this->size());
         
         if(bShrink)
         {
            
            if(!(this->m_eflagElement & e_flag_preallocated))
            {
               
               MEMORY::free(this->m_begin + this->m_countAllocationOffset);
               m_countAllocation = 0;
               this->m_begin = nullptr;
               

            }
            else
            {
             
               this->m_end = this->m_begin;
               
            }

            this->m_countAllocationOffset = 0;
            

         }
         else
         {

            if (this->m_arrayflags.m_bZeroeOnAllocation)
            {

               memset(this->m_begin, 0, this->size() * sizeof(TYPE));

            }

         }

      }

      this->m_end = this->m_begin;
      
   }
   else if(this->m_begin == nullptr)
   {

      if(nNewSize > UPTR_MAXIMUM / sizeof(TYPE))
      {
         
         throw_exception(error_no_memory);
         
      }

      auto nAllocSize = maximum(nNewSize, m_countAddUp);

#if MEMDLEAK || defined(__MCRTDBG)

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_character())
         {

            this->m_begin = MEMORY::allocate(nAllocSize, ::get_task()->m_strFile, ::get_task()->m_iLine);

         }
         else
         {

            this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);

         }

#else

         if (::get_task_object_debug().has_character())
         {

            this->m_begin = MEMORY::allocate(nAllocSize, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__);

         }
         else
         {

            this->m_begin = MEMORY::allocate(nAllocSize, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__);

         }

#endif

      }
      else
      {

         this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);

      }

#else

      this->m_begin = MEMORY::allocate(nAllocSize, &nAllocSize);

#endif

      if (this->m_arrayflags.m_bZeroeOnAllocation)
      {

         memset(this->m_begin, 0, nAllocSize * sizeof(TYPE));

      }
      
      if(!bRaw)
      {
         
         if (::is_null(ptype))
         {
            
            TYPED::construct_count(this->m_begin, nNewSize);
            
         }
         else
         {
            
            TYPED::copy_construct_count(this->m_begin, nNewSize, *ptype);
            
         }
         
      }

      this->m_end = this->m_begin + nNewSize;

      m_countAllocation = nAllocSize;

   }
   else if(nNewSize <= m_countAllocation)
   {

      defer_erase_allocation_offset();

      if (!bRaw)
      {

         if (nNewSize > countOld)
         {

            if (::is_null(ptype))
            {

               TYPED::construct_count(this->m_begin + countOld, nNewSize - countOld);

            }
            else
            {

               TYPED::copy_construct_count(this->m_begin + countOld, nNewSize - countOld, *ptype);

            }

         }
         else if (countOld > nNewSize)
         {

            TYPED::destruct_count(this->m_begin + nNewSize, countOld - nNewSize);

            if (this->m_arrayflags.m_bZeroeOnAllocation)
            {

               memset(this->m_begin + nNewSize, 0, (countOld - nNewSize) * sizeof(TYPE));

            }

         }

      }

      this->m_end = this->m_begin + nNewSize;

   }
   else
   {

      auto countAddUp = m_countAddUp;

      if(countAddUp <= 0)
      {

         countAddUp = this->size();
         
         constrain(countAddUp, 4, 1024);

      }

      ::collection::count countNewAllocation;

      if(nNewSize < m_countAllocation + countAddUp)
      {

         countNewAllocation = m_countAllocation + countAddUp;

      }
      else
      {

         countNewAllocation = nNewSize;

      }

      if(countNewAllocation > UPTR_MAXIMUM / sizeof(TYPE))
      {
         
         throw_exception(error_no_memory);
         
      }

#if MEMDLEAK || defined(__MCRTDBG)

      TYPE* pNewData =  nullptr;

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_character())
         {

            pNewData = MEMORY::allocate(countNewAllocation, ::get_task()->m_strFile,::get_task()->m_iLine);

         }
         else
         {

            pNewData = MEMORY::allocate(countNewAllocation, __FILE__, __LINE__);

         }

#else

         if (::get_task_object_debug().has_character())
         {

            pNewData = MEMORY::allocate(countNewAllocation, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__);

         }
         else
         {

            pNewData = MEMORY::allocate(countNewAllocation, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__);

         }

#endif

      }
      else
      {

         pNewData = MEMORY::allocate(countNewAllocation, __FILE__, __LINE__);

      }


#else

      TYPE * pNewData = MEMORY::allocate(countNewAllocation, &countNewAllocation);

#endif

      // copy ___new data from old
      ::safe_memory_copy2(pNewData, (size_t)countNewAllocation, this->m_begin, (size_t) countOld);

      if (this->m_arrayflags.m_bZeroeOnAllocation)
      {

         memset(this->m_begin + countOld, 0, (countNewAllocation - countOld) * sizeof(TYPE));

      }

      if(!bRaw)
      {
         
         // construct remaining elements
         ASSERT(nNewSize > countOld);
         
         if (nNewSize > countOld)
         {
            
            if (::is_null(ptype))
            {
               
               TYPED::construct_count(pNewData + countOld, nNewSize - countOld);
               
            }
            else
            {
               
               TYPED::copy_construct_count(pNewData + countOld, nNewSize - countOld, *ptype);
               
            }
            
         }
         
      }
      
      if(!(m_eflagElement & e_flag_preallocated))
      {
         
         // get rid of old stuff (note: no destructors called)
         MEMORY::free(this->m_begin + this->m_countAllocationOffset);
         
      }
      else
      {
         
         m_eflagElement -= e_flag_preallocated;
         
      }

      this->m_begin = pNewData;

      this->m_end = this->m_begin + nNewSize;

      this->m_countAllocationOffset = 0;

      m_countAllocation = countNewAllocation;

   }

   return countOld;

}
