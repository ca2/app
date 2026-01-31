


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::base_array()
{

   m_nGrowBy = 0;
   m_pData = nullptr;
   m_nSize = 0;
   m_nMaxSize = 0;

}




template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::~base_array ()
{

   if (m_pData != nullptr)
   {

      destroy();

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::count base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::resize(::collection::count nNewSize, ARG_TYPE t, ::collection::count nGrowBy)
{

   return allocate(nNewSize, nGrowBy, &t);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::count base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::allocate_in_bytes(::collection::count nNewSize,::collection::count nGrowBy)
{

   if(nGrowBy < 0)
   {

      return allocate(nNewSize / sizeof(TYPE),-1);

   }
   else
   {

      return allocate(nNewSize / sizeof(TYPE),nGrowBy / sizeof(TYPE));

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::index base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_at(::collection::index nIndex,::collection::count nCount)
{

   //ASSERT_OK(this);

   ::collection::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      throw ::exception(error_bad_argument);

   }

   ::collection::count nMoveCount = m_nSize - (nUpperBound);

   ALLOCATOR::destruct_count(m_pData + nIndex, nCount REFERENCING_DEBUGGING_COMMA_THIS);

   if(nMoveCount)
   {
      ::safe_memory_transfer(m_pData + nIndex,(size_t)nMoveCount * sizeof(TYPE),m_pData + nUpperBound,(size_t)nMoveCount * sizeof(TYPE));
   }

   m_nSize -= nCount;

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::index base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_item(TYPE * p)
{

   return erase_at(p - m_pData);

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::free_extra()
{

   if(m_nSize != m_nMaxSize)
   {
      // shrink to desired int_size
#ifdef SIZE_T_MAX
      ASSERT(m_nSize <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
#endif
      TYPE* pNewData = nullptr;
      if(m_nSize != 0)
      {
         TYPE * pNewData;
#if defined(__MCRTDBG) || MEMDLEAK
#ifdef __MCRTDBG
         if (::get_task() != nullptr)
         {
            if (::get_task()->m_strFile.has_character())
            {
               pNewData = ALLOCATOR::alloc(m_nSize, ::get_task()->m_strFile, ::get_task()->m_iLine);
            }
            else
            {
               pNewData = ALLOCATOR::alloc(m_nSize, __FILE__, __LINE__);
            }
         }
         else
         {
            pNewData = ALLOCATOR::alloc(m_nSize, __FILE__, __LINE__);
         }
#else

         if (::get_task_object_debug().has_character())
         {

            pNewData = ALLOCATOR::alloc(m_nSize, ::get_task_object_debug(), 0);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(m_nSize, __FILE__, __LINE__);

         }

#endif

#else

         pNewData = ALLOCATOR::alloc(m_nSize);

#endif      // copy aaa_primitive_new data from old

         // copy aaa_primitive_new data from old
         ::safe_memory_copy(pNewData, (size_t)m_nSize * sizeof(TYPE),m_pData, (size_t)m_nSize * sizeof(TYPE));

      }

      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);

      m_pData = pNewData;

      m_nMaxSize = m_nSize;

   }

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::destroy()
{

   if(m_pData != nullptr)
   {

      ALLOCATOR::destruct_count(m_pData, m_nSize REFERENCING_DEBUGGING_COMMA_THIS);

      ALLOCATOR::_free(m_pData);

      m_pData     = nullptr;
      m_nSize     = 0;
      m_nMaxSize  = 0;

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::index base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::insert_at(::collection::index nIndex,const TYPE & newElement,::collection::count nCount /*=1*/)
{

   ::collection::index nIndexParam = make_room_at(nIndex, nCount);

   while(nCount--)
   {

      ALLOCATOR::copy(m_pData + nIndex, &newElement);

      nIndex++;

   }

   return nIndexParam;

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::index base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::make_room_at(::collection::index nIndex, ::collection::count nCount /*=1*/)
{

   ASSERT(nIndex >= 0);    // will expand to meet need

   if(nCount <= 0)
      return -1;

   if(nIndex < 0)
      throw ::exception(error_bad_argument);

   if(nIndex >= m_nSize)
   {

      // adding after the end of the array
      set_size(nIndex + nCount,-1);   // grow so nIndex is valid

   }
   else
   {

      // inserting in the middle of the array
      ::collection::count nOldSize = (::collection::count) m_nSize;

      set_size((::collection::count) m_nSize + nCount,-1);  // grow it to aaa_primitive_new int_size
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::safe_memory_transfer(m_pData + nIndex + nCount,(size_t) ((nOldSize - nIndex) * sizeof(TYPE)),m_pData + nIndex,(size_t)((nOldSize - nIndex) * sizeof(TYPE)));

      ::zero(m_pData + nIndex, nCount* sizeof(TYPE));

      ALLOCATOR::construct_count(m_pData + nIndex,nCount);

   }

   // insert aaa_primitive_new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   return nIndex;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::count base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::append(const base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & src)
{

   ::collection::count nOldSize = m_nSize;

   ::collection::count nSrcSize = src.m_nSize;   // to enable to append to itself

   allocate(nOldSize + nSrcSize);

   ALLOCATOR::copy_count(m_pData + nOldSize, src.m_pData, nSrcSize);

   return nOldSize;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::copy(const base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & src)
{

   if(this == &src)
   {

      return;

   }

   ::collection::count nSrcSize = src.m_nSize;

   allocate(nSrcSize);

   ALLOCATOR::copy_count(m_pData,src.m_pData, nSrcSize);

}



// take in accptr that _001RemoveIndexes machine
// the ::collection::index raw_array by sorting it and returning
// only the indexes that could be erased
// without indexes duplicates
template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::_001RemoveIndexes(index_array & ia)
{

   // sort
   ::sort::quick_sort(ia,true);

   ::collection::index i = ia.get_upper_bound();

   // filter out of upper bound indexes
   while(i >= 0 && ia[i] >= get_size())
   {

      ia.erase_at(i);

      i--;

   }

   // filter out of lower bound indexes
   while(ia.get_size() > 0 && ia[0] < 0)
   {

      ia.erase_at(0);

   }

   i = ia.get_upper_bound();

   // filter out duplicates
   while(i > 0 && ia[i] >= get_size())
   {

      if(ia[i] == ia[i - 1])
         ia.erase_at(i);

      i--;

   }

   erase_indexes(ia);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_indexes(const index_array & ia)
{


   // erase indexes
   for(::collection::index i = ia.get_upper_bound(); i >= 0; i--)
   {

      erase_at(ia[i]);

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_descending_indexes(const index_array & ia)
{

   for(::collection::index i = 0; i < ia.get_count(); i++)
   {

      erase_at(ia[i]);

   }

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::index base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::insert_at(::collection::index nIndex,base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > * pNewArray)
{

   ASSERT(pNewArray != nullptr);
   ASSERT(nIndex >= 0);    // will expand to meet need

   ::collection::count nCount = pNewArray->get_size();

   if (nCount <= 0)
      return -1;

   if (nIndex < 0)
      throw ::exception(error_bad_argument);

   if (nIndex >= m_nSize)
   {

      // adding after the end of the array
      set_size(nIndex + nCount, -1);   // grow so nIndex is valid

   }
   else
   {

      // inserting in the middle of the array
      ::collection::count nOldSize = (::collection::count) m_nSize;

      set_size((::collection::count) (m_nSize + nCount), -1);  // grow it to aaa_primitive_new int_size
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::safe_memory_transfer(m_pData + nIndex + nCount, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)), m_pData + nIndex, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)));

      ::zero(m_pData + nIndex, nCount* sizeof(TYPE));

      ALLOCATOR::construct_count(m_pData + nIndex, nCount);

   }

   // insert aaa_primitive_new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   ::collection::index nIndexParam = nIndex;

   ::collection::index i = 0;

   while (nCount--)
   {

      ALLOCATOR::copy(m_pData + nIndex, pNewArray->m_pData + i);

      nIndex++;

   }

   return nIndexParam;


}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
TYPE base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::pick_at(::collection::index nIndex)
{

   ::collection::count nCount = 1;

   ::collection::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      throw ::exception(error_bad_argument);

   }

   ::collection::count nMoveCount = m_nSize - (nUpperBound);

   auto t = m_pData[nIndex];

   ALLOCATOR::destruct_count(m_pData + nIndex, nCount REFERENCING_DEBUGGING_COMMA_THIS);

   if (nMoveCount)
   {

      ::safe_memory_transfer(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE), m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));

   }

   m_nSize -= nCount;

   return ::transfer(t);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::pick_at(::collection::index nIndex, ::collection::count nCount)
{

   //ASSERT_OK(this);

   ::collection::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      throw ::exception(error_bad_argument);

   }

   ::collection::count nMoveCount = m_nSize - (nUpperBound);

   base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > a(m_pData + nIndex, (size_t)nMoveCount);

   ALLOCATOR::destruct_count(m_pData + nIndex, nCount REFERENCING_DEBUGGING_COMMA_THIS);

   if (nMoveCount)
   {

      ::safe_memory_transfer(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE), m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));

   }

   m_nSize -= nCount;

   return a;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::count base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::set_raw_size(::collection::count nNewSize,::collection::count nGrowBy)
{

   ::collection::count countOld = get_count();

   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
      throw ::exception(error_bad_argument);

   if(nGrowBy >= 0)
      m_nGrowBy = nGrowBy;  // set aaa_primitive_new int_size

   if(nNewSize == 0)
   {

      // shrink to nothing
      if(m_pData != nullptr)
      {

         ALLOCATOR::_free(m_pData);

         m_pData = nullptr;

      }

      m_nSize = m_nMaxSize = 0;
   }
   else if (m_pData == nullptr)
   {
      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if (nNewSize > SIZE_T_MAX / sizeof(TYPE))
         throw ::exception(error_no_memory);
      ASSERT(nNewSize <= SIZE_T_MAX / sizeof(TYPE));    // no overflow
#endif
      ::collection::count nAllocSize = (::collection::count) maximum(nNewSize, m_nGrowBy);
#if defined(__MCRTDBG) || MEMDLEAK
      if (::get_task() != nullptr)
      {
#if defined(MEMDLEAK)

         if (::get_task()->m_strFile.has_character())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strFile, 0);

         }
         else
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#else

         if (::get_task_object_debug().has_character())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, ::get_task_object_debug(), ::get_task()->m_iLine);

         }
         else
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#endif

      }
      else
      {

         m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

      }

#else

      m_pData = ALLOCATOR::alloc(nAllocSize);

#endif

      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if(nNewSize <= m_nMaxSize)
   {
      m_nSize = nNewSize;
   }
   else
   {
      // otherwise, grow aaa_base_array
      nGrowBy = (::collection::count) m_nGrowBy;
      if(nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = (::collection::count) m_nSize;
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
      }
      ::collection::count nNewMax;
      if(nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = (::collection::count) (m_nMaxSize + nGrowBy);  // granularity
      else
         nNewMax = nNewSize;  // no slush

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
         throw ::exception(error_bad_argument);

#ifdef SIZE_T_MAX
      ASSERT(nNewMax <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
#endif
      TYPE * pNewData;
#if defined(__MCRTDBG) || MEMDLEAK
#ifdef __MCRTDBG

      if (::get_task() != nullptr)
      {

         if (::get_task()->m_strFile.has_character())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, ::get_task()->m_strFile, ::get_task()->m_iLine);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

         }

      }
      else
      {

         pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

      }

#else

      if (::get_task_object_debug().has_character())
      {

         pNewData = ALLOCATOR::alloc(nNewMax, ::get_task_object_debug(), ::get_task()->m_iLine);

      }
      else
      {

         pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

      }

#endif

#else

      pNewData = ALLOCATOR::alloc(nNewMax);

#endif      // copy aaa_primitive_new data from old

      ::safe_memory_copy(pNewData,(size_t)nNewMax * sizeof(TYPE),m_pData,(size_t)m_nSize * sizeof(TYPE));

      ///for(int i = 0; i < nNewSize - m_nSize; i++)
      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);

      m_pData = pNewData;

      m_nSize = nNewSize;

      m_nMaxSize = nNewMax;

   }

   return countOld;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
::collection::count base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::allocate(::collection::count nNewSize,::collection::count nGrowBy, const TYPE * ptype)
{

   ::collection::count countOld = get_count();

   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
   {

      throw ::exception(error_bad_argument);

   }

   if(nGrowBy >= 0)
   {

      m_nGrowBy = nGrowBy;  // set aaa_primitive_new int_size

   }


   if(nNewSize == m_nSize)
   {

      return m_nSize;

   }

   if(nNewSize == 0)
   {

      // shrink to nothing
      if(m_pData != nullptr)
      {

         ALLOCATOR::destruct_count(m_pData, m_nSize  REFERENCING_DEBUGGING_COMMA_THIS);

         ALLOCATOR::_free(m_pData);

         m_pData = nullptr;

      }

      m_nSize = m_nMaxSize = 0;

   }
   else if(m_pData == nullptr)
   {

      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if(::comparison::gt(nNewSize, SIZE_T_MAX / sizeof(TYPE)))
         throw ::exception(error_no_memory);
      ASSERT(::comparison::lt(nNewSize, SIZE_T_MAX / sizeof(TYPE)));    // no overflow
#endif

      auto nAllocSize = maximum(nNewSize, m_nGrowBy);

#if MEMDLEAK  || defined(__MCRTDBG)

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_character())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strFile, ::get_task()->m_iLine);

         }
         else
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#else

         if (::get_task_object_debug().has_character())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__;

         }
         else
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__;

         }

#endif

      }
      else
      {

         m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

      }

#else

      m_pData = ALLOCATOR::alloc(nAllocSize);

#endif

      if (::is_null(ptype))
      {

         ALLOCATOR::construct_count(m_pData, nNewSize);

      }
      else
      {

         ALLOCATOR::copy_construct_count(m_pData, nNewSize, *ptype);

      }

      m_nSize = nNewSize;

      m_nMaxSize = nAllocSize;

   }
   else if(nNewSize <= m_nMaxSize)
   {

      if(nNewSize > m_nSize)
      {

         if (::is_null(ptype))
         {

            ALLOCATOR::construct_count(m_pData + m_nSize, nNewSize - m_nSize);

         }
         else
         {

            ALLOCATOR::copy_construct_count(m_pData + m_nSize, nNewSize - m_nSize, *ptype);

         }

      }
      else if(m_nSize > nNewSize)
      {

         ALLOCATOR::destruct_count(m_pData + nNewSize,m_nSize - nNewSize REFERENCING_DEBUGGING_COMMA_THIS);

      }

      m_nSize = nNewSize;

   }
   else
   {

   // otherwise, grow aaa_base_array
      nGrowBy = m_nGrowBy;

      if(nGrowBy == 0)
      {

         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = m_nSize;
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);

      }

      ::collection::count nNewMax;

      if(nNewSize < m_nMaxSize+ nGrowBy)
      {

         nNewMax = m_nMaxSize+ nGrowBy;  // granularity

      }
      else
      {

         nNewMax = nNewSize;  // no slush

      }

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
      {

         throw ::exception(error_bad_argument);

      }

