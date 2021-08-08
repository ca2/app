


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::array_base()
{

   m_nGrowBy = 0;
   m_pData = nullptr;
   m_nSize = 0;
   m_nMaxSize = 0;

}




template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::~array_base ()
{

   if (m_pData != nullptr)
   {

      destroy();

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::resize(::count nNewSize, ::count nGrowBy)
{

   return allocate(nNewSize,nGrowBy);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::allocate_in_bytes(::count nNewSize,::count nGrowBy)
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


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::erase_at(::index nIndex,::count nCount)
{

   //ASSERT_VALID(this);

   ::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      __throw(error_invalid_argument);

   }

   ::count nMoveCount = m_nSize - (nUpperBound);

   ALLOCATOR::destruct_count(m_pData + nIndex, nCount OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   if(nMoveCount)
   {
      ::acme::memmove_s(m_pData + nIndex,(size_t)nMoveCount * sizeof(TYPE),m_pData + nUpperBound,(size_t)nMoveCount * sizeof(TYPE));
   }

   m_nSize -= nCount;

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::erase_item(TYPE * p)
{

   return erase_at(p - m_pData);

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::free_extra()
{

   if(m_nSize != m_nMaxSize)
   {
      // shrink to desired size_i32
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
            if (::get_task()->m_strFile.has_char())
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

         if (::get_task()->m_strDebug.has_char())
         {

            pNewData = ALLOCATOR::alloc(m_nSize, ::get_task()->m_strDebug, 0);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(m_nSize, __FILE__, __LINE__);

         }

#endif

#else

         pNewData = ALLOCATOR::alloc(m_nSize);

#endif      // copy new data from old

         // copy new data from old
         ::acme::memcpy_s(pNewData, (size_t)m_nSize * sizeof(TYPE),m_pData, (size_t)m_nSize * sizeof(TYPE));

      }

      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);

      m_pData = pNewData;

      m_nMaxSize = m_nSize;

   }

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::e_status array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::destroy()
{

   auto estatus = ::matter::destroy();

   if(m_pData != nullptr)
   {

      ALLOCATOR::destruct_count(m_pData, m_nSize OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      ALLOCATOR::_free(m_pData);

      m_pData     = nullptr;
      m_nSize     = 0;
      m_nMaxSize  = 0;

   }

   return estatus;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::insert_at(::index nIndex,const TYPE & newElement,::count nCount /*=1*/)
{

   ::index nIndexParam = make_room_at(nIndex, nCount);

   while(nCount--)
   {

      ALLOCATOR::copy(m_pData + nIndex, &newElement);

      nIndex++;

   }

   return nIndexParam;

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::make_room_at(::index nIndex, ::count nCount /*=1*/)
{

   ASSERT(nIndex >= 0);    // will expand to meet need

   if(nCount <= 0)
      return -1;

   if(nIndex < 0)
      __throw(error_invalid_argument);

   if(nIndex >= m_nSize)
   {

      // adding after the end of the array
      set_size(nIndex + nCount,-1);   // grow so nIndex is valid

   }
   else
   {

      // inserting in the middle of the array
      ::count nOldSize = (::count) m_nSize;

      set_size((::count) m_nSize + nCount,-1);  // grow it to new size_i32
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::acme::memmove_s(m_pData + nIndex + nCount,(size_t) ((nOldSize - nIndex) * sizeof(TYPE)),m_pData + nIndex,(size_t)((nOldSize - nIndex) * sizeof(TYPE)));

      ::zero(m_pData + nIndex, nCount* sizeof(TYPE));

      ALLOCATOR::construct_count(m_pData + nIndex,nCount);

   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   return nIndex;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::append(const array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & src)
{

   ::count nOldSize = m_nSize;

   ::count nSrcSize = src.m_nSize;   // to enable to append to itself

   allocate(nOldSize + nSrcSize);

   ALLOCATOR::copy_count(m_pData + nOldSize, src.m_pData, nSrcSize);

   return nOldSize;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::copy(const array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & src)
{

   if(this == &src)
   {

      return;

   }

   ::count nSrcSize = src.m_nSize;

   allocate(nSrcSize);

   ALLOCATOR::copy_count(m_pData,src.m_pData, nSrcSize);

}



// take in accptr that _001RemoveIndexes machine
// the ::index raw_array by sorting it and returning
// only the indexes that could be erased
// without indexes duplicates
template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::_001RemoveIndexes(index_array & ia)
{

   // sort
   ::sort::quick_sort(ia,true);

   ::index i = ia.get_upper_bound();

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


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::erase_indexes(const index_array & ia)
{


   // erase indexes
   for(::index i = ia.get_upper_bound(); i >= 0; i--)
   {

      erase_at(ia[i]);

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::erase_descending_indexes(const index_array & ia)
{

   for(::index i = 0; i < ia.get_count(); i++)
   {

      erase_at(ia[i]);

   }

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::insert_at(::index nIndex,array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > * pNewArray)
{

   ASSERT(pNewArray != nullptr);
   ASSERT(nIndex >= 0);    // will expand to meet need

   ::count nCount = pNewArray->get_size();

   if (nCount <= 0)
      return -1;

   if (nIndex < 0)
      __throw(error_invalid_argument);

   if (nIndex >= m_nSize)
   {

      // adding after the end of the array
      set_size(nIndex + nCount, -1);   // grow so nIndex is valid

   }
   else
   {

      // inserting in the middle of the array
      ::count nOldSize = (::count) m_nSize;

      set_size((::count) (m_nSize + nCount), -1);  // grow it to new size_i32
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::acme::memmove_s(m_pData + nIndex + nCount, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)), m_pData + nIndex, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)));

      ::zero(m_pData + nIndex, nCount* sizeof(TYPE));

      ALLOCATOR::construct_count(m_pData + nIndex, nCount);

   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   ::index nIndexParam = nIndex;

   ::index i = 0;

   while (nCount--)
   {

      ALLOCATOR::copy(m_pData + nIndex, pNewArray->m_pData + i);

      nIndex++;

   }

   return nIndexParam;


}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::pick_at(::index nIndex)
{

   ::count nCount = 1;

   ::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      __throw(error_invalid_argument);

   }

   ::count nMoveCount = m_nSize - (nUpperBound);

   auto t = m_pData[nIndex];

   ALLOCATOR::destruct_count(m_pData + nIndex, nCount OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   if (nMoveCount)
   {

      ::acme::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE), m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));

   }

   m_nSize -= nCount;

   return ::move(t);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::pick_at(::index nIndex, ::count nCount)
{

   //ASSERT_VALID(this);

   ::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      __throw(error_invalid_argument);

   }

   ::count nMoveCount = m_nSize - (nUpperBound);

   array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > a(m_pData + nIndex, (size_t)nMoveCount);

   ALLOCATOR::destruct_count(m_pData + nIndex, nCount OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   if (nMoveCount)
   {

      ::acme::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE), m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));

   }

   m_nSize -= nCount;

   return a;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::set_raw_size(::count nNewSize,::count nGrowBy)
{

   ::count countOld = get_count();

   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
      __throw(error_invalid_argument);

   if(nGrowBy >= 0)
      m_nGrowBy = nGrowBy;  // set new size_i32

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
         __throw(error_no_memory);
      ASSERT(nNewSize <= SIZE_T_MAX / sizeof(TYPE));    // no overflow
#endif
      ::count nAllocSize = (::count) maximum(nNewSize, m_nGrowBy);
#if defined(__MCRTDBG) || MEMDLEAK
      if (::get_task() != nullptr)
      {
#if defined(MEMDLEAK)

         if (::get_task()->m_strFile.has_char())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strFile, 0);

         }
         else
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#else

         if (::get_task()->m_strDebug.has_char())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strDebug, ::get_task()->m_iLine);

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
      nGrowBy = (::count) m_nGrowBy;
      if(nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = (::count) m_nSize;
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
      }
      ::count nNewMax;
      if(nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = (::count) (m_nMaxSize + nGrowBy);  // granularity
      else
         nNewMax = nNewSize;  // no slush

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
         __throw(error_invalid_argument);

#ifdef SIZE_T_MAX
      ASSERT(nNewMax <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
#endif
      TYPE * pNewData;
#if defined(__MCRTDBG) || MEMDLEAK
#ifdef __MCRTDBG

      if (::get_task() != nullptr)
      {

         if (::get_task()->m_strFile.has_char())
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

      if (::get_task()->m_strDebug.has_char())
      {

         pNewData = ALLOCATOR::alloc(nNewMax, ::get_task()->m_strDebug, ::get_task()->m_iLine);

      }
      else
      {

         pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

      }

#endif

#else

      pNewData = ALLOCATOR::alloc(nNewMax);

#endif      // copy new data from old

      ::acme::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),m_pData,(size_t)m_nSize * sizeof(TYPE));

      ///for(i32 i = 0; i < nNewSize - m_nSize; i++)
      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);

      m_pData = pNewData;

      m_nSize = nNewSize;

      m_nMaxSize = nNewMax;

   }

   return countOld;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::allocate(::count nNewSize,::count nGrowBy)
{

   ::count countOld = get_count();

   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
   {

      __throw(error_invalid_argument);

   }

   if(nGrowBy >= 0)
   {

      m_nGrowBy = nGrowBy;  // set new size_i32

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

         ALLOCATOR::destruct_count(m_pData, m_nSize  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

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
         __throw(error_no_memory);
      ASSERT(::comparison::lt(nNewSize, SIZE_T_MAX / sizeof(TYPE)));    // no overflow
#endif

      auto nAllocSize = maximum(nNewSize, m_nGrowBy);

#if MEMDLEAK  || defined(__MCRTDBG)

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_char())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strFile, ::get_task()->m_iLine);

         }
         else
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#else

         if (::get_task()->m_strDebug.has_char())
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, "thread://" + demangle(typeid(*::get_task()).name()) + ", " + ::get_task()->m_strDebug + ", " + string(__FILE__), __LINE__);

         }
         else
         {

            m_pData = ALLOCATOR::alloc(nAllocSize, "thread://" + demangle(typeid(*::get_task()).name()) + ", " + string(__FILE__), __LINE__);

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

      ALLOCATOR::construct_count(m_pData,nNewSize);

      m_nSize = nNewSize;

      m_nMaxSize = nAllocSize;

   }
   else if(nNewSize <= m_nMaxSize)
   {

      if(nNewSize > m_nSize)
      {

         ALLOCATOR::construct_count(m_pData + m_nSize,nNewSize - m_nSize);

      }
      else if(m_nSize > nNewSize)
      {

         ALLOCATOR::destruct_count(m_pData + nNewSize,m_nSize - nNewSize OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

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

      ::count nNewMax;

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

         __throw(error_invalid_argument);

      }

#ifdef SIZE_T_MAX

      ASSERT(::comparison::lt(nNewMax, SIZE_T_MAX / sizeof(TYPE))); // no overflow

#endif

#if MEMDLEAK || defined(__MCRTDBG)

      TYPE* pNewData =  nullptr;

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_char())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, ::get_task()->m_strFile,::get_task()->m_iLine);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

         }

#else

         if (::get_task()->m_strDebug.has_char())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, "thread://" + demangle(typeid(*::get_task()).name()) + ", " + ::get_task()->m_strDebug + ", " + string(__FILE__), __LINE__);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, "thread://" + demangle(typeid(*::get_task()).name()) + ", " + string(__FILE__), __LINE__);

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

      // copy new data from old
      ::acme::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),m_pData,(size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);

      if (nNewSize > m_nSize)
      {

         ALLOCATOR::construct_count(pNewData + m_nSize, nNewSize - m_nSize);

      }

      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);

      m_pData = pNewData;

      m_nSize = nNewSize;

      m_nMaxSize = nNewMax;

   }

   return countOld;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::on_after_read()
{


}





template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::set_at_grow(::index nIndex, ARG_TYPE newElement, ::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   m_pData[nIndex] = newElement;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::element_at_grow(::index nIndex, ::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   return m_pData[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
   template < typename ITERATOR >
   inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::erase(const ITERATOR & begin, const ITERATOR & last) { ::erase(*this, begin, last); }
