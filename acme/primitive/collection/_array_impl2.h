#pragma once

//
// see collection_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_size() const
//{
//   return this->m_nSize;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_count() const
//{
//   return this->m_nSize;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_length() const
//{
//   return this->m_nSize;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_size_in_bytes() const
//{
//   return this->m_nSize * sizeof(TYPE);
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_byte_count() const
//{
//   return this->m_nSize * sizeof(TYPE);
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::size() const
//{
//   return this->get_size();
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::count() const
//{
//   return this->get_count();
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::length() const
//{
//   return this->get_length();
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::is_empty(::count countMinimum) const
//{
//   return this->size() < countMinimum;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::empty(::count countMinimum) const
//{
//   return is_empty(countMinimum);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::isEmpty(::count countMinimum) const
//{
//   return empty(countMinimum);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::has_elements(::count countMinimum) const
//{
//   return this->size() >= countMinimum;
//}
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::upper_bound(::index iIndex) const
//{
//   return (::index)this->size() + iIndex;
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::middle_index(::index iIndex) const
//{
//   return (::index) +iIndex;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_upper_bound(::index iIndex) const
//{
//   return this->size() + iIndex;
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_middle_index(::index iIndex) const
//{
//   return this->size() / 2 + iIndex;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::bounds(::index i) const
//{
//   return i >= 0 && i < this->size();
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::erase_all()
//{
//   return allocate(0, -1);
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::set_size(::index nNewSize, ::count nGrowBy) // does not call default constructors on memory_new items/elements
//{
//   return allocate(nNewSize, nGrowBy);
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::clear()
//{
//   erase_all();
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::erase_last()
//{
//   ASSERT(this->size() > 0);
//   erase_at(get_upper_bound());
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::zero(::index iStart,::count c)
//{
//   if(c < 0)
//   {
//      c = get_size() - iStart;
//   }
//   ::zero(&m_pData[iStart],c * sizeof(TYPE));
//}


























//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_at(::index nIndex)
//{
//
//   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
//
//   return get_data()[nIndex];
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_at(::index nIndex) const
//{
//
//   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
//
//   return get_data()[nIndex];
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::set_at(::index nIndex, ARG_TYPE newElement)
//{
//
//   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
//
//   get_data()[nIndex] = newElement;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::element_at(::index nIndex) const
//{
//
//   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
//
//   return m_pData[nIndex];
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::element_at(::index nIndex)
//{
//
//   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
//
//   return m_pData[nIndex];
//
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::first(::index nIndex) const
//{
//   return this->element_at(nIndex);
//}
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::first(::index nIndex)
//{
//   return this->element_at(nIndex);
//}
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::last(::index i) const
//{
//   return this->element_at(this->get_upper_bound(i);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::last(::index i)
//{
//   return this->element_at(this->get_upper_bound(i);
//}




//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE* array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_data() const
//{
//   return (const TYPE*)this->m_pData;
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE* array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::get_data()
//{
//   return (TYPE*)this->m_pData;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::add_item(ARG_TYPE newElement)
//{
//
//   ::index nIndex = (::index_cast) this->m_nSize;
//
//   this->allocate(nIndex + 1);
//
//   this->last() = newElement;
//
//   return nIndex;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::add(ARG_TYPE newElement)
//{
//
//   return add_item(newElement);
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::add(const array & src)
//{
//   return append(src);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::append(ARG_TYPE newElement)
//{
//   return add(newElement);
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::operator[](::index i) const
//{
//
//   return m_pData[i];
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::operator[](::index i)
//{
//
//   return m_pData[i];
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::__swap(::index index1, ::index index2)
//{
//
//   ::swap(m_pData[index1], m_pData[index2]);
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::__swap(iterator it1, iterator it2)
//{
//   TYPE t = *it1;
//   *it1 = *it2;
//   *it2 = t;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::__swap(const_iterator it1, const_iterator it2)
//{
//   TYPE t = get_data()[it1.m_i];
//   get_data()[it1.m_i] = get_data()[it2.m_i];
//   get_data()[it2.m_i] = t;
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >  & array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::operator = (const array & src)
//{
//   if(&src != this)
//   {
//      copy(src);
//   }
//   return *this;
//}



