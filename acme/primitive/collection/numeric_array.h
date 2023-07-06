#pragma once


#include "raw_array.h"
#include "comparable_eq_array.h"
#include "comparable_array.h"
#include "comparable_raw_array.h"
#include "acme/primitive/primitive/compare_predicate.h"

#include "acme/primitive/mathematics/numeric.h"


template < typename ARG_TYPE >
::index numeric_compare(ARG_TYPE t1, ARG_TYPE t2)
{
   typename ::erase_reference < ARG_TYPE >::TYPE t = t1 - t2;
   if(t > ::numeric_info< typename ::erase_reference < ARG_TYPE >::TYPE >::null())
      return 1;
   else if(t < ::numeric_info < typename ::erase_reference < ARG_TYPE >::TYPE >::null())
      return -1;
   else
      return 0;
}

//template < >
//inline i64 from_string(const ::scoped_string & scopedstr)
//{
//   return to_i64(string(psz));
//}


template < typename TYPE, enum_type m_etypeContainer >
class numeric_array :
   public comparable_raw_array < TYPE, TYPE, ::allocator::nodef < TYPE >, m_etypeContainer >
{
public:


   numeric_array(){}


   numeric_array(const std::initializer_list < TYPE > & initializer_list):
      comparable_raw_array < TYPE, TYPE, ::allocator::nodef < TYPE >, m_etypeContainer >(initializer_list)
   {

   }

   numeric_array(const TYPE * pa, ::count c) :
      numeric_array()
   {

      this->set_size(c);

      while(c > 0)
      {

         c--;

         this->operator[](c) = pa[c];

      }

   }


   numeric_array(const numeric_array & array)
   {

      operator = (array);

   }

   numeric_array(numeric_array && array)
   {

      this->transfer(::transfer(array));

   }


   //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(numeric_array, comparable_raw_array < TYPE >)

   typedef TYPE BASE_TYPE;
   typedef const TYPE & BASE_ARG_TYPE;
   typedef comparable_raw_array < TYPE, TYPE, ::allocator::nodef < TYPE >, m_etypeContainer > BASE_ARRAY;


   ::index find_first_maximum_value();
   TYPE & get_maximum_value();
   ::index find_first_minimum_value();
   TYPE & get_minimum_value();


   template < typename ::i32 >
   ::i32 & mask(::i32 & i)
   {

      i = 0;

      for(auto number : *this)
      {

         i |= number;

      }

      return i;

   }

   void push_last();


   TYPE pop_max();
   TYPE pop_max_last_add_up(TYPE tLastAddUp);

   TYPE get_sum(::index first = 0, ::count in_count_out_last = -1)
   {

      this->prepare_first_in_count_last_out(first, in_count_out_last);

      TYPE t = ::numeric_info < TYPE >:: null();

      for(::index i = first; i <= in_count_out_last; i++)
      {

         // TODO: numeric calculus

         t += this->element_at(i);

      }

      return t;

   }


   TYPE pop_to();


   void CopySorted(const numeric_array & array, const TYPE & tOffset, const TYPE & tMin);

   void Diff(
   const numeric_array & array1,
   const numeric_array & array2);

   void divide(TYPE i);

   void ElementDiff(
   const numeric_array & array1,
   const TYPE & tMax);

   TYPE simple_total_mean();

   void set(const TYPE & t, ::index iStart = 0, ::index iEnd = -1);

   ::index Cmp(const numeric_array & array1);


   numeric_array unique() const;
   void unique();




   numeric_array operator - (const numeric_array & a) const;
   numeric_array operator + (const numeric_array & a) const;

   numeric_array & operator -= (const numeric_array & a);
   numeric_array & operator += (const numeric_array & a);



   int compare(const numeric_array & a) const
   {

      ::count iCompare = this->get_size() - a.get_size();

      if (iCompare != 0)
      {

         return ::numeric::sign(iCompare);

      }

      TYPE t;
      for(::index i = 0; i < this->get_size(); i++)
      {

         t = this->element_at(i) - a[i];

         if (t != 0)
         {

            return ::numeric::sign(t);

         }

      }

      return 0;

   }


   using comparable_raw_array < TYPE, TYPE, ::allocator::nodef < TYPE >, m_etypeContainer >::operator =;
   numeric_array & operator = (const numeric_array & a)
   {

      BASE_ARRAY::operator = (a);

      return *this;

   }


   numeric_array & operator = (numeric_array && a)
   {
      transfer(::transfer(a));
      return *this;
   }


   numeric_array & transfer (numeric_array && a)
   {
      BASE_ARRAY::transfer(::transfer(a));
      return *this;
   }


   void sort(bool bAsc = true);

   bool is_any_set() const
   {

      return this->predicate_contains([](auto number) {return number != (TYPE)0; });

   }


};



