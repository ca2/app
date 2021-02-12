#pragma once

//
// see collection_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_size() const
{
   return this->m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_count() const
{
   return this->m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_length() const
{
   return this->m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_size_in_bytes() const
{
   return this->m_nSize * sizeof(TYPE);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_byte_count() const
{
   return this->m_nSize * sizeof(TYPE);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::size() const
{
   return this->get_size();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::count() const
{
   return this->get_count();
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::length() const
{
   return this->get_length();
}

//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::is_empty(::count countMinimum) const
//{
//   return this->size() < countMinimum;
//}


//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::empty(::count countMinimum) const
//{
//   return is_empty(countMinimum);
//}

//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::isEmpty(::count countMinimum) const
//{
//   return empty(countMinimum);
//}

//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::has_elements(::count countMinimum) const
//{
//   return this->size() >= countMinimum;
//}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR > ::upper_bound(::index iIndex) const
{
   return (::index)this->size() + iIndex;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR > ::middle_index(::index iIndex) const
{
   return (::index) +iIndex;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_upper_bound(::index iIndex) const
{
   return this->size() + iIndex;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_middle_index(::index iIndex) const
{
   return this->size() / 2 + iIndex;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::bounds(::index i) const
{
   return i >= 0 && i < this->size();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::remove_all()
{
   return allocate(0, -1);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::set_size(::index nNewSize, ::count nGrowBy) // does not call default constructors on new items/elements
{
   return allocate(nNewSize, nGrowBy);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::clear()
{
   remove_all();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::remove_last()
{
   ASSERT(this->size() > 0);
   remove_at(get_upper_bound());
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::zero(::index iStart,::count c)
{
   if(c < 0)
   {
      c = get_size() - iStart;
   }
   ::zero(&m_pData[iStart],c * sizeof(TYPE));
}


























template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::get_at(::index nIndex)
{
   
   ASSERT(nIndex >= 0 && nIndex < __count(this->m_nSize));

   return get_data()[nIndex];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::get_at(::index nIndex) const
{

   ASSERT(nIndex >= 0 && nIndex < __count(this->m_nSize));

   return get_data()[nIndex];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR > ::set_at(::index nIndex, ARG_TYPE newElement)
{

   ASSERT(nIndex >= 0 && nIndex < __count(this->m_nSize));

   get_data()[nIndex] = newElement;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(::index nIndex) const
{

   ASSERT(nIndex >= 0 && nIndex < __count(this->m_nSize));

   return m_pData[nIndex];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(::index nIndex)
{

   ASSERT(nIndex >= 0 && nIndex < __count(this->m_nSize));

   return m_pData[nIndex];

}

//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::first(::index nIndex) const
//{
//   return this->element_at(nIndex);
//}
//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::first(::index nIndex)
//{
//   return this->element_at(nIndex);
//}
//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::last(::index i) const
//{
//   return this->element_at(this->get_upper_bound(i);
//}
//
//
//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::last(::index i)
//{
//   return this->element_at(this->get_upper_bound(i);
//}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE* array < TYPE, ARG_TYPE, ALLOCATOR > ::get_data() const
{
   return (const TYPE*)this->m_pData;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE* array < TYPE, ARG_TYPE, ALLOCATOR > ::get_data()
{
   return (TYPE*)this->m_pData;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::add_item(ARG_TYPE newElement)
{

   ::index nIndex = (::index_cast) __count(this->m_nSize);

   this->allocate(nIndex + 1);

   this->last() = newElement;

   return nIndex;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::add(ARG_TYPE newElement)
{

   return add_item(newElement);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::add(const array & src)
{
   return append(src);
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::append(ARG_TYPE newElement)
{
   return add(newElement);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR > ::operator[](::index i) const
{

   return m_pData[i];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR > ::operator[](::index i)
{

   return m_pData[i];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::__swap(::index index1, ::index index2)
{

   ::swap(m_pData[index1], m_pData[index2]);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::__swap(iterator it1, iterator it2)
{
   TYPE t = *it1;
   *it1 = *it2;
   *it2 = t;
}


//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::__swap(const_iterator it1, const_iterator it2)
//{
//   TYPE t = get_data()[it1.m_i];
//   get_data()[it1.m_i] = get_data()[it2.m_i];
//   get_data()[it2.m_i] = t;
//}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR >  & array < TYPE, ARG_TYPE, ALLOCATOR > ::operator = (const array & src)
{
   if(&src != this)
   {
      copy(src);
   }
   return *this;
}



// out-of-line functions

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::matter * pobject, ::count nGrowBy) //:
   //::matter(pobject)
{
//   this->m_nGrowBy = maximum(0, nGrowBy);
//   this->m_pData = nullptr;
//   __count(this->m_nSize) = this->m_nMaxSize = 0;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(const array & a) //:
//   matter(a)
{

   operator = (a);

}


template < class TYPE,class ARG_TYPE,class ALLOCATOR >
inline array < TYPE,ARG_TYPE,ALLOCATOR > ::array(::std::initializer_list < TYPE >  l)
{
   forallref(l)
   {
      add((ARG_TYPE) item);
   }
}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > :: array(e_create_new, ::count n)
{
//   m_nGrowBy = 32;
//   m_pData = nullptr;
//   this->size() = m_nMaxSize = 0;
   this->allocate(n);
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::count n, ARG_TYPE t)
{
   while (n > 0)
   {
      add(t);
      n--;
   }
}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::~array()
{
   this->remove_all(); // on_destruct_element is virtual and won't be available for array_base
}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::append(const array& src)
{
    // ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this == &src)
      __throw(invalid_argument_exception());

   ::count nOldSize = __count(this->m_nSize);
   this->allocate(__count(this->m_nSize) + __count(src.m_nSize));
   CopyElements<TYPE>(&this->m_pData[nOldSize], src.m_pData, __count(src.m_nSize));
   return nOldSize;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR >::copy(const array& src)
{

    // ASSERT_VALID(this);

   ASSERT(this != &src);

   if(this != &src)
   {
      
      auto nSrcSize = __count(src.m_nSize);
      
      this->allocate(nSrcSize);
      
      CopyElements<TYPE>(this->m_pData,src.m_pData, nSrcSize);

   }

}







//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//void array < TYPE, ARG_TYPE, ALLOCATOR > ::dump(dump_context & dumpcontext) const
//{
//
////   matter::dump(dumpcontext);
//
//   dumpcontext << "with ";
//
//   dumpcontext.write(__count(this->m_nSize));
//
//   dumpcontext << " elements";
//
//   if (dumpcontext.GetDepth() > 0)
//   {
//
//      dumpcontext << "\n";
//
//      dump_elements<TYPE>(dumpcontext, this->get_data(), (::count_cast) __count(this->m_nSize));
//
//   }
//
//   dumpcontext << "\n";
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//void array < TYPE, ARG_TYPE, ALLOCATOR > ::assert_valid() const
//{
//   
//   //matter::assert_valid();
//
//   if (this->m_pData == nullptr)
//   {
//      
//      ASSERT(__count(this->m_nSize) == 0);
//      ASSERT(this->m_nMaxSize == 0);
//
//   }
//   else
//   {
//      
//      ASSERT(__count(this->m_nSize) >= 0);
//      ASSERT(this->m_nMaxSize >= 0);
//      ASSERT(__count(this->m_nSize) <= this->m_nMaxSize);
//      ASSERT(__is_valid_address(this->m_pData, (::memsize_cast) this->m_nMaxSize * sizeof(TYPE)));
//
//   }
//
//}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline typename array_base < TYPE, ARG_TYPE, ALLOCATOR > ::iterator array_base < TYPE, ARG_TYPE, ALLOCATOR > ::erase(iterator pos)
{
   if(pos >= begin() && pos < end())
   {
      this->remove_at(pos - begin());
      return pos;
   }
   else
   {
      return this->end();
   }
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline typename  array_base < TYPE, ARG_TYPE, ALLOCATOR > ::iterator array_base < TYPE, ARG_TYPE, ALLOCATOR > ::erase(iterator begin, iterator last)
{
   if(begin >= m_pData && last < m_pData + this->size())
   {
      if(begin < m_pData + this->size())
      {
         ::count nCount = last - begin;
         remove_at(begin - m_pData, nCount);
         return begin;
      }
      else
      {
         return this->end();
      }
   }
   else
   {
      return this->end();
   }
}





template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR >  & array < TYPE, ARG_TYPE, ALLOCATOR > ::operator += (const array & a)
{

   if(&a == this)
   {
      array < TYPE, ARG_TYPE, ALLOCATOR >  aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR >  array < TYPE, ARG_TYPE, ALLOCATOR > ::operator + (const array & a) const
{
   array < TYPE, ARG_TYPE, ALLOCATOR >  aNew(*this);
   aNew += a;
   return a;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR > ::add_new()
{

   this->set_size(__count(this->m_nSize) + 1);

   return this->last();

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::add_new(::count count)
{

   this->set_size(__count(this->m_nSize) + count);

   return this->get_upper_bound();

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR >::pop(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = element_at(i);

   this->remove_at(i);

   return t;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR >::pop_back(::index n)
{

   remove_at(this->get_upper_bound(n));

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR >::push(ARG_TYPE newElement,::index n)
{
   return insert_at(this->get_upper_bound(n),newElement);
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR >::push_back(ARG_TYPE newElement,::index n)
{
   insert_at(this->get_upper_bound(n),newElement);
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR >::takeAt(::index i)
{

   TYPE t = element_at(i);

   this->remove_at(i);

   return t;

}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR >::takeFirst(::index i)
{

   TYPE t = element_at(i);

   this->remove_at(i);

   return t;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR >::takeLast(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = element_at(i);

   this->remove_at(i);

   return t;

}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::set_at_grow(::index nIndex, ARG_TYPE newElement, ::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= __count(this->m_nSize))
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   get_data()[nIndex] = newElement;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR > ::element_at_grow(::index nIndex, ::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= __count(this->m_nSize))
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   return get_data()[nIndex];

}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR >::array(array && a)
{

   this->m_nGrowBy = a.m_nGrowBy;
   this->m_pData = a.m_pData;
   this->m_nSize = a.m_nSize;
   this->m_nMaxSize = a.m_nMaxSize;

   a.m_pData = nullptr;
   a.m_nSize = 0;
   a.m_nMaxSize = 0;

}


template < class TYPE,class ARG_TYPE,class ALLOCATOR >
inline array < TYPE,ARG_TYPE,ALLOCATOR > & array < TYPE,ARG_TYPE,ALLOCATOR >::move(array && a)
{

   if(&a != this)
   {

      this->destroy();

      this->m_nGrowBy = a.m_nGrowBy;
      this->m_pData = a.m_pData;
      this->m_nSize = a.m_nSize;
      this->m_nMaxSize = a.m_nMaxSize;

      a.m_pData = nullptr;
      a.m_nSize = 0;
      a.m_nMaxSize = 0;

   }

   return *this;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR > & array < TYPE, ARG_TYPE, ALLOCATOR >::operator = (array && a)
{

   move(::move(a));

   return *this;

}



//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR >::element_at(::index nIndex) const
//{
//
//   return m_pData[nIndex];
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR >::element_at(::index nIndex)
//{
//
//   return m_pData[nIndex];
//
//}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR >::first(::index nIndex) const
{

   return this->element_at(nIndex);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR >::first(::index nIndex)
{
   return this->element_at(nIndex);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR >::last(::index i) const
{
   return element_at(this->get_upper_bound(i));
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR >::last(::index i)
{

   return element_at(this->get_upper_bound(i));

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR >::middle(::index i) const
{

   return element_at(this->get_middle_index(i));

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR >::middle(::index i)
{

   return element_at(this->get_middle_index(i));

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
void  array_base < TYPE, ARG_TYPE, ALLOCATOR >::set_all(const TYPE & t)
{

   for (::index i = 0; i < get_count(); i++)
   {

      m_pData[i] = t;

   }

}