// out-of-line functions

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::array(::matter * pobject, ::count nGrowBy) //:
//   //::matter(pobject)
//{
////   this->m_nGrowBy = maximum(0, nGrowBy);
////   this->m_pData = nullptr;
////   this->m_nSize = this->m_nMaxSize = 0;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::array(const array & a) //:
////   matter(a)
//{
//
//   operator = (a);
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::array(::std::initializer_list < TYPE >  l)
//{
//   forallref(l)
//   {
//      add((ARG_TYPE) item);
//   }
//}




//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > :: array(e_create_new, ::count n)
//{
////   m_nGrowBy = 32;
////   m_pData = nullptr;
////   this->size() = m_nMaxSize = 0;
//   this->allocate(n);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::array(::count n, ARG_TYPE t)
//{
//   while (n > 0)
//   {
//      add(t);
//      n--;
//   }
//}



//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::~array()
//{
//   this->erase_all(); // on_destruct_element is virtual and won't be available for array_base
//}




//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::append(const array& src)
//{
//    // ASSERT_VALID(this);
//   ASSERT(this != &src);   // cannot append to itself
//
//   if(this == &src)
//      throw ::exception(error_bad_argument);
//
//   ::count nOldSize = this->m_nSize;
//   this->allocate(this->m_nSize) + __count(src.m_nSize);
//   CopyElements<TYPE>(&this->m_pData[nOldSize], src.m_pData, src.m_nSize);
//   return nOldSize;
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::copy(const array& src)
//{
//
//    // ASSERT_VALID(this);
//
//   ASSERT(this != &src);
//
//   if(this != &src)
//   {
//
//      auto nSrcSize = src.m_nSize;
//
//      this->allocate(nSrcSize);
//
//      CopyElements<TYPE>(this->m_pData,src.m_pData, nSrcSize);
//
//   }
//
//}







//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//void array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::dump(dump_context & dumpcontext) const
//{
//
////   matter::dump(dumpcontext);
//
//   dumpcontext << "with ";
//
//   dumpcontext.write(this->m_nSize);
//
//   dumpcontext << " elements";
//
//   if (dumpcontext.GetDepth() > 0)
//   {
//
//      dumpcontext << "\n";
//
//      dump_elements<TYPE>(dumpcontext, this->get_data(), this->m_nSize);
//
//   }
//
//   dumpcontext << "\n";
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//void array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::assert_ok() const
//{
//   
//   //matter::assert_ok();
//
//   if (this->m_pData == nullptr)
//   {
//      
//      ASSERT(this->m_nSize) == 0;
//      ASSERT(this->m_nMaxSize == 0);
//
//   }
//   else
//   {
//      
//      ASSERT(this->m_nSize) >= 0;
//      ASSERT(this->m_nMaxSize >= 0);
//      ASSERT(this->m_nSize) <= this->m_nMaxSize;
//      ASSERT(__is_valid_address(this->m_pData, (::memsize_cast) this->m_nMaxSize * sizeof(TYPE)));
//
//   }
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline typename array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::iterator array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::erase(iterator pos)
//{
//   if(pos >= begin() && pos < end())
//   {
//      this->erase_at(pos - begin());
//      return pos;
//   }
//   else
//   {
//      return this->end();
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline typename  array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::iterator array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::erase(iterator begin, iterator last)
//{
//   if(begin >= m_pData && last < m_pData + this->size())
//   {
//      if(begin < m_pData + this->size())
//      {
//         ::count nCount = last - begin;
//         erase_at(begin - m_pData, nCount);
//         return begin;
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