#ifdef SIZE_T_MAX

      ASSERT(::comparison::lt(nNewMax, SIZE_T_MAX / sizeof(TYPE))); // no overflow

#endif

#if MEMDLEAK || defined(__MCRTDBG)

      TYPE* pNewData =  nullptr;

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_character())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, ::get_task()->m_strFile,::get_task()->m_iLine);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

         }

#else

         if (::get_task_object_debug().has_character())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__;

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__;

         }

#endif

      }
      else
      {

         pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

      }


#else

      TYPE* pNewData = ALLOCATOR::alloc(nNewMax);

#endif

      // copy aaa_primitive_new data from old
      ::safe_memory_copy(pNewData,(size_t)nNewMax * sizeof(TYPE),m_pData,(size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);

      if (nNewSize > m_nSize)
      {

         if (::is_null(ptype))
         {

            ALLOCATOR::construct_count(pNewData + m_nSize, nNewSize - m_nSize);

         }
         else
         {

            ALLOCATOR::copy_construct_count(pNewData + m_nSize, nNewSize - m_nSize, *ptype);

         }

      }

      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);

      m_pData = pNewData;

      m_nSize = nNewSize;

      m_nMaxSize = nNewMax;

   }

   return countOld;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::on_after_read()
{


}





template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
inline void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::set_at_grow(::collection::index nIndex, ARG_TYPE newElement, ::collection::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   m_pData[nIndex] = newElement;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
inline TYPE & base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::element_at_grow(::collection::index nIndex, ::collection::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   return m_pData[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
inline void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::set_each(ARG_TYPE element, ::collection::index first, ::collection::count in_count_out_last)
{

   prepare_first_in_count_last_out(first, in_count_out_last);

   for(::collection::index i = first; i <= in_count_out_last; i++)
   {

      m_pData[i] = element;

   }

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
   template < typename ITERATOR >
   inline void base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::erase(const ITERATOR & begin, const ITERATOR & last) { ::erase(*this, begin, last); }