template < typename TYPE, ::enum_type m_etypeContainer >
class unique_number_sort_array :
   public numeric_array < TYPE, m_etypeContainer >
{
public:
   unique_number_sort_array();
   unique_number_sort_array(const unique_number_sort_array & array);

   ::index add(const TYPE & newElement)
   {
      ::index iFind = 0;
      if(find(newElement, iFind))
      {
         return -1;
      }
      else
      {
         this->insert_at(iFind, newElement);
         return iFind;
      }
   }

   bool find(const TYPE &t, ::index & find) const
   {
      ::index iL = find;
      ::index iU = this->get_upper_bound();
      while(iU - iL > 5)
      {
         find = (iL + iU) / 2;
         TYPE tCmp = t - this->element_at(find);
         if(tCmp == numeric_info < TYPE > :: null ())
         {
            return true;
         }
         else if(tCmp > numeric_info < TYPE >::null())
         {
            iL = find + 1;
         }
         else
         {
            iU = find - 1;
         }
      }
      for(; find < this->get_size(); find++)
      {
         TYPE tCmp = t - this->element_at(find);
         if(tCmp == numeric_info < TYPE >::null())
         {
            return true;
         }
         else if(tCmp < numeric_info  < TYPE >::null())
         {
            return false;
         }
      }
      return false;
   }

   /*::index find_first_maximum_value();
   TYPE & get_maximum_value();

   void CopySorted(
   const numeric_array  < TYPE > & array, // this array is sorted
   TYPE & tOffset,
   TYPE & tMin);

   void Diff(
   const numeric_array  < TYPE > & array1,
   const numeric_array  < TYPE > & array2);*/

   //void divide(i32 i);

   //void ElementDiff(
   // const numeric_array  < TYPE > & array1,
   //TYPE & tMax);

   //TYPE GetMean();

   //void set(const TYPE & t, i32 iStart = 0, i32 iEnd = -1);

   //i32 Cmp(const numeric_array  < TYPE > & array1);


   /*virtual void quick_sort(bool bAsc = true)
   {
   if(bAsc)
   {
   sort::QuickSortAsc(*this);
   }
   else
   {
   sort::QuickSortDesc(*this);
   }
   }*/


};



//template < typename T >
//string & to_network_payload(string & str, const T & t, bool bNewLine);


//template < typename TYPE, ::enum_type m_etypeContainer >
//string & numeric_array < TYPE, m_etypeContainer >::get_network_payload(string & str, bool bNewLine) const
//{
//
//
//   str += "[";
//
//   if(this->get_count() > 0)
//   {
//
//      to_network_payload(str, this->element_at(0), bNewLine);
//
//   }
//
//   for (::index i = 1; i < this->get_count(); i++)
//   {
//
//      if (bNewLine)
//      {
//
//         str += ", \r\n";
//
//      }
//      else
//      {
//
//         str += ", ";
//
//      }
//
//      to_network_payload(str, this->element_at(i), bNewLine);
//
//   }
//
//   if (bNewLine)
//   {
//
//      str += "\r\n";
//
//   }
//
//   str += "]";
//
//   return str;
//
//}


//template < typename TYPE, ::enum_type m_etypeContainer >
//void numeric_array < TYPE, m_etypeContainer >::implode(string & str, const ::scoped_string & scopedstrSeparator, ::index start, ::count count) const
//
//{
//   if(start < 0)
//   {
//      start += this->get_size();
//   }
//   ::index last;
//   if(count < 0)
//   {
//      last = this->get_size() + count;
//   }
//   else
//   {
//      last = start + count - 1;
//   }
//   if(start <= last)
//   {
//
//      ::index i = start;
//
//      ::copy(str, this->element_at(i));
//
//      i++;
//      for(; i <= last; i++)
//      {
//         str += scopedstrSeparator + as_string(this->element_at(i));
//      }
//   }
//   else
//   {
//
//      str.empty();
//
//   }
//
//}


