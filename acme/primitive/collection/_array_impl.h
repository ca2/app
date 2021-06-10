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
   return (::count) this->m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_count() const
{
   return (::count) this->m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_length() const
{
   return (::count) this->m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_size_in_bytes() const
{
   return (::count)this->m_nSize * sizeof(TYPE);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_byte_count() const
{
   return (::count) (this->m_nSize * sizeof(TYPE));
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
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_lower_bound(::index i) const
{
   return i < this->m_nSize ? i : -1;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_middle_index(::index iIndex) const
{
   return m_nSize / 2 + iIndex;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR > ::get_upper_bound(::index iIndex) const
{
   return this->size() + iIndex;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::bounds(::index i) const
{
   return i >= 0 && i < this->size();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::erase_all()
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
   erase_all();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::erase_last()
{
   ASSERT(this->size() > 0);
   erase_at(get_upper_bound());
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

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

   return get_data()[nIndex];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::get_at(::index nIndex) const
{

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

   return get_data()[nIndex];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR > ::set_at(::index nIndex, ARG_TYPE newElement)
{

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

   get_data()[nIndex] = newElement;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(::index nIndex) const
{

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

   return m_pData[nIndex];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(::index nIndex)
{

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

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

   auto nIndex = this->m_nSize;

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
template < container_type CONTAINER >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::add(const CONTAINER & src)
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

   ::sort::swap(m_pData[index1], m_pData[index2]);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::__swap(iterator it1, iterator it2)
{
   TYPE t = *it1;
   *it1 = *it2;
   *it2 = t;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR >  & array < TYPE, ARG_TYPE, ALLOCATOR > ::operator = (const array & src)
{

   if(&src != this)
   {

      copy(src);

   }

   return *this;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::matter * pobject, ::count nGrowBy) //:
{


}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(const array & a)
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
array < TYPE, ARG_TYPE, ALLOCATOR > :: array(enum_create_new, ::count n)
{

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

   this->erase_all(); // on_destruct_element is virtual and won't be available for array_base

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR > ::append(const array& src)
{
    // ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this == &src)
      __throw(error_invalid_argument);

   ::count nOldSize = this->m_nSize;
   this->allocate(this->m_nSize + src.m_nSize);
   CopyElements<TYPE>(&this->m_pData[nOldSize], src.m_pData, src.m_nSize);
   return nOldSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR >::copy(const array& src)
{

   ASSERT(this != &src);

   if(this != &src)
   {

      auto nSrcSize = src.m_nSize;

      this->allocate(nSrcSize);

      CopyElements<TYPE>(this->m_pData,src.m_pData, nSrcSize);

   }

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR > ::erase(const TYPE * begin, const TYPE * last)
{

   auto iStart = index_of(begin);

   auto iEnd = index_of(last);

   // iEnd exclusive
   return erase_at(iStart, iEnd - iStart);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
template < container_type CONTAINER >
inline array < TYPE, ARG_TYPE, ALLOCATOR > & array < TYPE, ARG_TYPE, ALLOCATOR > ::operator += (const CONTAINER & container)
{

   if(&container == this)
   {

      array < TYPE, ARG_TYPE, ALLOCATOR > aCopy(container);

      add(aCopy);

   }
   else
   {

      add(container);

   }

   return *this;

}


//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//template < container CONTAINER >
//inline array < TYPE, ARG_TYPE, ALLOCATOR >  array < TYPE, ARG_TYPE, ALLOCATOR > ::operator + (const CONTAINER & container) const
//{
//
//   array < TYPE, ARG_TYPE, ALLOCATOR >  aNew(*this);
//
//   aNew.add(container);
//
//   return aNew;
//
//}
//

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR > ::add_new(::count c)
{

   if (c <= 0)
   {

      __throw(error_invalid_argument);

   }

   auto end = this->m_nSize;

   this->set_size(end + c);

   return this->element_at(end);

}

//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR > ::add_new_at(int iIndex)
//{
//
//   this->make_room_at(iIndex);
//
//   return this->element_at(iIndex);
//
//}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR > ::add_new_at(::index iIndex, ::count nCount)
{

   this->make_room_at(iIndex, nCount);

   return this->element_at(iIndex);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR >::pop(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = element_at(i);

   this->erase_at(i);

   return t;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR >::pop_back(::index n)
{

   erase_at(this->get_upper_bound(n));

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

   this->erase_at(i);

   return t;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR >::takeFirst(::index i)
{

   TYPE t = element_at(i);

   this->erase_at(i);

   return t;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR >::takeLast(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = element_at(i);

   this->erase_at(i);

   return t;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array_base < TYPE, ARG_TYPE, ALLOCATOR >::array_base(TYPE * p, ::count c)
{

   m_nGrowBy = 0;
   m_pData = nullptr;
   m_nSize = 0;
   m_nMaxSize = 0;

   set_size(c);

   for (::index i = 0; i < c; i++)
   {

      element_at(i) = p[i];

   }

}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array_base < TYPE, ARG_TYPE, ALLOCATOR >::array_base(const array_base & array)
{

   m_nGrowBy = 0;
   m_pData = nullptr;
   m_nSize = 0;
   m_nMaxSize = 0;

   set_size(array.get_size());

   for (::index i = 0; i < array.get_size(); i++)
   {

      element_at(i) = array[i];

   }

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array_base < TYPE, ARG_TYPE, ALLOCATOR >::array_base(array_base && array) noexcept
{

   this->m_nGrowBy = array.m_nGrowBy;
   this->m_pData = array.m_pData;
   this->m_nSize = array.m_nSize;
   this->m_nMaxSize = array.m_nMaxSize;

   array.m_pData = nullptr;
   array.m_nSize = 0;
   array.m_nMaxSize = 0;

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


template < class TYPE, class ARG_TYPE , class ALLOCATOR >
template < typename VAR >
inline array_base < TYPE, ARG_TYPE, ALLOCATOR > & array_base < TYPE, ARG_TYPE, ALLOCATOR >::operator = (const payload_type < VAR > & a)
{

   ::count c = a.this_var()->array_get_count();

   for(::index i = 0; i < c; i++)
   {

      add((ARG_TYPE)a.this_var()->at(i));

   }

   return *this;

}



