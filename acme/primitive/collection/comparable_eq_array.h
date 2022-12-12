#pragma once


#include "acme/primitive/comparison/equals.h"


template < class TYPE, class ARG_TYPE, class ARRAY_TYPE >
class comparable_eq_array:
   public comparable_eq_range < ARRAY_TYPE >
{
public:


   using BASE_RANGE = comparable_eq_range < ARRAY_TYPE >;

   using BASE_ARRAY = ARRAY_TYPE;

   using CONST_RAW_RANGE = BASE_ARRAY::CONST_RAW_RANGE;

   using iterator = ARRAY_TYPE::iterator;
   using const_iterator = ARRAY_TYPE::const_iterator;
   

   comparable_eq_array() {}
   comparable_eq_array(::std::initializer_list < TYPE > initializer_list) { this->add_initializer_list(initializer_list); }
   comparable_eq_array(const comparable_eq_array & array) : BASE_RANGE(array) {}
   comparable_eq_array(comparable_eq_array && array) noexcept : BASE_RANGE(::move(array)) { }
   comparable_eq_array(::range < const_iterator > constrange) : BASE_RANGE(constrange) {}
   template < primitive_integral INTEGRAL >
   comparable_eq_array(const_iterator begin, INTEGRAL count, bool bNullTerminated = false) : BASE_RANGE(begin, count, bNullTerminated) {}
   comparable_eq_array(const_iterator begin, const_iterator end, bool bNullTerminated = false) : BASE_RANGE(begin, end, bNullTerminated) {}
   comparable_eq_array(const_iterator begin) : BASE_RANGE(begin, span_zero_item(begin), true) {}

   
   ::index find_first(ARG_TYPE t) const;
   ::index find_first(ARG_TYPE t, ::index find, ::index last = -1) const;
   ::index find_last(ARG_TYPE t) const;
   ::index find_last_not(ARG_TYPE t) const;
   ::count get_count() const;
   ::count get_count(ARG_TYPE t, ::index start = 0, ::index last = -1, ::count countMax = -1) const;
   //bool has(ARG_TYPE t) const { return contains(t); }
   bool contains(ARG_TYPE t) const;
   bool has(ARG_TYPE t) const { return contains(t); }
   bool contains(ARG_TYPE t, ::index start, ::index last = -1, ::count countMin = 1, ::count countMax = -1) const;
   bool contains(comparable_eq_array & a, ::count cMinCount = -1) const
   {
      if(cMinCount < 0)
      {
         cMinCount += a.get_count() + 1;
      }
      for(::index i = 0; cMinCount > 0 && i < a.get_count(); i++)
      {
         if(!this->contains(a[i]))
            return false;
         cMinCount--;
      }
      return true;
   }
   
   
   using BASE_ARRAY::erase_last;
   ::index erase_last(ARG_TYPE t);
   ::index erase_first(ARG_TYPE t);
   ::index erase_first(ARG_TYPE t, ::index find, ::index last = -1);
   ::count erase(ARG_TYPE t);
   ::count erase(ARG_TYPE t, ::index find, ::index last = -1, ::count countMin = 0, ::count countMax = -1);
   ::count erase_array(const comparable_eq_array & a);


   bool add_unique(ARG_TYPE t);
   ::count add_unique(const ARRAY_TYPE & a);
   TYPE & insert_unique(ARG_TYPE t);


   bool insert_unique_at(::index i, ARG_TYPE t);

   ::count add_erase(bool bAdd, ARG_TYPE t);


   // set
   void merge(const comparable_eq_array & a);
   void intersect(const comparable_eq_array & a);

   // set operators
   comparable_eq_array & operator -= (const TYPE & t);
   comparable_eq_array & operator &= (const comparable_eq_array & a);
   comparable_eq_array & operator -= (const comparable_eq_array & a);
   comparable_eq_array& operator |= (const comparable_eq_array & a);

   comparable_eq_array operator -(const comparable_eq_array & a) const;


   using ARRAY_TYPE::operator =;
   comparable_eq_array & operator = (const comparable_eq_array & array)
   {
      
      BASE_ARRAY::operator =(array);
      
      return *this;
      
   }
   
   
   comparable_eq_array & operator = (comparable_eq_array && array)
   {
      
      move(::move(array));
      
      return *this;
      
   }
   
   
   comparable_eq_array & move(comparable_eq_array && array)
   {
      
      BASE_ARRAY::move(::move(array));
      
      return *this;
      
   }

   
   using BASE_ARRAY::operator +=;


   TYPE get_next(ARG_TYPE t)
   {

      auto iFind = this->find_first(t);

      if (this->is_empty())
      {

         return TYPE();

      }

      if (iFind < 0)
      {

         return this->first();

      }

      return this->operator % (iFind + 1);

   }

   using BASE_ARRAY::equals;

   bool equals(CONST_RAW_RANGE a) const
   {

      return BASE_ARRAY::equals(a, ::comparison::comparison < TYPE >());

   }


   bool operator ==(CONST_RAW_RANGE a) const
   {

      return this->equals(a);

   }


};




//template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//comparable_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
//comparable_eq_array()
//{
//}
//template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//comparable_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
//comparable_eq_array(const comparable_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a)
//{
//   this->ARRAY_TYPE::operator = (a);
//}
//
//
//template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
//comparable_eq_array<  TYPE,ARG_TYPE,ARRAY_TYPE>::
//comparable_eq_array( comparable_eq_array<  TYPE,ARG_TYPE,ARRAY_TYPE> && a)
//{
//
//	move(::move(a));
//
//}