//template < typename TYPE, ::enum_type m_etypeContainer >
//string numeric_array < TYPE, m_etypeContainer >::implode(const ::scoped_string & scopedstrSeparator, ::index iStart, ::index iEnd) const
//{
//
//   string str;
//
//   implode(str, scopedstrSeparator, iStart, iEnd);
//
//   return str;
//
//}



//template < typename TYPE, ::enum_type m_etypeContainer >
//void numeric_array < TYPE, m_etypeContainer >::each_add(const TYPE & t,::index i, ::count iEnd)
//{
//
//   if(iEnd == 0)
//      return ;
//
//   if(iEnd < 0)
//   {
//
//      iEnd += get_size();
//
//   }
//   else
//   {
//
//      iEnd--;
//
//   }
//
//   if(i < 0)
//   {
//
//      i += get_size();
//
//   }
//
//   if(i < 0)
//   {
//
//      iEnd += i;
//
//      i = 0;
//
//   }
//
//   while(i <= iEnd)
//   {
//
//      element_at(i) += t;
//
//      i++;
//
//   }
//
//
//}
//
//template < typename TYPE, ::enum_type m_etypeContainer >
//void numeric_array < TYPE, m_etypeContainer >::each_subtract(const TYPE & t,::index i,::count iEnd)
//{
//
//   if(iEnd == 0)
//      return;
//
//   if(iEnd < 0)
//   {
//
//      iEnd += get_size();
//
//   }
//   else
//   {
//
//      iEnd--;
//
//   }
//
//   if(i < 0)
//   {
//
//      i += get_size();
//
//   }

//   if(i < 0)
//   {
//
//      iEnd += i;
//
//      i = 0;
//
//   }
//
//   while(i <= iEnd)
//   {
//
//      element_at(i) -= t;
//
//      i++;
//
//   }
//
//}



template < typename TYPE, ::enum_type m_etypeContainer >
numeric_array < TYPE, m_etypeContainer > numeric_array < TYPE, m_etypeContainer >::unique() const
{

   numeric_array < TYPE, m_etypeContainer > a;

   for(i32 i = 0; i < this->get_count(); i++)
   {
      a.add_unique(this->element_at(i));
   }

   return a;

}

template < typename TYPE, ::enum_type m_etypeContainer >
void numeric_array < TYPE, m_etypeContainer >::unique()
{

   numeric_array < TYPE, m_etypeContainer > a;

   for(i32 i = 0; i < this->get_count(); i++)
   {
      a.add_unique(this->element_at(i));
   }

   *this = a;

}





template < typename TYPE, ::enum_type m_etypeContainer >
::index numeric_array < TYPE, m_etypeContainer >::
Cmp(const numeric_array & array1)
{
   ::count iMinSize = minimum(array1.get_size(), this->get_size());
   ::index i = 0;
   while(true)
   {
      if(i >= iMinSize)
      {
         return this->get_size() - array1.get_size();
      }
      if(this->element_at(i) > array1.element_at(i))
         return 1;
      else if(this->element_at(i) < array1.element_at(i))
         return -1;
      i++;
   }
}

template < typename TYPE, ::enum_type m_etypeContainer >
void numeric_array < TYPE, m_etypeContainer >::CopySorted(
   const numeric_array< TYPE, m_etypeContainer > & a,
const TYPE & tOffset,
const TYPE & tMin)
{


   ::index i;
   TYPE tStart = tMin - tOffset;
   this->allocate(a.get_size());
   TYPE t;
   for(i = 0; i < a.get_size()
         && a.get_at(i) <= tStart; i++)
   {
      this->set_at(i, tMin);
   }
   for(; i < a.get_size(); i++)
   {
      t = a.get_at(i) + tOffset;
      this->set_at(i, t);
   }
}


template < typename TYPE, ::enum_type m_etypeContainer >
void numeric_array < TYPE, m_etypeContainer >::Diff(
const numeric_array < TYPE, m_etypeContainer > & array1,
const numeric_array < TYPE, m_etypeContainer > & array2)
{
   ASSERT(array1.get_size() == array2.get_size());
   ::index i;
   this->allocate(array1.get_size());
   TYPE t;
   for(i = 0; i < array1.get_size(); i++)
   {
      t = array1.get_at(i) - array2.get_at(i);
      this->set_at(i, t);
   }
}

