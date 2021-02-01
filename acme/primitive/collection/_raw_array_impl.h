#pragma once

//
// see collection_raw_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements

//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_size() const
//{
//   return m_nSize;
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_size_in_bytes() const
//{
//   return m_nSize * sizeof(TYPE);
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_count() const
//{
//   return this->get_size();
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_byte_count() const
//{
//   return this->get_size_in_bytes();
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::size() const
//{
//   return this->get_size();
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::count() const
//{
//   return this->get_count();
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline bool raw_array < TYPE, ARG_TYPE, ALLOCATOR >::is_empty(::count countMinimum) const
//{
//   return m_nSize < countMinimum;
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline bool raw_array < TYPE, ARG_TYPE, ALLOCATOR >::empty(::count countMinimum) const
//{
//   return m_nSize < countMinimum;
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline bool raw_array < TYPE, ARG_TYPE, ALLOCATOR >::has_elements(::count countMinimum) const
//{
//   return m_nSize >= countMinimum;
//}
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_upper_bound(::index i) const
//{
//   return m_nSize + ::index;
//}
//
template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::remove_all()
{
   return this->allocate(0, -1);
}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::
clear()
{
   remove_all();
}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::remove_last()
{

   this->remove_at(this->get_upper_bound());

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_at(::index nIndex)
{

   return get_data()[nIndex];
}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_at(::index nIndex) const
{

   return get_data()[nIndex];

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::set_at(::index nIndex, ARG_TYPE newElement)
{

   get_data()[nIndex] = newElement;

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE* raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_data() const
{

   return (const TYPE*)this->m_pData;

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE* raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_data()
{

   return (TYPE*)this->m_pData;

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::add(ARG_TYPE newElement)
{

   ::index nIndex = (::index_cast ) this->m_nSize;

   this->set_at_grow(nIndex, newElement);

   return nIndex;

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::add(const raw_array & src)
{

   return this->append(src);

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::add_new(::count count)
{

   this->allocate(this->size() + count);

   return this->get_upper_bound();

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & raw_array < TYPE, ARG_TYPE, ALLOCATOR >::add_new()
{

   this->allocate(this->size() + 1);

   return this->last();

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE raw_array < TYPE, ARG_TYPE, ALLOCATOR >::pop(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = this->element_at(i);

   this->remove_at(i);

   return t;

}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::pop_back(::index n)
{

   this->remove_at(this->get_upper_bound(n));

}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::push(ARG_TYPE newElement, ::index n)
{
   return insert_at(this->get_upper_bound(n), newElement);
}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::push_back(ARG_TYPE newElement, ::index n)
{
   insert_at(this->get_upper_bound(n), newElement);
}


//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline const TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR >::operator[](::index nIndex) const
//{
//
//   return this->element_at(nIndex);
//
//}
//
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE& raw_array < TYPE, ARG_TYPE, ALLOCATOR >::operator[](::index nIndex)
//{
//
//   return this->element_at(nIndex);
//
//}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::__swap(::index index1, ::index index2)
{
   TYPE t = get_data()[index1];
   get_data()[index1] = get_data()[index2];
   get_data()[index2] = t;
}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline raw_array < TYPE, ARG_TYPE, ALLOCATOR > & raw_array < TYPE, ARG_TYPE, ALLOCATOR >::operator = (const raw_array & src)
{
   if(&src != this)
   {
      this->copy(src);
   }
   return *this;
}



// out-of-line functions

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR >::raw_array(::matter * pobject)
   //:
   //::matter(pobject)
{

}


template<class TYPE,class ARG_TYPE,class ALLOCATOR >
inline raw_array < TYPE,ARG_TYPE,ALLOCATOR >::raw_array(::std::initializer_list < TYPE >  l)
{
   forallref(l)
   {
      add((ARG_TYPE) item);
   }
}



template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR >::raw_array(const raw_array <TYPE, ARG_TYPE, ALLOCATOR> & array):
   ARRAY_BASE(array)
{

}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE,ARG_TYPE,ALLOCATOR >::raw_array(raw_array <TYPE,ARG_TYPE,ALLOCATOR> && a) noexcept :
   ARRAY_BASE(::move(a))
{

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR >:: raw_array(::count n)
{
   this->allocate(n);
}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR >::raw_array(ARG_TYPE t, ::count n)
{
   insert_at(0, t, n);
}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR >::raw_array(TYPE * ptypea, ::count n)
{

   this->allocate(n);

   for(int i = 0; i < n; i++)
   {

      this->element_at(i) = ptypea[i];

   }

}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR >::~raw_array()
{

   this->destroy();

}

//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::destroy()
//{
//   if (m_pData != nullptr)
//   {
//      for( i32 i = 0; i < m_nSize; i++ )
//         destruct_element(m_pData + i)->~TYPE();
//      delete[] (byte*)m_pData;
//      m_pData     = nullptr;
//      m_nSize     = 0;
//      m_nMaxSize  = 0;
//   }
//
//}


//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::set_size(::count nNewSize, ::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::resize(::count nNewSize, ::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::allocate_in_bytes(::count nNewSize, ::count nGrowBy)
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

//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//::count raw_array < TYPE, ARG_TYPE, ALLOCATOR >::allocate(::count nNewSize, ::count nGrowBy)
//{
//   ::count countOld = get_count();
//   ASSERT_VALID(this);
//   ASSERT(nNewSize >= 0);
//
//   if(nNewSize < 0 )
//      __throw(invalid_argument_exception());
//
//   if (nGrowBy >= 0)
//      m_nGrowBy = nGrowBy;  // set new size_i32
//
//   if (nNewSize == 0)
//   {
//      // shrink to nothing
//      if (m_pData != nullptr)
//      {
////         for( i32 i = 0; i < m_nSize; i++ )
////            (m_pData + i)->~TYPE();
//         delete[] (byte*)m_pData;
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
//         __throw(memory_exception());
//      ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
//#endif
//      ::count nAllocSize = max(nNewSize, m_nGrowBy);
////#undef new
//      m_pData = (TYPE*) new byte[(size_t)nAllocSize * sizeof(TYPE)];
//      //__memset((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
////      for( ::index i = 0; i < nNewSize; i++ )
//  //       ::new( (void *)( m_pData + i ) ) TYPE;
////#define new ACME_NEW
//      m_nSize = nNewSize;
//      m_nMaxSize = nAllocSize;
//   }
//   else if (nNewSize <= m_nMaxSize)
//   {
//      // it fits
//      if (nNewSize > m_nSize)
//      {
//         // initialize the new elements
////         __memset((void *)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////         for( i32 i = 0; i < nNewSize-m_nSize; i++ )
////#undef new
////            ::new( (void *)( m_pData + m_nSize + i ) ) TYPE;
////#define new ACME_NEW
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
//         __throw(invalid_argument_exception());
//
//#ifdef SIZE_T_MAX
//      ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
//#undef new
//      TYPE* pNewData = (TYPE*) new byte[(size_t)nNewMax * sizeof(TYPE)];
//#define new ACME_NEW
//
//      // copy new data from old
//      ::acme::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
//         m_pData, (size_t)m_nSize * sizeof(TYPE));
//
//      // construct remaining elements
//      ASSERT(nNewSize > m_nSize);
////      __memset((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////      for( i32 i = 0; i < nNewSize-m_nSize; i++ )
////#undef new
////         ::new( (void *)( pNewData + m_nSize + i ) ) TYPE;
////#define new ACME_NEW
//      // get rid of old stuff (note: no destructors called)
//      delete[] (byte*)m_pData;
//      m_pData = pNewData;
//      m_nSize = nNewSize;
//      m_nMaxSize = nNewMax;
//   }
//   return countOld;
//}
//

//
//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::free_extra()
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
//         pNewData = (TYPE*) new byte[m_nSize * sizeof(TYPE)];
//         // copy new data from old
//         ::acme::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
//            m_pData, m_nSize * sizeof(TYPE));
//      }
//
//      // get rid of old stuff (note: no destructors called)
//      delete[] (byte*)m_pData;
//      m_pData = pNewData;
//      m_nMaxSize = m_nSize;
//   }
//}

//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//void array_base < TYPE, ARG_TYPE, ALLOCATOR >::set_at_grow(::index nIndex, ARG_TYPE newElement)
//{
//   //ASSERT_VALID(this);
//   //ASSERT(nIndex >= 0);
//
//   if(nIndex < 0)
//      __throw(invalid_argument_exception());
//
//   if (nIndex >= this->m_nSize)
//      this->allocate(nIndex+1, -1);
//   get_data()[nIndex] = newElement;
//}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE raw_array < TYPE, ARG_TYPE, ALLOCATOR >::get_at_grow(::index nIndex)
{

   return this->element_at_grow(nIndex);

}


//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE & raw_array < TYPE, ARG_TYPE, ALLOCATOR >::element_at_grow(::index nIndex)
//{
//   if (nIndex >= this->m_nSize)
//      this->allocate(nIndex+1, -1);
//   return get_data()[nIndex];
//}


template<class TYPE, class ARG_TYPE, class ALLOCATOR >
::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{

   return array_base < TYPE, ARG_TYPE, ALLOCATOR >::insert_at(nIndex, newElement,nCount);

}


//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::insert_at(::index nStartIndex, raw_array * pNewArray)
//{
//   ASSERT_VALID(this);
//   ASSERT(pNewArray != nullptr);
//   ASSERT_VALID(pNewArray);
//   ASSERT(nStartIndex >= 0);
//
//   if(pNewArray == nullptr || nStartIndex < 0)
//      __throw(invalid_argument_exception());
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


//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::dump(dump_context & dumpcontext) const
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
//      dump_elements<TYPE>(dumpcontext,get_data(), (::count_cast) this->m_nSize);
//
//   }
//
//   dumpcontext << "\n";
//
//}


//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//void raw_array < TYPE, ARG_TYPE, ALLOCATOR >::assert_valid() const
//{
//
//   matter::assert_valid();
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
//      ASSERT(__is_valid_address(this->m_pData, (::memsize_cast) this->m_nMaxSize * sizeof(TYPE)));
//
//   }
//
//}


//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//typename raw_array < TYPE, ARG_TYPE, ALLOCATOR >::iterator raw_array < TYPE, ARG_TYPE, ALLOCATOR >::erase(iterator pos)
//{
//   if(pos.m_parray == this)
//   {
//      this->remove_at(pos.m_i);
//      return iterator(pos.m_i, this);
//   }
//   else
//   {
//      return this->end();
//   }
//}

//template<class TYPE, class ARG_TYPE, class ALLOCATOR >
//typename  raw_array < TYPE, ARG_TYPE, ALLOCATOR >::iterator raw_array < TYPE, ARG_TYPE, ALLOCATOR >::erase(iterator begin, iterator last)
//{
//   if(begin.m_parray == this && last.m_parray == this)
//   {
//      if(begin.m_i >= 0 && begin.m_i < this->get_size())
//      {
//         ::count nCount = last.m_i - begin.m_i;
//         remove_at(begin.m_i, nCount);
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
template<class TYPE, class ARG_TYPE, class ALLOCATOR >
::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::raw_find_first(TYPE *point_i32, ::index find, ::index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(&this->element_at(find) == point_i32)
         return find;
   }
   return -1;
}
template<class TYPE, class ARG_TYPE, class ALLOCATOR >
::index raw_array < TYPE, ARG_TYPE, ALLOCATOR >::find_first(ARG_TYPE t, ::index ( * pfnCompare )(ARG_TYPE, ARG_TYPE), ::index find, ::index last) const

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




template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR > & raw_array < TYPE, ARG_TYPE, ALLOCATOR >::operator += (const raw_array & a)
{

   if(&a == this)
   {
      raw_array < TYPE, ARG_TYPE, ALLOCATOR > aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template<class TYPE, class ARG_TYPE, class ALLOCATOR >
raw_array < TYPE, ARG_TYPE, ALLOCATOR > raw_array < TYPE, ARG_TYPE, ALLOCATOR >::operator + (const raw_array & a) const
{
   raw_array < TYPE, ARG_TYPE, ALLOCATOR > aNew(*this);
   aNew += a;
   return a;
}








template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline raw_array < TYPE, ARG_TYPE, ALLOCATOR > & raw_array < TYPE, ARG_TYPE, ALLOCATOR >::operator =(raw_array && a)
{

   return move(::move(a));

}





template<class TYPE, class ARG_TYPE, class ALLOCATOR >
inline raw_array < TYPE, ARG_TYPE, ALLOCATOR > & raw_array < TYPE, ARG_TYPE, ALLOCATOR >::move(raw_array && a)
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