//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >  & array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::operator += (const array & a)
//{
//
//   if(&a == this)
//   {
//      array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >  aCopy(a);
//      add(aCopy);
//   }
//   else
//   {
//      add(a);
//   }
//   return *this;
//
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >  array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::operator + (const array & a) const
//{
//   array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >  aNew(*this);
//   aNew += a;
//   return a;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::add_new()
//{
//
//   this->set_size(this->m_nSize) + 1;
//
//   return this->last();
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::add_new(::count count)
//{
//
//   this->set_size(this->m_nSize) + count;
//
//   return this->get_upper_bound();
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::pop(::index n)
//{
//
//   ::index i = this->get_upper_bound(n);
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::pop_back(::index n)
//{
//
//   erase_at(this->get_upper_bound(n));
//
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::push(ARG_TYPE newElement,::index n)
//{
//   return insert_at(this->get_upper_bound(n),newElement);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::push_back(ARG_TYPE newElement,::index n)
//{
//   insert_at(this->get_upper_bound(n),newElement);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::takeAt(::index i)
//{
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::takeFirst(::index i)
//{
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::takeLast(::index n)
//{
//
//   ::index i = this->get_upper_bound(n);
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::set_at_grow(::index nIndex, ARG_TYPE newElement, ::count nGrowBy)
//{
//
//   ASSERT(nIndex >= 0);
//
//   if (nIndex >= this->m_nSize)
//   {
//
//      this->set_size(nIndex + 1, nGrowBy);
//
//   }
//
//   get_data()[nIndex] = newElement;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > ::element_at_grow(::index nIndex, ::count nGrowBy)
//{
//
//   ASSERT(nIndex >= 0);
//
//   if (nIndex >= this->m_nSize)
//   {
//
//      this->set_size(nIndex + 1, nGrowBy);
//
//   }
//
//   return get_data()[nIndex];
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::array(array && a)
//{
//
//   this->m_nGrowBy = a.m_nGrowBy;
//   this->m_pData = a.m_pData;
//   this->m_nSize = a.m_nSize;
//   this->m_nMaxSize = a.m_nMaxSize;
//
//   a.m_pData = nullptr;
//   a.m_nSize = 0;
//   a.m_nMaxSize = 0;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::move(array && a)
//{
//
//   if(&a != this)
//   {
//
//      this->destroy();
//
//      this->m_nGrowBy = a.m_nGrowBy;
//      this->m_pData = a.m_pData;
//      this->m_nSize = a.m_nSize;
//      this->m_nMaxSize = a.m_nMaxSize;
//
//      a.m_pData = nullptr;
//      a.m_nSize = 0;
//      a.m_nMaxSize = 0;
//
//   }
//
//   return *this;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::operator = (array && a)
//{
//
//   move(::move(a));
//
//   return *this;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::element_at(::index nIndex) const
//{
//
//   return m_pData[nIndex];
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::element_at(::index nIndex)
//{
//
//   return m_pData[nIndex];
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::first(::index nIndex) const
//{
//
//   return this->element_at(nIndex);
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::first(::index nIndex)
//{
//   return this->element_at(nIndex);
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::last(::index i) const
//{
//   return element_at(this->get_upper_bound(i));
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::last(::index i)
//{
//
//   return element_at(this->get_upper_bound(i));
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline const TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::middle(::index i) const
//{
//
//   return element_at(this->get_middle_index(i));
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::middle(::index i)
//{
//
//   return element_at(this->get_middle_index(i));
//
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//void  array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::set_all(const TYPE & t)
//{
//
//   for (::index i = 0; i < get_count(); i++)
//   {
//
//      m_pData[i] = t;
//
//   }
//
//}





template < typename T >
bool pointer_array < T > ::insert_unique_at(::index i, T * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
{

   if (i < 0 || i > this->get_size())
   {

      throw ::exception(error_bad_argument);

   }

   auto iFind = this->find_first(p);

   if (iFind < 0)
   {

      this->insert_at(i, p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

      return true;

   }

   if (iFind < i)
   {

      this->erase_at(iFind);

      this->insert_at(i - 1, p);

   }
   else if(iFind > i)
   {

      this->erase_at(iFind);

      this->insert_at(i, p);

   }

   return false;

}