template < typename TYPE, ::enum_type m_etypeContainer >
void numeric_array < TYPE, m_etypeContainer >::ElementDiff(
const numeric_array  & a,
const TYPE & tMax)
{
   ::index i;
   TYPE t;
   TYPE it;
   this->allocate(a.get_size());
   if(a.get_size() > 0)
   {
      TYPE tLast = a[0];
      for(i = 1; i < a.get_size(); i++)
      {
         t = a[i];
         it =  t - tLast;
         this->set_at(i - 1, it);
         tLast = t;
      }
      it =  tMax - tLast;
      this->set_at(i - 1, it);
   }
}


template < typename TYPE, ::enum_type m_etypeContainer >
::index numeric_array < TYPE, m_etypeContainer >::find_first_maximum_value()
{

   TYPE tMax = this->element_at(0);

   ::index iFind = 0;

   for(::index i = 1; i < this->get_size(); i++)
   {

      if (this->element_at(i) > tMax)
      {

         iFind = i;

         tMax = this->element_at(i);

      }

   }

   return iFind;

}


template < typename TYPE, ::enum_type m_etypeContainer >
TYPE & numeric_array < TYPE, m_etypeContainer >::
get_maximum_value()
{
   ASSERT(this->get_size() > 0);
   return this->element_at(find_first_maximum_value());
}

template < typename TYPE, ::enum_type m_etypeContainer >
::index numeric_array < TYPE, m_etypeContainer >::find_first_minimum_value()
{

   TYPE tMin = this->element_at(0);

   ::index iFind = 0;

   for (::index i = 1; i < this->get_size(); i++)
   {

      if (this->element_at(i) < tMin)
      {

         iFind = i;

         tMin = this->element_at(i);

      }

   }

   return iFind;

}


template < typename TYPE, ::enum_type m_etypeContainer >
TYPE & numeric_array < TYPE, m_etypeContainer >::
get_minimum_value()
{
   ASSERT(this->get_size() > 0);
   return this->element_at(find_first_minimum_value());
}

template < typename INTEGER >
inline INTEGER get_integer_mean(const INTEGER * p, ::count N)
{
   i64 x = 0;
   i64 y = 0;
   ::count c = N;
   while (c > 0)
   {
      i64 a = *p;
      x += a / N;
      if (a >= 0)
      {
         int b = (int) (a % N);
         if (y >= N - b)
         {
            x++;
            y -= N - b;
         }
         else
         {
            y += b;
         }
      }
      else
      {
         int b = (int) ((-a) % N);
         if (y <= -N + b)
         {
            x--;
            y -= -N + b;
         }
         else
         {
            y -= b;
         }
      }
      c--;
      p++;
   }
   return (int) (x + y / N);

}


template < primitive_integral INTEGRAL >
inline INTEGRAL simple_total_mean(const INTEGRAL * p, ::count N)
{

   ::i64 i = 0;

   ::count c = N;

   while(c > 0)
   {

      i += *p;

      p++;

      c--;

   }

   return (INTEGRAL) (i / N);

}

template < primitive_floating FLOATING >
inline FLOATING simple_total_mean(const FLOATING * p, ::count N)
{

   double d = 0.;

   ::count c = N;

   while (c > 0)
   {

      d += *p;

      p++;

      c--;

   }

   return (FLOATING)(d / (double) N);

}

inline int get_mean(const int * A, ::count N)
{
   return get_integer_mean(A, N);
}


template < typename TYPE, ::enum_type m_etypeContainer >
TYPE numeric_array < TYPE, m_etypeContainer >::simple_total_mean()
{

   return ::simple_total_mean(this->get_data(), this->get_count());

}


template < typename TYPE, ::enum_type m_etypeContainer >
void numeric_array < TYPE, m_etypeContainer >::set(const TYPE & t, ::index iStart, ::index iEnd)
{
   if(iEnd == -1)
      iEnd = this->get_upper_bound();
   for(::index i = iStart; i <= iEnd; i++)
   {
      this->set_at(i, t);
   }
}


template < typename TYPE, ::enum_type m_etypeContainer >
void numeric_array < TYPE, m_etypeContainer >::divide(TYPE div)
{
   ::index i;
   for(i = 0; i < this->get_size(); i++)
   {
      this->element_at(i) = this->element_at(i) / div;
   }
}

