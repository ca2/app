#pragma once

//
// see collection_raw_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_size() const
//{
//   return m_nSize;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_size_in_bytes() const
//{
//   return m_nSize * sizeof(TYPE);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_count() const
//{
//   return this->get_size();
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_byte_count() const
//{
//   return this->get_size_in_bytes();
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::size() const
//{
//   return this->get_size();
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::count() const
//{
//   return this->get_count();
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline bool raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::is_empty(::count countMinimum) const
//{
//   return m_nSize < countMinimum;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline bool raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::empty(::count countMinimum) const
//{
//   return m_nSize < countMinimum;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline bool raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::has_elements(::count countMinimum) const
//{
//   return m_nSize >= countMinimum;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_upper_bound(::index i) const
//{
//   return m_nSize + ::index;
//}
//
template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase_all()
{
   return this->allocate(0, -1);
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::
clear()
{
   erase_all();
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase_last()
{

   this->erase_at(this->get_upper_bound());

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_at(::index nIndex)
{

   return get_data()[nIndex];
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_at(::index nIndex) const
{

   return get_data()[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::set_at(::index nIndex, ARG_TYPE newElement)
{

   get_data()[nIndex] = newElement;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE* raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_data() const
{

   return (const TYPE*)this->m_pData;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE* raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_data()
{

   return (TYPE*)this->m_pData;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::add(ARG_TYPE newElement)
{

   ::index nIndex = (::index_cast ) this->m_nSize;

   set_at_grow(nIndex, newElement);

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::add(const raw_array & src)
{

   return this->append(src);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::add_new(::count count)
{

   this->allocate(this->size() + count);

   return this->get_upper_bound();

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE & raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::add_new()
{

   this->allocate(this->size() + 1);

   return this->last();

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::pop(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = this->element_at(i);

   this->erase_at(i);

   return t;

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::pop_back(::index n)
{

   this->erase_at(this->get_upper_bound(n));

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::push(ARG_TYPE newElement, ::index n)
{
   return insert_at(this->get_upper_bound(n), newElement);
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::push_back(ARG_TYPE newElement, ::index n)
{
   insert_at(this->get_upper_bound(n), newElement);
}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline const TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator[](::index nIndex) const
//{
//
//   return this->element_at(nIndex);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator[](::index nIndex)
//{
//
//   return this->element_at(nIndex);
//
//}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::__swap(::index index1, ::index index2)
{
   TYPE t = get_data()[index1];
   get_data()[index1] = get_data()[index2];
   get_data()[index2] = t;
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator = (const raw_array & src)
{
   if(&src != this)
   {
      this->copy(src);
   }
   return *this;
}



// out-of-line functions

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::raw_array(::particle * pparticle) 
   //:
   //::matter(pparticle)
{

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::raw_array(::std::initializer_list < TYPE >  l)
{
   forallref(l)
   {
      add((ARG_TYPE) item);
   }
}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::raw_array(const raw_array <TYPE, ARG_TYPE, ALLOCATOR> & a)// :
   // matter(a.get_app())
{
   ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator = (a);
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::raw_array(raw_array <TYPE,ARG_TYPE,ALLOCATOR> && a) //:
//   matter(a.get_app())
{

   this->m_nGrowBy = a.m_nGrowBy;
   this->m_pData = a.m_pData;
   this->m_nSize = a.m_nSize;
   this->m_nMaxSize = a.m_nMaxSize;

   //a.m_nGrowBy = 0;
   a.m_pData = nullptr;
   //a.m_nSize = 0;
   //a.m_nMaxSize = 0;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >:: raw_array(::count n)
{
   this->allocate(n);
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::raw_array(ARG_TYPE t, ::count n)
{
   insert_at(0, t, n);
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::raw_array(TYPE * ptypea, ::count n)
{

   this->allocate(n);

   for(int i = 0; i < n; i++)
   {

      this->element_at(i) = ptypea[i];

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::~raw_array()
{

   this->destroy();

}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::destroy()
//{
//   if (m_pData != nullptr)
//   {
//      for( i32 i = 0; i < m_nSize; i++ )
//         destruct_element(m_pData + i)->~TYPE();
//      delete[] (::u8*)m_pData;
//      m_pData     = nullptr;
//      m_nSize     = 0;
//      m_nMaxSize  = 0;
//   }
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::set_size(::count nNewSize, ::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::resize(::count nNewSize, ::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::allocate_in_bytes(::count nNewSize, ::count nGrowBy)
//{
//   if(nGrowBy < 0)
//   {
//      return allocate(nNewSize / sizeof(TYPE), -1);
//   }
//   else
//   {
//      return allocate(nNewSize / sizeof(TYPE), nGrowBy / sizeof(TYPE));
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::allocate(::count nNewSize, ::count nGrowBy)
//{
//   ::count countOld = get_count();
//   ASSERT_VALID(this);
//   ASSERT(nNewSize >= 0);
//
//   if(nNewSize < 0 )
//      throw ::exception(error_bad_argument);
//
//   if (nGrowBy >= 0)
//      m_nGrowBy = nGrowBy;  // set memory_new size_i32
//
//   if (nNewSize == 0)
//   {
//      // shrink to nothing
//      if (m_pData != nullptr)
//      {
////         for( i32 i = 0; i < m_nSize; i++ )
////            (m_pData + i)->~TYPE();
//         delete[] (::u8*)m_pData;
//         m_pData = nullptr;
//      }
//      m_nSize = m_nMaxSize = 0;
//   }
//   else if (m_pData == nullptr)
//   {
//      // create buffer big enough to hold number of requested elements or
//      // m_nGrowBy elements, whichever is larger.
//#ifdef SIZE_T_MAX
//      if(nNewSize > SIZE_T_MAX/sizeof(TYPE))
//         throw ::exception(error_no_memory);
//      ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
//#endif
//      ::count nAllocSize = maximum(nNewSize, m_nGrowBy);
////
//      m_pData = (TYPE*) memory_new ::u8[(size_t)nAllocSize * sizeof(TYPE)];
//      //memory_set((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
////      for( ::index i = 0; i < nNewSize; i++ )
//  //       ::memory_new( (void *)( m_pData + i ) ) TYPE;
//////#define memory_new ACME_NEW
//      m_nSize = nNewSize;
//      m_nMaxSize = nAllocSize;
//   }
//   else if (nNewSize <= m_nMaxSize)
//   {
//      // it fits
//      if (nNewSize > m_nSize)
//      {
//         // initialize the memory_new elements
////         memory_set((void *)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////         for( i32 i = 0; i < nNewSize-m_nSize; i++ )
////
////            ::memory_new( (void *)( m_pData + m_nSize + i ) ) TYPE;
//////#define memory_new ACME_NEW
//      }
//      else if (m_nSize > nNewSize)
//      {
//         // destroy the old elements
////         for( i32 i = 0; i < m_nSize-nNewSize; i++ )
//  //          (m_pData + nNewSize + i)->~TYPE();
//      }
//      m_nSize = nNewSize;
//   }
//   else
//   {
//      // otherwise, grow aaa_base_array
//      nGrowBy = m_nGrowBy;
//      if (nGrowBy == 0)
//      {
//         // heuristically determine growth when nGrowBy == 0
//         //  (this avoids heap fragmentation in many situations)
//         nGrowBy = m_nSize / 8;
//         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
//      }
//      ::count nNewMax;
//      if (nNewSize < m_nMaxSize + nGrowBy)
//         nNewMax = m_nMaxSize + nGrowBy;  // granularity
//      else
//         nNewMax = nNewSize;  // no slush
//
//      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
//
//      if(nNewMax  < m_nMaxSize)
//         throw ::exception(error_bad_argument);
//
//#ifdef SIZE_T_MAX
//      ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
//
//      TYPE* pNewData = (TYPE*) memory_new ::u8[(size_t)nNewMax * sizeof(TYPE)];
////#define memory_new ACME_NEW
//
//      // copy memory_new data from old
//      ::acme::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
//         m_pData, (size_t)m_nSize * sizeof(TYPE));
//
//      // construct remaining elements
//      ASSERT(nNewSize > m_nSize);
////      memory_set((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////      for( i32 i = 0; i < nNewSize-m_nSize; i++ )
////
////         ::memory_new( (void *)( pNewData + m_nSize + i ) ) TYPE;
//////#define memory_new ACME_NEW
//      // get rid of old stuff (note: no destructors called)
//      delete[] (::u8*)m_pData;
//      m_pData = pNewData;
//      m_nSize = nNewSize;
//      m_nMaxSize = nNewMax;
//   }
//   return countOld;
//}
//

//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::free_extra()
//{
//   ASSERT_VALID(this);
//
//   if (m_nSize != m_nMaxSize)
//   {
//      // shrink to desired size_i32
//#ifdef SIZE_T_MAX
//      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
//      TYPE* pNewData = nullptr;
//      if (m_nSize != 0)
//      {
//         pNewData = (TYPE*) memory_new ::u8[m_nSize * sizeof(TYPE)];
//         // copy memory_new data from old
//         ::acme::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
//            m_pData, m_nSize * sizeof(TYPE));
//      }
//
//      // get rid of old stuff (note: no destructors called)
//      delete[] (::u8*)m_pData;
//      m_pData = pNewData;
//      m_nMaxSize = m_nSize;
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::set_at_grow(::index nIndex, ARG_TYPE newElement)
//{
//   //ASSERT_VALID(this);
//   //ASSERT(nIndex >= 0);
//
//   if(nIndex < 0)
//      throw ::exception(error_bad_argument);
//
//   if (nIndex >= this->m_nSize)
//      this->allocate(nIndex+1, -1);
//   get_data()[nIndex] = newElement;
//}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::get_at_grow(::index nIndex)
{
   return element_at_grow(nIndex);
}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline TYPE & raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::element_at_grow(::index nIndex)
//{
//   if (nIndex >= this->m_nSize)
//      this->allocate(nIndex+1, -1);
//   return get_data()[nIndex];
//}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{

   return array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::insert_at(nIndex, newElement,nCount);

}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::insert_at(::index nStartIndex, raw_array * pNewArray)
//{
//   ASSERT_VALID(this);
//   ASSERT(pNewArray != nullptr);
//   ASSERT_VALID(pNewArray);
//   ASSERT(nStartIndex >= 0);
//
//   if(pNewArray == nullptr || nStartIndex < 0)
//      throw ::exception(error_bad_argument);
//
//   if (pNewArray->get_size() > 0)
//   {
//      insert_at(nStartIndex, pNewArray->element_at(0), pNewArray->get_size());
//      for (::index i = 1; i < pNewArray->get_size(); i++)
//         insert_at(nStartIndex + i, pNewArray->element_at(i));
//   }
//
//   return nStartIndex;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::dump(dump_context & dumpcontext) const
//{
//
//   matter::dump(dumpcontext);
//
//   dumpcontext << "with " << this->m_nSize << " elements";
//
//   if (dumpcontext.GetDepth() > 0)
//   {
//
//      dumpcontext << "\n";
//
//      dump_elements<TYPE>(dumpcontext,get_data(), this->m_nSize);
//
//   }
//
//   dumpcontext << "\n";
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::assert_ok() const
//{
//
//   matter::assert_ok();
//
//
//   if (get_data() == nullptr)
//   {
//
//      ASSERT(this->m_nSize == 0);
//      ASSERT(this->m_nMaxSize >= 0);
//
//   }
//   else
//   {
//
//      ASSERT(this->m_nSize >= 0);
//      ASSERT(this->m_nMaxSize >= 0);
//      ASSERT(this->m_nSize <= this->m_nMaxSize);
//      ASSERT(is_memory_segment_ok(this->m_pData, (::memsize_cast) this->m_nMaxSize * sizeof(TYPE)));
//
//   }
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//typename raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::iterator raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase(iterator pos)
//{
//   if(pos.m_parray == this)
//   {
//      this->erase_at(pos.m_i);
//      return iterator(pos.m_i, this);
//   }
//   else
//   {
//      return this->end();
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//typename  raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::iterator raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase(iterator begin, iterator last)
//{
//   if(begin.m_parray == this && last.m_parray == this)
//   {
//      if(begin.m_i >= 0 && begin.m_i < this->get_size())
//      {
//         ::count nCount = last.m_i - begin.m_i;
//         erase_at(begin.m_i, nCount);
//         return iterator(begin.m_i, this);
//      }
//      else
//      {
//         return this->end();
//      }
//   }
//   else
//   {
//      return this->end();
//   }
//}
//
//
template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::raw_find_first(TYPE *point, ::index find, ::index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(&this->element_at(find) == point)
         return find;
   }
   return -1;
}
template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::find_first(ARG_TYPE t, ::index ( * pfnCompare )(ARG_TYPE, ARG_TYPE), ::index find, ::index last) const

{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(pfnCompare((ARG_TYPE)this->element_at(find), (ARG_TYPE)t) == 0)

         return find;
   }
   return -1;
}




template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator += (const raw_array & a)
{

   if(&a == this)
   {
      raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator + (const raw_array & a) const
{
   raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > aNew(*this);
   aNew += a;
   return a;
}








template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator =(raw_array && a)
{

   return transfer(::transfer(a));

}





template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::transfer(raw_array && a)
{

   if (&a != this)
   {
      this->destroy();

      this->m_nGrowBy = a.m_nGrowBy;
      this->m_pData = a.m_pData;
      this->m_nSize = a.m_nSize;
      this->m_nMaxSize = a.m_nMaxSize;

      a.m_pData = nullptr;

   }

   return *this;

}