template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
find_first(ARG_TYPE t) const
{
   ::index find = 0;
   ::index c = this->get_size();
   for(; find < c; find++)
   {
      if(EqualElements(this->element_at(find),t))
         return find;
   }
   return -1;
}

template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
find_last(ARG_TYPE t) const
{
   ::index find = this->get_upper_bound();
   for(; find >= 0; find--)
   {
      if(EqualElements(this->element_at(find),t))
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
find_last_not(ARG_TYPE t) const
{
   ::index find = this->get_upper_bound();
   for (; find >= 0; find--)
   {
      if (!EqualElements(this->element_at(find), t))
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
find_first(ARG_TYPE t, ::index find, ::index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(EqualElements(this->element_at(find), t))
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline ::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
get_count() const
{

   return ARRAY_TYPE::get_count();

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
get_count(ARG_TYPE t, ::index find, ::index last, ::count countMax) const
{

   ::count count = 0;

   while((countMax < 0 || count <= countMax) && (find = find_first(t, find, last)) >= 0)
   {

      count++;

      find++;

   }

   return count;

}


template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
bool comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
contains(ARG_TYPE t) const
{

   return find_first(t) >= 0;

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
bool comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
contains(ARG_TYPE t, ::index find, ::index last, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax)) && (find = find_first(t, find, last)) >= 0)
   {

      count++;

   }

   return count >= countMin && ::conditional(countMax >= 0, count <= countMax);

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
bool comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::add_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
   this->add(t);
   return true;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
TYPE & comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::insert_unique(ARG_TYPE t)
{

   auto iIndex = this->find_first(t);

   if (iIndex < 0)
   {

      iIndex = this->add(t);

   }
   
   return this->element_at(iIndex);

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::add_erase(bool bAdd, ARG_TYPE t)
{
   if (bAdd)
      return this->add_unique(t) ? 1 : 0;
   else
      return this->erase(t);
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::add_unique(const ARRAY_TYPE & a)
{

   ::count ca = 0;

   ::count cAdd = a.get_count();

   for(i32 i = 0; i < cAdd; i++)
   {
      if(add_unique(a[i]))
         ca++;
   }

   return ca;

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
void comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
intersect(const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   for(::index i = 0; i < this->get_size();)
   {
      if(a.contains(this->element_at(i)))
      {
         i++;
      }
      else
      {
         this->erase_at(i);
      }
   }
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
void comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
merge(const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   
   for(::index i = 0; i < a.get_size(); i++)
   {
      
      if(!contains(a.element_at(i)))
      {
         
         this->add(a.element_at(i));

      }

   }

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > &  comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator &= (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   intersect(a);
   return *this;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > &  comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator -= (const TYPE & t)
{
   erase(t);
   return *this;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > &  comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator -= (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   erase_array(a);
   return *this;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator - (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a) const
{
   comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > aRet(*this);
   aRet.erase_array(a);
   return aRet;
}

//template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
//inline bool comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
//operator == (const comparable_eq_array & a) const
//{
//
//   if(this == &a)
//   {
//
//
//
//   }
//
//   if(this->size() != a.size())
//   {
//
//      return false;
//
//   }
//
//
//
//}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > &  comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator |= (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   merge(a);
   return *this;
}


template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::erase_last(ARG_TYPE t)
{

   ::index find;

   if((find = find_last(t)) >= 0)
   {

      this->erase_at(find);

   }

   return find;

}


template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
erase_first(ARG_TYPE t)
{
   ::index find;
   if((find = find_first(t)) >= 0)
   {
      this->erase_at(find);
   }
   return find;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
erase_first(ARG_TYPE t, ::index find, ::index last)
{
   if((find = find_first(t, find, last)) >= 0)
   {
      this->erase_at(find);
   }
   return find;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
erase(ARG_TYPE t, ::index find, ::index last, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if(contains(t, find, last, countMin, countMax))
   {

      while(::conditional(countMax >= 0, count < countMax) && (find = erase_first(t, find, last)) >= 0)
      {

         count++;

      }

   }

   return count;

}


template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::count comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
erase(ARG_TYPE t)
{

   ::count count = 0;

   while (erase_last(t) >= 0)
   {

      count++;

   }

   return count;

}


//template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
//::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
//erase(ARG_TYPE t, ::index find, ::index last, ::count countMin, ::count countMax)
//{
//   return erase(t, find, last, countMin, countMax);
//}


//template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
//typename ARRAY_TYPE::iterator comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
//erase(typename  ARRAY_TYPE::iterator it)
//{
//   return ARRAY_TYPE::erase(it);
//}
//
//template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
//typename ARRAY_TYPE::iterator comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
//erase(typename ARRAY_TYPE::iterator first, typename ARRAY_TYPE::iterator last)
//{
//   return ARRAY_TYPE::erase(first, last);
//}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
erase_array(const comparable_eq_array & a)
{

   ::count count = 0;

   if(this == &a)
   {

      count = this->get_size();

      this->erase_all();

   }
   else
   {

      for(::index i = 0; i < a.get_count(); i++)
      {

         count += erase(a[i]);

      }

   }

   return count;

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
bool comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::insert_unique_at(::index i, ARG_TYPE t)
{

   if (i < 0 || i > this->get_size())
   {

      throw_exception(error_bad_argument);

   }

   auto iFind = this->find_first(t);

   if (iFind < 0)
   {

      this->insert_at(i, t);

      return true;

   }

   if (iFind < i)
   {

      this->erase_at(iFind);

      this->insert_at(i - 1, t);

   }
   else if (iFind > i)
   {

      this->erase_at(iFind);

      this->insert_at(i, t);

   }

   return false;

}