template < typename TYPE, ::enum_type m_etypeContainer >
numeric_array < TYPE, m_etypeContainer >  numeric_array < TYPE, m_etypeContainer >::operator - (const numeric_array < TYPE, m_etypeContainer > & a) const
{

   numeric_array < TYPE, m_etypeContainer > aRet(*this);

   aRet.erase_array(a);

   return aRet;

}

template < typename TYPE, ::enum_type m_etypeContainer >
numeric_array < TYPE, m_etypeContainer >  numeric_array < TYPE, m_etypeContainer >::operator + (const numeric_array < TYPE, m_etypeContainer >  & a) const
{

   numeric_array < TYPE, m_etypeContainer > aRet(*this);

   aRet.append(a);

   return aRet;

}

template < typename TYPE, ::enum_type m_etypeContainer >
numeric_array < TYPE, m_etypeContainer >  & numeric_array < TYPE, m_etypeContainer >::operator -= (const numeric_array < TYPE, m_etypeContainer >  & a)
{

   this->erase_array(a);

   return *this;

}

template < typename TYPE, ::enum_type m_etypeContainer >
numeric_array < TYPE, m_etypeContainer >  & numeric_array < TYPE, m_etypeContainer >::operator += (const numeric_array < TYPE, m_etypeContainer >  & a)
{

   this->append(a);

   return *this;

}



template < typename TYPE, ::enum_type m_etypeContainer >
inline void numeric_array < TYPE, m_etypeContainer > ::push_last()
{

   this->add(this->last());

}


template < typename TYPE, ::enum_type m_etypeContainer >
inline TYPE numeric_array < TYPE, m_etypeContainer > ::pop_max()
{

   TYPE lastelement = this->last();

   TYPE nowpop = this->pop();

   this->last() = maximum(nowpop, lastelement);

   return this->last();

}



template < typename TYPE, ::enum_type m_etypeContainer >
inline TYPE numeric_array < TYPE, m_etypeContainer > ::pop_max_last_add_up(TYPE tLastAddUp)
{

   TYPE lastelement = this->last();

   TYPE nowpop = this->pop();

   this->last() = maximum(nowpop, lastelement + tLastAddUp);

   return this->last();

}



template < typename TYPE, ::enum_type m_etypeContainer >
inline TYPE numeric_array < TYPE, m_etypeContainer > ::pop_to()
{

   TYPE lastelement = this->pop();

   this->last() = lastelement;

   return this->last();

}



template < typename TYPE, ::enum_type m_etypeContainer >
unique_number_sort_array < TYPE, m_etypeContainer >::
unique_number_sort_array() 
{
}

template < typename TYPE, ::enum_type m_etypeContainer >
unique_number_sort_array < TYPE, m_etypeContainer >::
unique_number_sort_array(const unique_number_sort_array < TYPE, m_etypeContainer > & a) 
{
   numeric_array < TYPE, m_etypeContainer > ::operator = (a);
}





















































namespace acme
{

   namespace numeric_array
   {

      template < class ARRAY >
      typename ARRAY::BASE_TYPE big_average(const ARRAY & a)
      {
         ::count c = a.get_count();
         if(c == 0)
            return 0.0;
         typename ARRAY::BASE_TYPE f = 0.0;
         typename ARRAY::BASE_TYPE fCount = (typename ARRAY::BASE_TYPE) c;
         for(::index i = 0; i < c; i++)
         {
            f += a.element_at(i) / fCount;
         }
         return f;
      }

   } // namespace numeric_array

} // namespace acme


#include "numeric_array_range.h"



namespace acme
{

