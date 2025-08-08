#pragma once


#include "acme/prototype/comparison/equals.h"


template < class TYPE, class ARG_TYPE, class ARRAY_TYPE >
class comparable_eq_array:
   //public comparable_eq_range < ARRAY_TYPE >
   public ARRAY_TYPE
{
public:


   //using BASE_RANGE = comparable_eq_range < ARRAY_TYPE >;
   using BASE_RANGE = ARRAY_TYPE;

   using BASE_ARRAY = ARRAY_TYPE;

   using CONST_RAW_RANGE = typename BASE_ARRAY::CONST_RAW_RANGE;

   using iterator = typename ARRAY_TYPE::iterator;
   using const_iterator = typename ARRAY_TYPE::const_iterator;


   using ARRAY_TYPE::ARRAY_TYPE;
   using ARRAY_TYPE::operator =;

   // comparable_eq_array(no_initialize_t):BASE_RANGE(no_initialize_t{}){}
   // comparable_eq_array(nullptr_t):BASE_RANGE(nullptr){}
   // comparable_eq_array():BASE_RANGE(){}
   // comparable_eq_array(::std::initializer_list < TYPE > initializer_list) { this->add_initializer_list(initializer_list); }
   // comparable_eq_array(const comparable_eq_array & array) : BASE_RANGE(array) {}
   // comparable_eq_array(comparable_eq_array && array) noexcept : BASE_RANGE(::transfer(array)) { }
   // comparable_eq_array(::range < const_iterator > constrange) : BASE_RANGE(constrange) {}
   // template < primitive_integral INTEGRAL >
   // comparable_eq_array(const_iterator begin, INTEGRAL count) : BASE_RANGE(begin, count) {}
   // comparable_eq_array(const_iterator begin, const_iterator end) : BASE_RANGE(begin, end) {}
   // comparable_eq_array(const_iterator begin) : BASE_RANGE(begin, find_first_null_character(begin)) {}

   
   ::collection::index find_first(ARG_TYPE t) const;
   ::collection::index find_first(ARG_TYPE t, ::collection::index find, ::collection::index last = -1) const;
   ::collection::index find_last(ARG_TYPE t) const;
   ::collection::index find_last_not(ARG_TYPE t) const;
   ::collection::count get_count() const;
   ::collection::count get_count(ARG_TYPE t, ::collection::index start = 0, ::collection::index last = -1, ::collection::count countMax = -1) const;
   //bool has(ARG_TYPE t) const { return contains(t); }
   bool contains(ARG_TYPE t) const;
   bool has(ARG_TYPE t) const { return contains(t); }
   bool contains(ARG_TYPE t, ::collection::index start, ::collection::index last = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;
   bool contains(comparable_eq_array & a, ::collection::count cMinCount = -1) const
   {
      if(cMinCount < 0)
      {
         cMinCount += a.get_count() + 1;
      }
      for(::collection::index i = 0; cMinCount > 0 && i < a.get_count(); i++)
      {
         if(!this->contains(a[i]))
            return false;
         cMinCount--;
      }
      return true;
   }
   

   using BASE_ARRAY::erase_first;
   using BASE_ARRAY::erase_last;
   ::collection::index erase_last(ARG_TYPE t);
   ::collection::index erase_first(ARG_TYPE t);
   ::collection::index erase_first(ARG_TYPE t, ::collection::index find, ::collection::index last = -1);
   ::collection::count erase(ARG_TYPE t);
   ::collection::count erase(ARG_TYPE t, ::collection::index find, ::collection::index last = -1, ::collection::count countMin = 0, ::collection::count countMax = -1);
   template < primitive_container CONTAINER>
   ::collection::count erase_container(const CONTAINER & container);


   bool add_unique(ARG_TYPE t);
   ::collection::count append_unique(const ARRAY_TYPE & a);
   TYPE & insert_unique(ARG_TYPE t);


   bool insert_unique_at(::collection::index i, ARG_TYPE t);

   ::collection::count add_erase(bool bAdd, ARG_TYPE t);


   // set
   void merge(const comparable_eq_array & a);
   void intersect(const comparable_eq_array & a);

   // set operators
   //comparable_eq_array & operator -= (const TYPE & t);
   //comparable_eq_array & operator &= (const comparable_eq_array & a);
   //comparable_eq_array & operator -= (const comparable_eq_array & a);
   //comparable_eq_array& operator |= (const comparable_eq_array & a);

   //comparable_eq_array operator -(const comparable_eq_array & a) const;


   // using ARRAY_TYPE::operator =;
   // comparable_eq_array & operator = (const comparable_eq_array & array)
   // {
   //
   //    BASE_ARRAY::operator =(array);
   //
   //    return *this;
   //
   // }
   //
   //
   // comparable_eq_array & operator = (comparable_eq_array && array)
   // {
   //
   //    BASE_ARRAY::operator = (::transfer(array));
   //
   //    return *this;
   //
   // }
   //
   
   comparable_eq_array & transfer(comparable_eq_array && array)
   {
      
      BASE_ARRAY::transfer(::transfer(array));
      
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
//	transfer(::transfer(a));
//
//}

template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::collection::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
find_first(ARG_TYPE t) const
{
   ::collection::index find = 0;
   ::collection::index c = this->get_size();
   for(; find < c; find++)
   {
      if(EqualElements(this->element_at(find),t))
         return find;
   }
   return -1;
}

template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::collection::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
find_last(ARG_TYPE t) const
{
   ::collection::index find = this->get_upper_bound();
   for(; find >= 0; find--)
   {
      if(EqualElements(this->element_at(find),t))
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::collection::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
find_last_not(ARG_TYPE t) const
{
   ::collection::index find = this->get_upper_bound();
   for (; find >= 0; find--)
   {
      if (!EqualElements(this->element_at(find), t))
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::collection::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
find_first(ARG_TYPE t, ::collection::index find, ::collection::index last) const
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
inline ::collection::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
get_count() const
{

   return ARRAY_TYPE::get_count();

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::collection::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
get_count(ARG_TYPE t, ::collection::index find, ::collection::index last, ::collection::count countMax) const
{

   ::collection::count count = 0;

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
contains(ARG_TYPE t, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax) const
{

   ::collection::count count = 0;

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
::collection::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::add_erase(bool bAdd, ARG_TYPE t)
{
   if (bAdd)
      return this->add_unique(t) ? 1 : 0;
   else
      return this->erase(t);
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::collection::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::append_unique(const ARRAY_TYPE & a)
{

   ::collection::count ca = 0;

   ::collection::count cAdd = a.get_count();

   for(int i = 0; i < cAdd; i++)
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
   for(::collection::index i = 0; i < this->get_size();)
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
   
   for(::collection::index i = 0; i < a.get_size(); i++)
   {
      
      if(!contains(a.element_at(i)))
      {
         
         this->add(a.element_at(i));

      }

   }

}


template < primitive_container CONTAINER, primitive_container CONTAINER2 >
inline CONTAINER& operator |= (CONTAINER& container, const CONTAINER& container2)
{

   container.merge(container);

   return container;

}


template < primitive_container CONTAINER, primitive_container CONTAINER2 >
inline CONTAINER& operator &= (CONTAINER& container, const CONTAINER& container2)
{
   
   container.intersect(container2);

   return container;

}


template < primitive_container CONTAINER >
inline CONTAINER & operator -= (CONTAINER & container, const typename CONTAINER::CONTAINER_ITEM_TYPE& t)
{

   container.erase(t);

   return container;

}


template < primitive_container CONTAINER, primitive_container CONTAINER2 >
inline CONTAINER& operator -= (CONTAINER& container, const CONTAINER2& container2)
{

   container.erase_container(container2);

   return container;

}


template < primitive_container CONTAINER1, primitive_container CONTAINER2 >
CONTAINER1 operator - (const CONTAINER1 & container1, const CONTAINER2 & container2)
{
   
   auto container = container1;
   
   container.erase_container(container2);
   
   return container;

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



template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::collection::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::erase_last(ARG_TYPE t)
{

   ::collection::index find;

   if((find = find_last(t)) >= 0)
   {

      this->erase_at(find);

   }

   return find;

}


template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::collection::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
erase_first(ARG_TYPE t)
{
   ::collection::index find;
   if((find = find_first(t)) >= 0)
   {
      this->erase_at(find);
   }
   return find;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::collection::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
erase_first(ARG_TYPE t, ::collection::index find, ::collection::index last)
{
   if((find = find_first(t, find, last)) >= 0)
   {
      this->erase_at(find);
   }
   return find;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::collection::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
erase(ARG_TYPE t, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax)
{

   ::collection::count count = 0;

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
::collection::count comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
erase(ARG_TYPE t)
{

   ::collection::count count = 0;

   while (erase_last(t) >= 0)
   {

      count++;

   }

   return count;

}


//template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
//::collection::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
//erase(ARG_TYPE t, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax)
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
template < primitive_container CONTAINER>
::collection::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
erase_container(const CONTAINER & container)
{

   ::collection::count count = 0;

   if((::quantum *) this == (::quantum *)&container)
   {

      count = this->get_size();

      this->erase_all();

   }
   else
   {

      for(auto & item : container)
      {

         count += erase(item);

      }

   }

   return count;

}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
bool comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::insert_unique_at(::collection::index i, ARG_TYPE t)
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
