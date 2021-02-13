#pragma once


template < typename ARG_TYPE >
index numeric_compare(ARG_TYPE t1, ARG_TYPE t2)
{
   typename ::remove_reference < ARG_TYPE >::TYPE t = t1 - t2;
   if(t > ::numeric_info< typename ::remove_reference < ARG_TYPE >::TYPE >::null())
      return 1;
   else if(t < ::numeric_info < typename ::remove_reference < ARG_TYPE >::TYPE >::null())
      return -1;
   else
      return 0;
}

namespace str
{


   template < >
   inline i64 from_string(const char * psz)
   {
      return to_i64(string(psz));
   }

} // namespace ::acme::str

template < typename TYPE >
class numeric_array :
   public comparable_raw_array < TYPE >
{
public:

   explicit numeric_array(::matter * pobject = nullptr) : comparable_raw_array < TYPE >(pobject) {}

   numeric_array(std::initializer_list < TYPE >  l):
      comparable_raw_array < TYPE >(l)
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

      this->move(::move(array));

   }


   //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(numeric_array, comparable_raw_array < TYPE >)

   typedef TYPE BASE_TYPE;
   typedef const TYPE & BASE_ARG_TYPE;
   typedef comparable_raw_array < TYPE > BASE_ARRAY;


   index find_first_maximum_value();
   TYPE & get_maximum_value();
   index find_first_minimum_value();
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

   TYPE get_total()
   {
      TYPE t = ::numeric_info < TYPE >:: null();
      for(index i = 0; i < this->get_count(); i++)
      {
         t+= this->element_at(i);
      }
      return t;
   }

   TYPE pop_to();


   void CopySorted(const numeric_array < TYPE > & array, TYPE & tOffset, TYPE & tMin);

   void Diff(
   const numeric_array  < TYPE > & array1,
   const numeric_array  < TYPE > & array2);

   void divide(TYPE i);

   void ElementDiff(
   const numeric_array  < TYPE > & array1,
   TYPE & tMax);

   TYPE simple_total_mean();

   void set(const TYPE & t, index iStart = 0, index iEnd = -1);

   index Cmp(const numeric_array  < TYPE > & array1);


   numeric_array unique() const;
   void unique();



   void implode(string & rwstr, const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string implode(const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;



   string surround_and_implode(const char * pcszSeparator = nullptr, const char * pszPrefix = nullptr, const char * pszSuffix = nullptr, index iStart = 0, ::count iCount = -1);



   numeric_array operator - (const numeric_array & a) const;
   numeric_array operator + (const numeric_array & a) const;

   numeric_array & operator -= (const numeric_array & a);
   numeric_array & operator += (const numeric_array & a);



   string & get_json(string & str, bool bNewLine = true) const;


   int compare(const numeric_array < TYPE > & a) const
   {

      ::count iCompare = this->get_size() - a.get_size();

      if(iCompare != 0)
         return ::papaya::sgn(iCompare);

      TYPE t;
      for(index i = 0; i < this->get_size(); i++)
      {

         t = this->element_at(i) - a[i];

         if(t != 0)
            return ::papaya::sgn(t);

      }

      return 0;

   }


   using comparable_raw_array < TYPE >::operator =;
   numeric_array & operator = (const numeric_array & a)
   {
      BASE_ARRAY::operator = (a);
      return *this;
   }


   numeric_array & operator = (numeric_array && a)
   {
      move(::move(a));
      return *this;
   }


   numeric_array & move (numeric_array && a)
   {
      BASE_ARRAY::move(::move(a));
      return *this;
   }


   void sort(bool bAsc = true);

};



template < class TYPE >
class unique_number_sort_array :
   public numeric_array < TYPE >
{
public:
   unique_number_sort_array();
   unique_number_sort_array(const unique_number_sort_array & array);

   index add(const TYPE & newElement)
   {
      index iFind = 0;
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

   bool find(const TYPE &t, index & find) const
   {
      index iL = find;
      index iU = this->get_upper_bound();
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

   /*index find_first_maximum_value();
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



template < typename T >
string & to_json(string & str, const T & t, bool bNewLine);


template < class TYPE >
string & numeric_array < TYPE >::get_json(string & str, bool bNewLine) const
{


   str += "[";

   if(this->get_count() > 0)
   {

      to_json(str, this->element_at(0), bNewLine);

   }

   for (index i = 1; i < this->get_count(); i++)
   {

      if (bNewLine)
      {

         str += ", \r\n";

      }
      else
      {

         str += ", ";

      }

      to_json(str, this->element_at(i), bNewLine);

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "]";

   return str;

}


template < class TYPE >
void numeric_array < TYPE >::implode(string & str, const char * pcszSeparator, index start, ::count count) const

{
   if(start < 0)
   {
      start += this->get_size();
   }
   index last;
   if(count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   if(start <= last)
   {
      string strSeparator(pcszSeparator);

      index i = start;
      str = __str(this->element_at(i));
      i++;
      for(; i <= last; i++)
      {
         str += strSeparator + __str(this->element_at(i));
      }
   }
   else
   {
      str.Empty();
   }
}

template < class TYPE >
string numeric_array < TYPE >::implode(const char * pcszSeparator, index iStart, index iEnd) const

{
   string str;
   implode(str, pcszSeparator, iStart, iEnd);

   return str;
}


template < class TYPE >
string numeric_array < TYPE >::surround_and_implode(const char * pszSeparator, const char * pszPrefix, const char * pszSuffix, index iStart, ::count iCount)
{
   string str;
   string strSeparator(pszSeparator);
   string strPrefix(pszPrefix);
   string strSuffix(pszSuffix);
   index iEnd;
   if(iStart < 0)
      iStart = this->get_size() + iStart;
   if(iCount < 0)
      iEnd = this->get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;
   if(iStart <= iEnd)
   {
      index i = iStart;
      str = strPrefix + __str(this->element_at(i)) + strSuffix;
      i++;
      for(; i <= iEnd; i++)
      {
         str += strSeparator + strPrefix + __str(this->element_at(i)) + strSuffix;
      }
   }
   return str;
}

//template < class TYPE >
//void numeric_array < TYPE >::each_add(const TYPE & t,::index i, ::count iEnd)
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
//template < class TYPE >
//void numeric_array < TYPE >::each_subtract(const TYPE & t,::index i,::count iEnd)
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
//      element_at(i) -= t;
//
//      i++;
//
//   }
//
//}



template < class TYPE >
numeric_array < TYPE > numeric_array < TYPE >::unique() const
{

   numeric_array < TYPE > a;

   for(i32 i = 0; i < this->get_count(); i++)
   {
      a.add_unique(this->element_at(i));
   }

   return a;

}

template < class TYPE >
void numeric_array < TYPE >::unique()
{

   numeric_array < TYPE > a;

   for(i32 i = 0; i < this->get_count(); i++)
   {
      a.add_unique(this->element_at(i));
   }

   *this = a;

}





template < class TYPE >
index numeric_array < TYPE >::
Cmp(const numeric_array  < TYPE > & array1)
{
   ::count iMinSize = minimum(array1.get_size(), this->get_size());
   index i = 0;
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

template < class TYPE >
void numeric_array < TYPE >::CopySorted(
const numeric_array  < TYPE > & a,
TYPE & tOffset,
TYPE & tMin)
{
   index i;
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
template < class TYPE >
void numeric_array < TYPE >::Diff(
const numeric_array  < TYPE > & array1,
const numeric_array  < TYPE > & array2)
{
   ASSERT(array1.get_size() == array2.get_size());
   index i;
   this->allocate(array1.get_size());
   TYPE t;
   for(i = 0; i < array1.get_size(); i++)
   {
      t = array1.get_at(i) - array2.get_at(i);
      this->set_at(i, t);
   }
}

template < class TYPE >
void numeric_array < TYPE >::ElementDiff(
const numeric_array  < TYPE > & a,
TYPE & tMax)
{
   index i;
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


template < class TYPE >
index numeric_array < TYPE >::find_first_maximum_value()
{

   TYPE tMax = this->element_at(0);

   index iFind = 0;

   for(index i = 1; i < this->get_size(); i++)
   {

      if (this->element_at(i) > tMax)
      {

         iFind = i;

         tMax = this->element_at(i);

      }

   }

   return iFind;

}


template < class TYPE >
TYPE & numeric_array < TYPE >::
get_maximum_value()
{
   ASSERT(this->get_size() > 0);
   return this->element_at(find_first_maximum_value());
}

template < class TYPE >
index numeric_array < TYPE >::find_first_minimum_value()
{

   TYPE tMin = this->element_at(0);

   index iFind = 0;

   for (index i = 1; i < this->get_size(); i++)
   {

      if (this->element_at(i) < tMin)
      {

         iFind = i;

         tMin = this->element_at(i);

      }

   }

   return iFind;

}


template < class TYPE >
TYPE & numeric_array < TYPE >::
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


template < class TYPE >
TYPE numeric_array < TYPE >::simple_total_mean()
{

   return ::simple_total_mean(this->get_data(), this->get_count());

}


template < class TYPE >
void numeric_array < TYPE >::set(const TYPE & t, ::index iStart, ::index iEnd)
{
   if(iEnd == -1)
      iEnd = this->get_upper_bound();
   for(index i = iStart; i <= iEnd; i++)
   {
      this->set_at(i, t);
   }
}


template < class TYPE >
void numeric_array < TYPE >::divide(TYPE div)
{
   index i;
   for(i = 0; i < this->get_size(); i++)
   {
      this->element_at(i) = this->element_at(i) / div;
   }
}

template < class TYPE >
numeric_array < TYPE >  numeric_array < TYPE >::operator - (const numeric_array < TYPE > & a) const
{

   numeric_array < TYPE > aRet(*this);

   aRet.remove_array(a);

   return aRet;

}

template < class TYPE >
numeric_array < TYPE >  numeric_array < TYPE >::operator + (const numeric_array < TYPE >  & a) const
{

   numeric_array < TYPE > aRet(*this);

   aRet.add(a);

   return aRet;

}

template < class TYPE >
numeric_array < TYPE >  & numeric_array < TYPE >::operator -= (const numeric_array < TYPE >  & a)
{

   this->remove_array(a);

   return *this;

}

template < class TYPE >
numeric_array < TYPE >  & numeric_array < TYPE >::operator += (const numeric_array < TYPE >  & a)
{

   this->add(a);

   return *this;

}



template < class TYPE >
inline void numeric_array < TYPE > ::push_last()
{

   this->add(this->last());

}


template < class TYPE >
inline TYPE numeric_array < TYPE > ::pop_max()
{

   TYPE lastelement = this->last();

   TYPE nowpop = this->pop();

   this->last() = maximum(nowpop, lastelement);

   return this->last();

}



template < class TYPE >
inline TYPE numeric_array < TYPE > ::pop_max_last_add_up(TYPE tLastAddUp)
{

   TYPE lastelement = this->last();

   TYPE nowpop = this->pop();

   this->last() = maximum(nowpop, lastelement + tLastAddUp);

   return this->last();

}



template < class TYPE >
inline TYPE numeric_array < TYPE > ::pop_to()
{

   TYPE lastelement = this->pop();

   this->last() = lastelement;

   return this->last();

}



template < class TYPE >
unique_number_sort_array < TYPE >::
unique_number_sort_array() 
{
}

template < class TYPE >
unique_number_sort_array < TYPE >::
unique_number_sort_array(const unique_number_sort_array < TYPE > & a) 
{
   numeric_array < TYPE > ::operator = (a);
}





















































namespace papaya
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
         for(index i = 0; i < c; i++)
         {
            f += a.element_at(i) / fCount;
         }
         return f;
      }

   } // namespace numeric_array

} // namespace papaya




namespace papaya
{

   namespace array
   {


      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index & iIndex,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE));

      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index & iIndex, less_pred_base < typename ARRAY::BASE_ARG_TYPE > * pcompare, index_array & ia);

      template<class ARRAY>
      index sort_add(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia)
      {
         index iIndex = 0;
         binary_search(a, t, iIndex, fCompare, ia);
         a.insert_at(iIndex, t);
         ia.add(iIndex);
         return iIndex;
      }

      template<class ARRAY, class ARRAY2>
      ::count sort_add_array(ARRAY & a,ARRAY2 & a2,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia)
      {
         for(index i = 0; i < a2.get_count(); i++)
         {
            sort_add(a,a2[i],fCompare,ia);
         }
         return a2.get_count();
      }


      template<class ARRAY>
      ::count sort_remove(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia)
      {
         ::count ca = 0;
         index iFind = 0;
         while(binary_search(a,t, iFind, fCompare, ia))
         {
            a.remove_at(iFind);
            index iIndex = ia[iFind];
            ia.remove_at(iFind);
            for(index i = 0; i < ia.get_size(); i++)
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


   template < typename TYPE >
   numeric_array_each < ::numeric_array < TYPE > > each(::numeric_array < TYPE > & a) { return a; }
   template < typename TYPE >
   numeric_array_each < ::numeric_array < TYPE > > all(::numeric_array < TYPE > & a) { return a; }
   template < typename TYPE >
   numeric_array_each < ::numeric_array < TYPE > > range(::numeric_array < TYPE > & a) { return a; }

   template < typename TYPE >
   numeric_array_range < ::numeric_array < TYPE > > each(::numeric_array < TYPE > & a,index iBeg,::count iCount) { return numeric_array_range < ::numeric_array < TYPE > >(a,iBeg,iCount); }
   template < typename TYPE >
   numeric_array_range < ::numeric_array < TYPE > > all(::numeric_array < TYPE > & a,index iBeg,::count iCount) { return numeric_array_range < ::numeric_array < TYPE > >(a,iBeg,iCount); }
   template < typename TYPE >
   numeric_array_range < ::numeric_array < TYPE > > range(::numeric_array < TYPE > & a,index iBeg,::count iCount) { return numeric_array_range <  ::numeric_array < TYPE > >(a,iBeg,iCount); }

   template < class TYPE >
   void quick_sort(::numeric_array < TYPE > & a, bool bAsc = true);

   template < class TYPE >
   ::count remove_greater_than(::numeric_array < TYPE > & a,TYPE hi)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) > hi)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < class TYPE >
   ::count remove_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE hi)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) >= hi)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < class TYPE >
   ::count remove_lesser_than(::numeric_array < TYPE > & a,TYPE lo)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) < lo)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < class TYPE >
   ::count remove_lesser_than_or_equal(::numeric_array < TYPE > & a,TYPE lo)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) <= lo)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < class TYPE >
   ::count remove_lesser_than_or_greater_than(::numeric_array < TYPE > & a,TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) < lo)
         {
            a.remove_at(i);
            ca++;
         }
         else if(a.element_at(i) > hi)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < class TYPE >
   ::count remove_lesser_than_or_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) < lo)
         {
            a.remove_at(i);
            ca++;
         }
         else if(a.element_at(i) >= hi)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < class TYPE >
   ::count remove_lesser_than_or_equal_or_greater_than(::numeric_array < TYPE > & a,TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) <= lo)
         {
            a.remove_at(i);
            ca++;
         }
         else if(a.element_at(i) > hi)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }


   template < class TYPE >
   ::count remove_lesser_than_or_equal_or_greater_than_or_equal(::numeric_array < TYPE > & a, TYPE lo,TYPE hi)
   {

      ::count ca = 0;

      for(index i = a.get_upper_bound(); i >= 0; i--)
      {
         if(a.element_at(i) <= lo)
         {
            a.remove_at(i);
            ca++;
         }
         else if(a.element_at(i) >= hi)
         {
            a.remove_at(i);
            ca++;
         }
      }

      return ca;

   }

} // namespace papaya