   namespace array
   {


      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,::index & iIndex,::index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE));

      template<class ARRAY, primitive_array INDEX_ARRAY >
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,::index & iIndex, less_predicate_base < typename ARRAY::BASE_ARG_TYPE > * pcompare, INDEX_ARRAY & ia);

      template<class ARRAY, primitive_array INDEX_ARRAY>
      ::index sort_add(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,::index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),INDEX_ARRAY & ia)
      {
         ::index iIndex = 0;
         binary_search(a, t, iIndex, fCompare, ia);
         a.insert_at(iIndex, t);
         ia.add(iIndex);
         return iIndex;
      }

      template<class ARRAY, class ARRAY2, primitive_array INDEX_ARRAY >
      ::count sort_add_array(ARRAY & a,ARRAY2 & a2,::index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),INDEX_ARRAY & ia)
      {
         for(::index i = 0; i < a2.get_count(); i++)
         {
            sort_add(a,a2[i],fCompare,ia);
         }
         return a2.get_count();
      }


      template<class ARRAY, primitive_array INDEX_ARRAY >
      ::count sort_erase(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,::index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE), INDEX_ARRAY & ia)
      {
         ::count ca = 0;
         ::index iFind = 0;
         while(binary_search(a,t, iFind, fCompare, ia))
         {
            a.erase_at(iFind);
            ::index iIndex = ia[iFind];
            ia.erase_at(iFind);
            for(::index i = 0; i < ia.get_size(); i++)
            {
               if(ia[i] > iIndex)
               {
                  ia[i]--;
               }
            }
            iFind = 0;
            ca++;
         }
         return ca;
      }



   } // namespace array




   template < typename TYPE, ::enum_type m_etypeContainer >
   numeric_array_each < ::numeric_array < TYPE, m_etypeContainer > > each(::numeric_array < TYPE, m_etypeContainer > & a) { return a; }
   template < typename TYPE, ::enum_type m_etypeContainer >
   numeric_array_each < ::numeric_array < TYPE, m_etypeContainer > > all(::numeric_array < TYPE, m_etypeContainer > & a) { return a; }
   template < typename TYPE, ::enum_type m_etypeContainer >
   numeric_array_each < ::numeric_array < TYPE, m_etypeContainer > > range(::numeric_array < TYPE, m_etypeContainer > & a) { return a; }

   template < typename TYPE, ::enum_type m_etypeContainer >
   numeric_array_range < ::numeric_array < TYPE, m_etypeContainer > > each(::numeric_array < TYPE, m_etypeContainer > & a,::index iBeg,::count iCount) { return numeric_array_range < ::numeric_array < TYPE, m_etypeContainer > >(a,iBeg,iCount); }
   template < typename TYPE, ::enum_type m_etypeContainer >
   numeric_array_range < ::numeric_array < TYPE, m_etypeContainer > > all(::numeric_array < TYPE, m_etypeContainer > & a,::index iBeg,::count iCount) { return numeric_array_range < ::numeric_array < TYPE, m_etypeContainer > >(a,iBeg,iCount); }
   template < typename TYPE, ::enum_type m_etypeContainer >
   numeric_array_range < ::numeric_array < TYPE, m_etypeContainer > > range(::numeric_array < TYPE, m_etypeContainer > & a,::index iBeg,::count iCount) { return numeric_array_range <  ::numeric_array < TYPE, m_etypeContainer > >(a,iBeg,iCount); }

   template < typename TYPE, ::enum_type m_etypeContainer >
   void quick_sort(::numeric_array < TYPE, m_etypeContainer > & a, bool bAsc = true);

   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_greater_than(::numeric_array < TYPE, m_etypeContainer > & a,TYPE hi)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) > hi)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_greater_than_or_equal(::numeric_array < TYPE, m_etypeContainer > & a,TYPE hi)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) >= hi)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_lesser_than(::numeric_array < TYPE, m_etypeContainer > & a,TYPE lo)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) < lo)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_lesser_than_or_equal(::numeric_array < TYPE, m_etypeContainer > & a,TYPE lo)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) <= lo)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_lesser_than_or_greater_than(::numeric_array < TYPE, m_etypeContainer > & a,TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) < lo)
         {
            a.erase_at(i);
            ca++;
         }
         else if(a.element_at(i) > hi)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_lesser_than_or_greater_than_or_equal(::numeric_array < TYPE, m_etypeContainer > & a,TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) < lo)
         {
            a.erase_at(i);
            ca++;
         }
         else if(a.element_at(i) >= hi)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_lesser_than_or_equal_or_greater_than(::numeric_array < TYPE, m_etypeContainer > & a,TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) <= lo)
         {
            a.erase_at(i);
            ca++;
         }
         else if(a.element_at(i) > hi)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < typename TYPE, ::enum_type m_etypeContainer >
   ::count erase_lesser_than_or_equal_or_greater_than_or_equal(::numeric_array < TYPE, m_etypeContainer > & a, TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(::index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) <= lo)
         {
            a.erase_at(i);
            ca++;
         }
         else if(a.element_at(i) >= hi)
         {
            a.erase_at(i);
            ca++;
         }
      }

      return ca;

   }

} // namespace acme


