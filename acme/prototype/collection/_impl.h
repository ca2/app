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
::collection::count base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::_allocate(::collection::count nNewSize, bool bShrink, bool bRaw, const TYPE * ptype)
{

   //if (this->m_erange & e_range_array_allocate)
   //{

   //   if (nNewSize > this->m_countAllocation)
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   if (nNewSize > this->m_countAllocation + this->m_countAllocationOffset)
   //   {

   //      auto countOffset = this->m_countAllocationOffset;

   //      for (auto p = this->m_begin; p < this->m_end; p++)
   //      {

   //         p[countOffset] = *p;

   //      }

   //      this->m_begin += countOffset;

   //      this->m_end += countOffset;

   //      this->m_countAllocationOffset = 0;

   //   }

   //   if (ptype)
   //   {

   //      auto nOldSize = this->size();

   //      TYPED::destruct_count(this->m_begin + nOldSize, nNewSize - nOldSize);

   //      TYPED::copy_construct_count(this->m_begin + nOldSize, nNewSize - nOldSize, *ptype);

   //   }

   //   this->m_end = this->m_begin + nNewSize;

   //   if (this->m_end == this->m_begin)
   //   {

   //      if (this->m_countAllocationOffset != 0)
   //      {

   //         this->m_begin += this->m_countAllocationOffset;

   //         this->m_end = this->m_begin;

   //      }

   //   }

   //   return nNewSize;

   //}

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
            
            //if(!(this->m_erange & e_range_array_allocate))
            {
               
               MEMORY::free(this->m_begin + this->m_countAllocationOffset);
               m_countAllocation = 0;
               this->m_begin = nullptr;
               

            }
            //else
            //{
            // 
            //   TYPED::construct_count(this->m_begin, this->size());
            //   this->m_end = this->m_begin;

            //}

            this->m_countAllocationOffset = 0;


         }
         else
         {

            if (this->m_erange & e_range_array_clear_on_allocate)
            {

               memset(this->m_begin, 0, maximum(0, countOld) * sizeof(TYPE));

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

      if (this->m_erange & e_range_array_clear_on_allocate)
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

            if (this->m_erange & e_range_array_clear_on_allocate)
            {

               memset(this->m_begin + nNewSize, 0, (countOld - nNewSize) * sizeof(TYPE));

            }
            else
            {
               TYPED::construct_count(this->m_begin + nNewSize, countOld - nNewSize);

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

      if (this->m_erange & e_range_array_clear_on_allocate)
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
      
      //if(!(this->m_erange & e_range_array_allocate))
      {
         
         // get rid of old stuff (note: no destructors called)
         MEMORY::free(this->m_begin + this->m_countAllocationOffset);
         
      }
      //else
      //{
      //   
      //   this->m_erange = (::enum_range) (this->m_erange & ~e_range_array_allocate);
      //   
      //}

      this->m_begin = pNewData;

      this->m_end = this->m_begin + nNewSize;

      this->m_countAllocationOffset = 0;

      m_countAllocation = countNewAllocation;

   }

   return countOld;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::array_base_ok() const
{

   if (this->m_begin)
   {

      ASSERT(this->m_end);

      ASSERT(this->m_countAllocation > 0);

   }
   else
   {

      ASSERT(!this->m_end);

      ASSERT(this->m_countAllocation == 0);

   }

}



template < class TYPE, class ARG_TYPE >
void list_base < TYPE, ARG_TYPE >::list_base_ok() const
{

   if (this->m_begin)
   {

      ASSERT(this->m_end);

      ASSERT(this->m_count > 0);

   }
   else
   {

      ASSERT(!this->m_end);

      ASSERT(this->m_count == 0);

   }

}


template < typename ITEM, enum_allocate t_eallocate >
void node_set_base < ITEM, t_eallocate >::container_ok() const
{

   if (this->m_begin)
   {

      ASSERT(this->m_end);

      ASSERT(this->m_count > 0);

   }
   else
   {

      ASSERT(!this->m_end);

      ASSERT(this->m_count == 0);

   }

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::base_array(const base_array< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & array)
{

   this->m_begin = nullptr;
   this->m_end = nullptr;
   this->m_erange = e_range_none;
   //this->m_erange = e_array_none;
   m_countAddUp = 0;
   m_countAllocation = 0;
   m_countAllocationOffset = 0;
   set_size(array.get_size());


   TYPED::copy_count(this->m_begin, array.m_begin, this->size());
   // for (::collection::index i = 0; i < array.get_size(); i++)
   // {
   //
   //    this->element_at(i) = array[i];
   //
   // }

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::base_array(base_array< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > && array) noexcept :
   ARRAY_RANGE(no_initialize_t{})
{

   this->m_begin = array.m_begin;
   this->m_end = array.m_end;
   this->m_erange = array.m_erange;
   this->m_countAddUp = array.m_countAddUp;
   this->m_countAllocation = array.m_countAllocation;
   this->m_countAllocationOffset = array.m_countAllocationOffset;

   array.m_begin = nullptr;
   array.m_end = nullptr;
   array.m_erange = e_range_none;
   array.m_countAllocation = 0;
   array.m_countAllocation = 0;
   array.m_countAllocationOffset = 0;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
template < typename OTHER_RANGE >
base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::
base_array(const OTHER_RANGE & range) requires
(container_range < OTHER_RANGE >
   && !::std::is_base_of_v < base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >, ::std::remove_cvref_t < OTHER_RANGE > >) :
   base_array()
{ 

   for (auto p = range.begin(); range.is_iterator_ok(p); p++)
   {

      this->add((ARG_TYPE) *p);

   }

}



