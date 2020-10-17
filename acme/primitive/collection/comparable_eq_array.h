#pragma once

template < class TYPE, class ARG_TYPE = const TYPE &, class ARRAY_TYPE = array < TYPE, ARG_TYPE > >
class comparable_eq_array:
   public ARRAY_TYPE
{
public:


   typedef ARRAY_TYPE BASE_ARRAY;

   explicit comparable_eq_array(::matter * pobject = nullptr) : BASE_ARRAY(pobject) { }
   comparable_eq_array(::std::initializer_list < TYPE > l) : BASE_ARRAY(l) {   }
   comparable_eq_array(const comparable_eq_array & array) : BASE_ARRAY(array) { }
   comparable_eq_array(comparable_eq_array && array) noexcept : BASE_ARRAY(::move(array)) { }

   ::index find_first(ARG_TYPE t) const;
   ::index find_first(ARG_TYPE t, ::index find, ::index last = -1) const;
   ::index find_last(ARG_TYPE t) const;
   ::index find_last_not(ARG_TYPE t) const;
   ::count get_count() const;
   ::count get_count(ARG_TYPE t, ::index start = 0, ::index last = -1, ::count countMax = -1) const;
   bool has(ARG_TYPE t) const { return contains(t); }
   bool contains(ARG_TYPE t) const;
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
   using BASE_ARRAY::remove_last;
   ::index remove_last(ARG_TYPE t);
   ::index remove_first(ARG_TYPE t);
   ::index remove_first(ARG_TYPE t, ::index find, ::index last = -1);
   ::count remove(ARG_TYPE t);
   ::count remove(ARG_TYPE t, ::index find, ::index last = -1, ::count countMin = 0, ::count countMax = -1);
   //typename ARRAY_TYPE::iterator erase(typename ARRAY_TYPE::iterator it);
   //typename ARRAY_TYPE::iterator erase(typename ARRAY_TYPE::iterator first, typename ARRAY_TYPE::iterator last);
   //::index remove(ARG_TYPE t, ::index find = 0, ::index last = -1, ::count countMin = 0, ::count countMax = -1);
   ::count remove_array(const comparable_eq_array & a);



   bool add_unique(ARG_TYPE t);
   ::count add_unique(const ARRAY_TYPE & a);


   ::count add_remove(bool bAdd, ARG_TYPE t);


   // set
   void merge(const comparable_eq_array & a);
   void intersect(const comparable_eq_array & a);

   // set operators
   comparable_eq_array & operator -= (const TYPE & t);
   comparable_eq_array & operator &= (const comparable_eq_array & a);
   comparable_eq_array & operator -= (const comparable_eq_array & a);
   comparable_eq_array& operator |= (const comparable_eq_array & a);

   comparable_eq_array operator -(const comparable_eq_array & a) const;

   //bool operator == (const comparable_eq_array  & a);
   //bool operator != (const comparable_eq_array  & a);


   template < typename A >
   bool operator == (const A & a) const
   {

      if (a.get_size() != this->get_size())
      {

         return false;

      }

      for (::index i = 0; i < this->get_size(); i++)
      {

         if (this->element_at(i) != a.element_at(i))
         {

            return false;

         }

      }

      return true;

   }

   template < typename A >
   bool operator != (const A & a) const
   {

      return !operator==(a);

   }

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
::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::add_remove(bool bAdd, ARG_TYPE t)
{
   if (bAdd)
      return this->add_unique(t) ? 1 : 0;
   else
      return this->remove(t);
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
         this->remove_at(i);
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
   remove(t);
   return *this;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > &  comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator -= (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   remove_array(a);
   return *this;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator - (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a) const
{
   comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > aRet(*this);
   aRet.remove_array(a);
   return aRet;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
inline comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > &  comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
operator |= (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   merge(a);
   return *this;
}

template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
remove_last(ARG_TYPE t)
{
   ::index find;
   if((find = find_last(t)) >= 0)
   {
      this->remove_at(find);
   }
   return find;
}


template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::index comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
remove_first(ARG_TYPE t)
{
   ::index find;
   if((find = find_first(t)) >= 0)
   {
      this->remove_at(find);
   }
   return find;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
remove_first(ARG_TYPE t, ::index find, ::index last)
{
   if((find = find_first(t, find, last)) >= 0)
   {
      this->remove_at(find);
   }
   return find;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
remove(ARG_TYPE t, ::index find, ::index last, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if(contains(t, find, last, countMin, countMax))
   {

      while(::conditional(countMax >= 0, count < countMax) && (find = remove_first(t, find, last)) >= 0)
      {

         count++;

      }

   }

   return count;

}


template <class TYPE,class ARG_TYPE,class ARRAY_TYPE >
::count comparable_eq_array < TYPE,ARG_TYPE,ARRAY_TYPE >::
remove(ARG_TYPE t)
{

   ::count count = 0;

   while (remove_last(t) >= 0)
   {

      count++;

   }

   return count;

}


//template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
//::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
//erase(ARG_TYPE t, ::index find, ::index last, ::count countMin, ::count countMax)
//{
//   return remove(t, find, last, countMin, countMax);
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
remove_array(const comparable_eq_array & a)
{

   ::count count = 0;

   if(this == &a)
   {

      count = this->get_size();

      this->remove_all();

   }
   else
   {

      for(::index i = 0; i < a.get_count(); i++)
      {

         count += remove(a[i]);

      }

   }

   return count;

}