#include "sort.h"

template < typename TYPE, ::enum_type m_etypeContainer >
void numeric_array < TYPE, m_etypeContainer >::sort(bool bAsc)
{

   if (bAsc)
   {

      sort::QuickSortAsc(*this);

   }
   else
   {

      sort::QuickSortDesc(*this);

   }

}


using int2a = array < int_array >;


using float2a = array < float_array >;


using double2a = array < double_array >;





namespace acme
{


    namespace array
    {


        template < typename ARRAY1, typename ARRAY2 >
        inline bool is_equal(const ARRAY1 & a1, const ARRAY2 & a2)
        {

           if (a1.get_count() != a2.get_count())
           {

              return false;

           }

           for (int i = 0; i < a1.get_count(); i++)
           {

              if (a1[i] != a2[i])
              {

                 return false;

              }

           }

           return true;

        }


        template < typename ARRAY_TYPE, typename PRED >
        void predicate_sort(ARRAY_TYPE  & a, PRED pred)
        {

           index_array stackLowerBound;

           index_array stackUpperBound;

           iptr iLowerBound;

           iptr iUpperBound;

           iptr iLPos, iUPos, iMPos;

           if (a.get_size() >= 2)
           {

              stackLowerBound.push(0);

              stackUpperBound.push(a.get_size() - 1);

              while (true)
              {

                 iLowerBound = stackLowerBound.pop();

                 iUpperBound = stackUpperBound.pop();

                 iLPos = iLowerBound;

                 iMPos = iLowerBound;

                 iUPos = iUpperBound;

                 while (true)
                 {

                    while (true)
                    {

                       if (iMPos >= iUPos)
                       {

                          goto break_mid_loop;

                       }

                       if (!pred(a[iUPos], a[iMPos]))
                       {

                          iUPos--;

                       }
                       else
                       {

                          a.__swap(iMPos, iUPos);

                          break;

                       }

                    }

                    iMPos = iUPos;

                    while (true)
                    {

                       if (iLPos >= iMPos)
                       {

                          goto break_mid_loop;

                       }

                       if (!pred(a[iMPos], a[iLPos]))
                       {

                          iLPos++;

                       }
                       else
                       {

                          a.__swap(iLPos, iMPos);

                          break;

                       }


                    }

                    iMPos = iLPos;

                 }

                 break_mid_loop:

                 if (iLowerBound < iMPos - 1)
                 {

                    stackLowerBound.push(iLowerBound);

                    stackUpperBound.push(iMPos - 1);

                 }

                 if (iMPos + 1 < iUpperBound)
                 {

                    stackLowerBound.push(iMPos + 1);

                    stackUpperBound.push(iUpperBound);

                 }

                 if (stackLowerBound.count() == 0)
                 {

                    break;

                 }

              }

           }

        }

        template < typename ARRAY_TYPE, typename T, typename PRED >
        iptr predicate_binary_search(const ARRAY_TYPE & a, const T & t, PRED pred)
        {

           iptr iLPos, iUPos, iMPos;

           iLPos = 0;

           iUPos = a.get_upper_bound();

           while(iLPos <= iUPos)
           {

              iMPos = (iLPos + iUPos) / 2;

              if (pred(a[iMPos], t))
              {

                 if (pred(t, a[iMPos]))
                 {

                    return iMPos;

                 }
                 else
                 {

                    iLPos = iMPos + 1;

                 }

              }
              else
              {

                 if (!pred(t, a[iMPos]))
                 {

                    return iMPos;

                 }
                 else
                 {

                    iUPos = iMPos - 1;

                 }

              }

           }

           return -1;

        }



    } // namespace array


} // namespace acme



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
template < typename PRED >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::predicate_sort(PRED pred)
{

   ::acme::array::predicate_sort(*this, pred);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
template < typename T, typename PRED >
index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::predicate_binary_search(const T & t, PRED pred) const
{

   return ::acme::array::predicate_binary_search(*this, t, pred);

}


template < primitive_container CONTAINER1, primitive_container CONTAINER2 >
CONTAINER1 operator + (const CONTAINER1 & container1, const CONTAINER2 & container2)
{

   auto container = container1;

   container.append(container2);

   return ::transfer(container);

}



