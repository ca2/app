// Created by camilo on 2022-11-08 16:53 <3ThomasBorregaardSorensen!!
#pragma once


#include "int_map.h"


namespace acme
{


   namespace array
   {


      template<primitive_array ARRAY1, primitive_array ARRAY2>
      bool is_equal(const ARRAY1 & array1, const ARRAY2 & array2)
      {

         if (array1.get_size() != array2.get_size())
         {

            return false;

         }

         for (::collection::index i = 0; i < array1.get_size(); i++)
         {

            if (array1.element_at(i) != array2.element_at(i))
            {

               return false;

            }

         }

         return true;

      }


      template<primitive_array ARRAY1, primitive_array ARRAY2>
      bool is_different(const ARRAY1 & array1, const ARRAY2 & array2)
      {

         return !is_equal(array1, array2);

      }


   } // namespace array
   

} // namespace acme





// From _papaya_array.h by camilo on 2022-10-22 18:18 <3ThomasBorregaardSorensen!!
// From _papaya_array_impl.h by camilo on 2022-10-22 18:07 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/collection/pointer_array_process.h"
#include "acme/prototype/prototype/compare_predicate.h"
//#include "acme/prototype/prototype/payload.h"
//#include "acme/prototype/prototype/payload_array.h"


template < class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::nodef < TYPE >, class MEMORY = ::heap::typed_memory < TYPE, ::heap::e_memory_array >, ::enum_type t_etypeContainer = e_type_element >
inline auto& __array_object(::array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >& a, ::collection::index i);


template < typename ARRAY_TYPE, typename T >
inline auto& __array_object(::pointer_array_process < ARRAY_TYPE, T >& a, ::collection::index i);


namespace acme
{


   template < class TDST, class TSRC >
   ::collection::count copy(pointer_array < TDST >& dsta, const pointer_array < TSRC >& srca);


   template < class A, class T >
   A make_array(T t1)
   {

      A a;
      a.add(t1);
      return a;

   }


   namespace ptra
   {


      template < class TDST, class TSRC >
      ::collection::count copy(address_array < TDST >& dsta, const address_array < TSRC >& srca);

      template < class TDST, class TSRC >
      ::collection::count ptrcopy(TDST& dsta, const TSRC& srca);


   }


   namespace array
   {


      template < class TDST, class TSRC >
      ::collection::count copy(TDST& dsta, const TSRC& srca);

      template < typename CONTAINER, class TYPE >
      bool contains_item(const CONTAINER& container, const TYPE& t);


      //#ifdef UNIVERSAL_WINDOWS
      //
      //      template < typename T, typename ITEM >
      //      inline ::collection::index find_first_item(::winrt::Windows::Foundation::Collections::IVectorImpact < T > ^ ivectorview, const ITEM & item)
      //      {
      //
      //         for (::u32 u = 0; u < ivectorview->Size; u++)
      //         {
      //
      //            if (ivectorview->GetAt(u) == item)
      //            {
      //
      //               return u;
      //
      //            }
      //
      //         }
      //
      //         return -1;
      //
      //      }
      //
      //
      //      template < typename T, typename ITEM >
      //      inline bool contains_item(::winrt::Windows::Foundation::Collections::IVectorImpact < T > ^ ivectorview, const ITEM & item)
      //      {
      //
      //         auto iFindFirst = find_first_item(ivectorview, item);
      //
      //         return iFindFirst >= 0;
      //
      //      }
      //
      //
      //#endif


      template < class TINTERSECTION, class TDST, class TSRC >
      void intersection(TINTERSECTION& intersection, const TDST& dsta, const TSRC& srca);

      template < class A >
      void randomize(A& a)
      {

         A b;

         while (a.get_count() > 0)
         {

            ::collection::index i = (::collection::index)(rand() % a.get_size());
            b.add(a.element_at(i));
            a.erase_at(i);

         }

         a = b;

      }


      template < class A >
      typename A::BASE_TYPE pick_random(A& a)
      {

         ::collection::index i = (::collection::index)(rand() % a.get_size());

         return a.element_at(i);

      }


      template < class A >
      typename A::BASE_TYPE pop_random(A& a)
      {

         ::collection::index i = (::collection::index)(rand() % a.get_size());

         auto matter = a.element_at(i);

         a.erase_at(i);

         return matter;

      }


      template < class A, class TYPE >
      ::collection::count populate(A& a, TYPE start, TYPE end, TYPE step, bool bIncludeStart = true, bool bIncludeEnd = true, bool bIncludeEndOnStep = true)
      {

         ::collection::count count = 0;

         TYPE cur = start;

         if (bIncludeStart)
         {

            if (start == end)
            {

               if (bIncludeEnd)
               {

                  a.add(cur);

                  return 1;

               }
               else
               {

                  return 0;

               }

            }
            else
            {

               a.add(cur);

               count++;

            }

         }

         if (end > start)
         {

            if (step == 0)
            {

               return count;

            }

            if (step < 0)
            {

               step = -step;

            }

            while (true)
            {

               cur = cur + step;

               if (cur >= end)
               {

                  break;

               }

               a.add(cur);

               count++;

            }

         }
         else
         {

            if (step == 0)
            {

               return count;

            }

            if (step < 0)
            {

               step = -step;

            }

            while (true)
            {

               cur = cur - step;

               if (cur <= end)
               {

                  break;

               }

               a.add(cur);

               count++;

            }

         }

         if (bIncludeEnd)
         {

            if (bIncludeEndOnStep)
            {

               if (cur == end)
               {

                  a.add(cur);

                  return count + 1;

               }
               else
               {

                  return count;

               }

            }
            else
            {

               a.add(cur);

               return count + 1;

            }

         }
         else
         {

            return count;

         }

      }


      template < typename ARRAY >
      ::collection::index find_first(const ARRAY& a, typename ARRAY::BASE_ARG_TYPE t, ::collection::index(*pfnCompare)(typename ARRAY::BASE_ARG_TYPE, typename ARRAY::BASE_ARG_TYPE), ::collection::index find = 0, ::collection::index last = -1)
      {

         if (find < 0)
         {

            find += a.get_count();

         }

         if (last < 0)
         {

            last += a.get_count();

         }

         for (; find <= last; find++)
         {

            if (pfnCompare((typename ARRAY::BASE_ARG_TYPE)a.element_at(find), (typename ARRAY::BASE_ARG_TYPE)t) == 0)
            {

               return find;

            }

         }

         return -1;

      }





      namespace every
      {

         template < typename A >
         bool ci_is(const A& a, const typename A::BASE_TYPE& t)
         {

            for (auto& i : a)
            {

               if (::case_insensitive_ansi_compare(i, t))
               {

                  return false;

               }

            }

            return true;

         }

         template < typename A >
         bool is_true(A&& a)
         {

            for (auto& i : a)
            {

               if ((bool)i)
               {

                  return true;

               }

            }

            return false;

         }


      }


   } // namespace array



   template < class A >
   void array_merge(A& a, const A& a1, const A& a2)
   {
      a = a1 + a2;
   }

   template < class A >
   void array_makecombination(pointer_array < A >& comb, const A& a, A blindprefixa = A(), ::collection::index idx = 0)
   {
      comb.add(__new A(blindprefixa));
      for (::collection::index i = idx; i < a.get_count(); i++)
      {
         array_makecombination(comb, a, blindprefixa + make_array < A >(a[i]), i + 1);
      }
   }

   /*
   function array_arrange($a)
   {
   $comb = array_makecombination($a);
   $ret = array();
   $count = count($comb);
   foreach($comb as $ai)
   {
      if(count($ai) > 0)
         $ret = array_merge($ret, array_permute($ai));
   }
   return $ret;
   }*/

   template < class A, class A2D >
   void array_permute(A2D& perm, const A& a);

   template < class A >
   void array_permute(pointer_array < A >& perm, const A& a);

   CLASS_DECL_ACME string_array x1_decode_ida(const ::scoped_string & scopedstr);

   CLASS_DECL_ACME string x1_encode_ida(const string_array& stra);


   template < class A >
   void x1_on_erase(const A& a, typename A::BASE_TYPE& n)
   {
      ::collection::count c = 0;
      for (::collection::index i = 0; i < a.get_size(); i++)
      {
         if (a[i] < n)
         {
            c++;
         }
      }
      n -= c;
   }


   namespace array
   {


      //template < typename TYPE >
      //::stream & write_container_as_parent(::stream & stream, const pointer_array < TYPE > & a);

      //template < typename TYPE >
      //::stream & read_container_as_parent(::stream & stream, pointer_array < TYPE > & a);

      //template < typename TYPE, typename INITIALIZER >
      //::stream & exchange_container(::stream & stream, INITIALIZER * pinitializer, const pointer_array < TYPE > & a);

      template < typename Type, typename RawType, ::enum_type t_etypeContainer >
      ::collection::index add(string_array_base < Type, RawType, t_etypeContainer >& array, const Type& psz)
      {

         auto iIndex = __index(array.m_nSize);

         array.set_at_grow(iIndex, psz);

         return iIndex;

      }


      template < typename Type, typename RawType, ::enum_type t_etypeContainer >
      ::collection::index add(string_array_base < Type, RawType, t_etypeContainer >& array, const ::payload& payload);


      template < typename Type, typename RawType, ::enum_type t_etypeContainer >
      ::collection::index unfold_add(string_array_base < Type, RawType, t_etypeContainer >& array, const ::payload& payload);

      template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
      ::collection::count ensure_sequence(::numeric_array < TYPE, t_etypeContainer >& a, TYPE start, TYPE end, TYPE increment = 1);

      template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
      ::collection::count append_sequence(::numeric_array < TYPE, t_etypeContainer >& a, TYPE iterator, TYPE end, TYPE increment = 1);

      template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
      ::collection::count set_sequence(::numeric_array < TYPE, t_etypeContainer >& a, TYPE start, TYPE end, TYPE increment = 1);

      template<class ARRAY>
      bool binary_search(ARRAY& a, typename ARRAY::BASE_ARG_TYPE t, ::collection::index& iIndex, ::collection::index(*fCompare) (typename ARRAY::BASE_ARG_TYPE, typename ARRAY::BASE_ARG_TYPE));

      template<class ARRAY>
      bool binary_search(ARRAY& a, typename ARRAY::BASE_ARG_TYPE t, ::collection::index& iIndex, less_predicate_base < typename ARRAY::BASE_ARG_TYPE >* pcompare, index_array& ia);

      template<class ARRAY>
      ::collection::index sort_add(ARRAY& a, typename ARRAY::BASE_ARG_TYPE t, ::collection::index(*fCompare) (typename ARRAY::BASE_ARG_TYPE, typename ARRAY::BASE_ARG_TYPE), index_array& ia);

      template<class ARRAY, class ARRAY2>
      ::collection::count sort_add_array(ARRAY& a, ARRAY2& a2, ::collection::index(*fCompare) (typename ARRAY::BASE_ARG_TYPE, typename ARRAY::BASE_ARG_TYPE), index_array& ia);

      template<class ARRAY>
      inline typename ARRAY::BASE_TYPE pop(ARRAY& a, ::collection::index n = -1);

      template<class ARRAY>
      inline void pop_back(ARRAY& a, ::collection::index n = -1);

      template<class ARRAY>
      inline ::collection::index push(ARRAY& a, typename ARRAY::BASE_ARG_TYPE newElement, ::collection::index n = 0);

      template<class ARRAY>
      inline void add(ARRAY& a, typename ARRAY::BASE_ARG_TYPE newElement, ::collection::index n = 0);

      template<class TARGET, class SOURCE> inline ::collection::index add(TARGET& target, const SOURCE& source)
      {

         return target.add(source);

      }


      template < typename ARRAY1, typename ARRAY2>
      inline ::collection::index add_array(ARRAY1& array1, const ARRAY2& array2)
      {

         ::collection::index i = -1;

         for (auto& item : array2)
         {

            ::collection::index iItem = array1.add_item(item);

            if (i < 0)
            {

               i = iItem;

            }

         }

         return i;

      }


      template < typename ARRAY1, typename ARRAY2>
      inline ::collection::index unfold_array(ARRAY1& array1, const ARRAY2& array2)
      {

         ::collection::index i = -1;

         for (auto& item : array2)
         {

            ::collection::index iItem = add(array1, item);

            if (i < 0)
            {

               i = iItem;

            }

         }

         return i;

      }


      inline ::collection::index add(string_array& stra, const ::scoped_string & scopedstr);
      inline ::collection::index add(string_array& stra, const char& ch);
      inline ::collection::index add(string_array& stra, const ansi_string& str);
      inline ::collection::index add(string_array& stra, const wide_string& str);
      inline ::collection::index add(string_array& stra, const ::file::path& path);
      inline ::collection::index add(string_array& stra, const ::payload& payload);
      inline ::collection::index add(string_array& stra, const ::property& property);
      inline ::collection::index add(string_array& stra, const ::property_set& propertyset);

      inline ::collection::index add(::file::path_array& patha, const ::string& str);

      inline ::collection::index add(string_array& stra, const string_array& straSource);

      inline ::collection::index add(::file::path_array& patha, const string_array& stra);
      inline ::collection::index add(::file::path_array& patha, const ::file::path_array& pathaSrc);
      inline ::collection::index add(::file::path_array& patha, const ::file::listing& listing);

      template < typename T >
      inline bool are_all_elements_equal(const pointer_array < T >& a1, const pointer_array < T >& a2);

      // t1 candidate bigger
      template < typename T1, typename  T2>
      inline bool contains_array(const T1& t1, const T2& t2);


      template < typename T1, typename  T2>
      inline ::collection::count erase_array(T1& t1, T2&& t2);


      template < typename T1, typename  T2>
      inline bool equals_non_unique_unordered(const T1& t1, const T2& t2)
      {

         return ::acme::array::contains_array(t1, t2) && ::acme::array::contains_array(t2, t1);

      }

      template < typename A, typename PTRA >
      void ptra(PTRA& ptra, const A& a)
      {

         for (auto& item : a)
         {

            ptra.add((typename PTRA::BASE_TYPE) item);

         }

      }


      template < typename A >
      ::array < const char* > psza(const A& a)
      {

         ::array < const char* > pa;

         ptra(pa, a);

         pa.add(nullptr);

         return pa;

      }


      template < typename A, typename PA >
      void copy_points(A& a, const PA* pa, ::collection::count c);


   } // namespace array

   namespace array2d
   {

      template < typename A >
      ::collection::count predominant_column_count(A& a);

   } // namespace array2d


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_greater_than(::numeric_array < TYPE, t_etypeContainer >& a, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_greater_than_or_equal(::numeric_array < TYPE, t_etypeContainer >& a, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than(::numeric_array < TYPE, t_etypeContainer >& a, TYPE lo);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_equal(::numeric_array < TYPE, t_etypeContainer >& a, TYPE lo);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_greater_than(::numeric_array < TYPE, t_etypeContainer >& a, TYPE lo, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_greater_than_or_equal(::numeric_array < TYPE, t_etypeContainer >& a, TYPE lo, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_equal_or_greater_than(::numeric_array < TYPE, t_etypeContainer >& a, TYPE lo, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_equal_or_greater_than_or_equal(::numeric_array < TYPE, t_etypeContainer >& a, TYPE lo, TYPE hi);


}   // namespace acme






namespace acme
{


   namespace array
   {


      //template < typename ARRAY >
      //inline void load(ARRAY & a, stream & s)
      //{

      //   ::collection::count cSerialized = 0;

      //   ::collection::count c = 0;

      //   s >> c;

      //   //if (!s.fail())
      //   /*{

      //      try
      //      {*/

      //   for (::collection::index i = 0; i < c; i++)
      //   {

      //      a.set_size(i + 1, minimum((size_t)(c - i), 96_mb / sizeof(a[0])));

      //      auto & item = __typed(a[i]);

      //      s >> item;

      //      cSerialized++;

      //      //if (s.fail())
      //      //{

      //      //   break;

      //      //}

      //   }

      //   //}
      //   //catch (...)
      //   //{

      //   //   //s.set_fail_bit();

      //   //}

      //   //if (s.fail())
      //   {

      //      a.set_size(cSerialized);

      //   }

      //   //}

      //}


      //template < typename TYPE >
      //::stream & exchange_container_as_parent(::stream & stream, const pointer_array < TYPE > & a)
      //{

      //   ::collection::count c = a.get_count();

      //   stream.exchange(::atom(), c);

      //   //if (stream.fail())
      //   //{

      //   //   return stream;

      //   //}

      //   for (::collection::index i = 0; i < c; i++)
      //   {

      //      auto & pitem = ((pointer_array < TYPE > &) a).element_at_grow(i);

      //      if (!pitem)
      //      {

      //         pitem = __new TYPE(&(pointer_array < TYPE > &)a);

      //      }

      //      pitem->exchange(stream);

      //      //if (stream.fail())
      //      //{

      //      //   break;

      //      //}

      //   }

      //   return stream;

      //}


      //template < typename TYPE, typename INITIALIZER >
      //::stream & exchange_container(::stream & stream, INITIALIZER * pinitializer, const pointer_array < TYPE > & a)
      //{

      //   ::collection::count c = a.get_count();

      //   stream.exchange(::atom(), c);

      //   //if (stream.fail())
      //   //{

      //   //   return stream;

      //   //}

      //   for (::collection::index i = 0; i < c; i++)
      //   {

      //      auto & pitem = ((pointer_array < TYPE > &) a).element_at_grow(i);

      //      if (!pitem)
      //      {

      //         pinitializer->__initialize(pitem);

      //         //pitem = __new TYPE(&(pointer_array < TYPE > &)a);

      //      }

      //      pitem->exchange(stream);

      //      //if (stream.fail())
      //      //{

      //      //   break;

      //      //}

      //   }

      //   return stream;

      //}


      //template < typename TYPE >
      //::stream & write_container_as_parent(::stream & stream, const pointer_array < TYPE > & a)
      //{

      //   ::collection::count c = a.get_count();

      //   stream << c;

      //   //if (stream.fail())
      //   //{

      //   //   return stream;

      //   //}

      //   for (auto & item : a)
      //   {

      //      stream << item;

      //      c--;

      //   }

      //   return stream;

      //}


      template < typename Type, typename RawType, ::enum_type t_etypeContainer >
      ::collection::index add(string_array_base < Type, RawType, t_etypeContainer >& array, const ::payload& payload)
      {

         ::collection::index i = -1;

         if (payload.is_empty())
         {

         }
         else if (payload.get_type() == ::e_type_string_array)
         {

            i = ::acme::array::add(array, payload.as_string_array());

         }
         else if (payload.cast < string_array_base < Type, RawType, t_etypeContainer > >() != nullptr)
         {

            i = ::acme::array::add(array, *payload.cast < string_array_base < Type, RawType, t_etypeContainer > >());

         }
         else if (payload.get_type() == ::e_type_payload_array)
         {

            for (::collection::index i = 0; i < payload.as_payload_array().get_count(); i++)
            {

               ::collection::index iItem = ::acme::array::add(array, payload.as_payload_array()[i]);

               if (i < 0)
               {

                  i = iItem;

               }

            }

         }
         else if (payload.get_type() == ::e_type_i32_array)
         {

            array.copy(payload.as_i32_array());

         }
         else if (payload.get_type() == ::e_type_property_set)
         {

            auto & set = payload.property_set_reference();

            for (auto& property : set)
            {

               auto iItem = ::acme::array::add(array, property);

               if (i < 0)
               {

                  i = iItem;

               }

            }

         }
         else
         {

            i = ::acme::array::add(array, payload);

         }

         return i;

      }


      //template < typename TYPE >
      //::stream & read_container_as_parent(::stream & stream, pointer_array < TYPE > & a)
      //{

      //   ::collection::count c = 0;

      //   stream >> c;

      //   //if (stream.fail())
      //   //{

      //   //   return stream;

      //   //}

      //   while (c > 0)
      //   {

      //      auto p = __new TYPE(&a);

      //      stream >> *p;

      //      /*          if (stream.fail())
      //                {

      //                   break;

      //                }*/

      //      a.add(p);

      //      c--;

      //   }

      //   return stream;

      //}


      template < class TDST, class TSRC >
      ::collection::count copy(TDST& dsta, const TSRC& srca)
      {

         dsta.erase_all();

         for (int i = 0; i < srca.get_size(); i++)
         {

            dsta.add((typename TDST::BASE_TYPE) srca[i]);

         }

         return dsta.get_count();

      }


      //template < class TDST, class TSRC >
      //::collection::count copy(TDST & dsta, const TSRC & srca);


      template < typename CONTAINER, class TYPE >
      bool contains_item(const CONTAINER& container, const TYPE& t)
      {

         for (auto& item : container)
         {

            if (item == t)
            {

               return true;

            }

         }

         return false;

      }


      // t1 candidate bigger
      template < typename T1, typename  T2>
      inline bool contains_array(const T1& t1, const T2& t2)
      {

         for (auto& t : t2)
         {

            if (!contains_item(t1, t))
            {

               return false;

            }

         }

         return true;

      }




      template < class TINTERSECTION, class TDST, class TSRC >
      void intersection(TINTERSECTION& intersection, const TDST& dsta, const TSRC& srca)
      {

         intersection.clear();

         for (auto& item : dsta)
         {

            if (contains_item(srca, item))
            {

               intersection.add(item);

            }

         }

      }

      template < typename T1, typename  T2>
      inline ::collection::count erase_array(T1& t1, T2&& t2)
      {

         ::collection::count c = 0;

         for (auto& t : t2)
         {

            c += t1.erase(t);

         }

         return c;

      }




      //template < class TDST, class TSRC >
      //::collection::count copy(TDST & dsta, const TSRC & srca)
      //{

      //   ::collection::count c = srca.get_count();

      //   dsta.set_size(c);

      //   for (int i = 0; i < c; i++)
      //   {

      //      dsta[i] = (typename TDST::BASE_TYPE) srca[i];

      //   }

      //   return c;

      //}

      //template < class ARRAY >
      //::collection::count copy_same_class(ARRAY & dsta, const ARRAY & srca)
      //{

      //   ::collection::count c = srca.get_count();

      //   dsta.set_size(c);

      //   for (int i = 0; i < c; i++)
      //   {

      //      dsta[i] = srca[i];

      //   }

      //   return c;

      //}


      template < typename A, typename PA >
      void copy_points(A& a, const PA* pa, ::collection::count c)
      {

         a.set_size(c);

         for (::collection::index i = 0; i < c; i++)
         {

            a[i] = (typename A::BASE_TYPE) pa[i];

         }

      }

   } // namespace array


   template < class TDST, class TSRC >
   ::collection::count copy(pointer_array < TDST >& dsta, const pointer_array < TSRC >& srca)
   {

      ::collection::count ca = 0;

      dsta.erase_all();

      for (int i = 0; i < srca.get_size(); i++)
      {
         dsta.add(__new TSRC(srca(i)));
         ca++;
      }

      return ca;

   }

   namespace ptra
   {

      template < class TDST, class TSRC >
      ::collection::count copy(address_array < TDST >& dsta, const address_array < TSRC >& srca)
      {

         ::collection::count ca = 0;

         dsta.erase_all();

         for (int i = 0; i < srca.get_size(); i++)
         {
            dsta.add(new TSRC (srca(i)));
            ca++;
         }

         return ca;

      }

      template < class TDST, class TSRC >
      ::collection::count ptrcopy(TDST& dsta, const TSRC& srca)
      {

         ::collection::count ca = 0;

         dsta.erase_all();

         for (int i = 0; i < srca.get_size(); i++)
         {
            dsta.add(srca[i]);
            ca++;
         }

         return ca;

      }

   }


   template < class A, class A2D >
   void array_permute(A2D& perm, const A& a)
   {
      ::collection::count count = a.get_count();
      if (count == 1)
      {
         perm.add(a);
         return;
      }
      A elema;
      A topermut;
      A2D perm2;
      for (i32 i = 0; i < count; i++)
      {
         elema.erase_all();
         elema.add(a[i]);
         topermut.erase_all();
         for (i32 j = 0; j < i; j++)
         {
            topermut.add(a[j]);
         }
         for (i32 j = i + 1; j < count; j++)
         {
            topermut.add(a[j]);
         }
         perm2.erase_all();
         array_permute(perm2, topermut);
         for (i32 j = 0; j < perm2.get_count(); j++)
         {
            perm.add(elema + perm2[j]);
         }
      }
   }

   template < class A >
   void array_permute(pointer_array < A >& perm, const A& a)
   {
      ::collection::count count = a.get_count();
      if (count == 1)
      {
         perm.add(__new A(a));
         return;
      }
      A elema;
      A topermut;
      pointer_array < A > perm2;
      for (i32 i = 0; i < count; i++)
      {
         elema.erase_all();
         elema.add(a[i]);
         topermut.erase_all();
         for (i32 j = 0; j < i; j++)
         {
            topermut.add(a[j]);
         }
         for (i32 j = i + 1; j < count; j++)
         {
            topermut.add(a[j]);
         }
         perm2.erase_all();
         array_permute(perm2, topermut);
         for (i32 j = 0; j < perm2.get_count(); j++)
         {
            perm.add(__new A(elema + perm2[j]));
         }
      }
   }

} // namespace array






namespace acme
{


   namespace array
   {



      /////////////////////
      ////
      ////   Adding ITEM
      ////      to array

      ////inline ::collection::index add(string_array & stra, const ::scoped_string & scopedstr) { return stra.add_item(psz); }
      ////inline ::collection::index add(string_array & stra, const char & ch) { return stra.add_item(ch); }
      ////inline ::collection::index add(string_array & stra, const ansi_string & str) { return stra.add_item(str); }
      ////inline ::collection::index add(string_array & stra, const wd16_string & str) { return stra.add_item(str); }
      ////inline ::collection::index add(string_array & stra, const wd32_string & str) { return stra.add_item(str); }
      ////inline ::collection::index add(string_array & stra, const ::file::path & path) { return stra.add_item(path); }


      ////inline ::collection::index add(::file::path_array & patha, const ::scoped_string & scopedstr) { return patha.add_item(psz); }
      ////inline ::collection::index add(::file::path_array & patha, const char & ch) { return patha.add_item(ch); }
      ////inline ::collection::index add(::file::path_array & patha, const ansi_string & str) { return patha.add_item(str); }
      ////inline ::collection::index add(::file::path_array & patha, const wd16_string & str) { return patha.add_item(str); }
      ////inline ::collection::index add(::file::path_array & patha, const wd32_string & str) { return patha.add_item(str); }
      ////inline ::collection::index add(::file::path_array & patha, const ::file::path & path) { return patha.add_item(path); }


      //inline ::collection::index add(string_array & stra, const ::payload & payload)
      //{

      //   ::collection::index iInsert = -1;

      //   if (payload.is_array())
      //   {

      //      ::collection::count c = payload.array_get_count();

      //      for (::collection::index i = 0; i < c; i++)
      //      {

      //         auto iItem = stra.add_item(payload.at(i));

      //         if (iInsert < 0)
      //         {

      //            iInsert = iItem;

      //         }

      //      }

      //   }
      //   else
      //   {

      //      iInsert = stra.add_item(payload);

      //   }

      //   return iInsert;

      //}

      //inline ::collection::index add(string_array & stra, const ::property & property)
      //{

      //   return add(stra, (const ::payload &)property);

      //}

      //inline ::collection::index add(string_array & stra, const ::property_set & propertyset)
      //{

      //   ::collection::index iInsert = -1;

      //   ::collection::count c = propertyset.get_count();

      //   for (::collection::index i = 0; i < c; i++)
      //   {

      //      auto iItem = stra.add_item(*propertyset.element_at(i));

      //      if (iInsert < 0)
      //      {

      //         iInsert = iItem;

      //      }

      //   }

      //   return iInsert;

      //}



      ///////////////////////////////////////
      //
      //   Appending ARRAY
      //          to array

      //inline ::collection::index add(string_array & stra, const string_array & straSource) { return add_array(stra, straSource); }

      //inline ::collection::index add(::file::path_array & patha, const string_array & stra) { return add_array(patha, stra); }
      //inline ::collection::index add(::file::path_array & patha, const ::file::path_array & pathaSrc) { return add_array(patha, pathaSrc); }
      //inline ::collection::index add(::file::path_array & patha, const ::file::listing & listing) { return add_array(patha, listing); }


      //template < typename TYPE, ::enum_type t_etypeContainer >
      //::collection::count ensure_sequence(::numeric_array < TYPE, t_etypeContainer > & aParam, TYPE start, TYPE end, TYPE increment)
      //{

      //   ::collection::count c = 0;

      //   ::numeric_array < TYPE, t_etypeContainer > a;

      //   ::acme::array::set_sequence(a, start, end, increment);

      //   c += erase_lesser_than_or_greater_than(aParam, start, end);

      //   for (::collection::index i = aParam.get_upper_bound(); i >= 0; i--)
      //   {

      //      auto pFind = 0;

      //      if (::acme::array::binary_search(a, aParam.element_at(i), iFind, &::numeric_compare < typename ::numeric_array < TYPE, t_etypeContainer >::BASE_ARG_TYPE >))
      //      {

      //         a.erase_at(iFind);

      //         c++;

      //      }
      //      else
      //      {

      //         aParam.erase_at(i);

      //         c++;

      //      }

      //   }

      //   c += aParam.add(a);

      //   return c;

      //}


      template<class ARRAY>
      bool binary_search(ARRAY& a, typename ARRAY::BASE_ARG_TYPE t, ::collection::index& iIndex, ::collection::index(*fCompare) (typename ARRAY::BASE_ARG_TYPE, typename ARRAY::BASE_ARG_TYPE))
      {

         if (a.get_size() == 0)
         {
            return false;
         }

         ::collection::index iLowerBound = 0;
         ::collection::index iMaxBound = a.get_upper_bound();
         ::collection::index iUpperBound = iMaxBound;
         ::collection::index iCompare;
         // do binary search
         iIndex = (iUpperBound + iLowerBound) / 2;
         while (iUpperBound - iLowerBound >= 8)
         {
            iCompare = fCompare(a.element_at(iIndex), t);
            if (iCompare == 0)
            {
               return true;
            }
            else if (iCompare > 0)
            {
               iUpperBound = iIndex - 1;
               if (iUpperBound < 0)
               {
                  iIndex = 0;
                  break;
               }
            }
            else
            {
               iLowerBound = iIndex + 1;
               if (iLowerBound > iMaxBound)
               {
                  iIndex = iMaxBound + 1;
                  break;
               }
            }
            iIndex = (iUpperBound + iLowerBound) / 2;
         }
         // do sequential search
         while (iIndex < a.get_count())
         {
            iCompare = fCompare(a.element_at(iIndex), t);
            if (iCompare == 0)
               return true;
            else if (iCompare < 0)
               iIndex++;
            else
               break;
         }
         if (iIndex >= a.get_count())
            return false;
         while (iIndex >= 0)
         {
            iCompare = fCompare(a.element_at(iIndex), t);
            if (iCompare == 0)
               return true;
            else if (iCompare > 0)
               iIndex--;
            else
               break;
         }
         iIndex++;
         return false;

      }


      template<class ARRAY>
      bool binary_search(ARRAY& a, typename ARRAY::BASE_ARG_TYPE t, ::collection::index& iIndex, less_predicate_base < typename ARRAY::BASE_ARG_TYPE >* pless, index_array& ia)
      {

         if (a.get_size() == 0)
         {

            return false;

         }

         ::collection::index iLowerBound = 0;
         ::collection::index iMaxBound = a.get_upper_bound();
         ::collection::index iUpperBound = iMaxBound;
         ::collection::index iCompare;

         // do binary search
         iIndex = (iUpperBound + iLowerBound) / 2;

         while (iUpperBound - iLowerBound >= 8)
         {

            iCompare = pless->less(a.element_at(iIndex), t);

            if (iCompare == 0)
            {

               return true;

            }
            else if (iCompare > 0)
            {

               iUpperBound = iIndex - 1;

               if (iUpperBound < 0)
               {

                  iIndex = 0;

                  break;

               }

            }
            else
            {

               iLowerBound = iIndex + 1;

               if (iLowerBound > iMaxBound)
               {

                  iIndex = iMaxBound + 1;

                  break;

               }

            }

            iIndex = (iUpperBound + iLowerBound) / 2;

         }

         // do sequential search
         while (iIndex < a.get_count())
         {

            iCompare = pless->less(a.element_at(iIndex), t);

            if (iCompare == 0)
            {

               return true;

            }

            else if (iCompare < 0)
            {

               iIndex++;

            }
            else
            {

               break;

            }

         }

         if (iIndex >= a.get_count())
         {

            return false;

         }

         while (iIndex >= 0)
         {

            iCompare = pless->less(a.element_at(iIndex), t);

            if (iCompare == 0)
            {

               return true;

            }

            else if (iCompare > 0)
            {

               iIndex--;

            }
            else
            {

               break;

            }

         }

         iIndex++;

         return false;

      }


      template < typename TYPE, ::enum_type t_etypeContainer >
      ::collection::count append_sequence(::numeric_array < TYPE, t_etypeContainer >& a, TYPE iterator, TYPE end, TYPE increment)
      {
         if (increment == 0)
         {
            a.add(iterator);
            a.add(end);
            return 2;
         }
         else if (increment > 0)
         {
            ::collection::count ca = 0;
            for (; iterator <= end; iterator += increment)
            {
               a.add(iterator);
               ca++;
            }
            return ca;
         }
         else
         {
            ::collection::count ca = 0;
            for (; iterator >= end; iterator += increment)
            {
               a.add(iterator);
               ca++;
            }
            return ca;
         }
      }


      template < typename TYPE, ::enum_type t_etypeContainer >
      ::collection::count set_sequence(::numeric_array < TYPE, t_etypeContainer >& a, TYPE start, TYPE end, TYPE increment)
      {
         a.erase_all();
         return append_sequence(a, start, end, increment);
      }


      template < typename ARRAY >
      inline typename ARRAY::BASE_TYPE pop(ARRAY& a, ::collection::index n)
      {

         ::collection::index i = a.get_upper_bound(n);

         typename ARRAY::TYPE t = a.element_at(i);

         a.erase_at(i);

         return t;

      }


      template < typename ARRAY >
      inline void pop_back(ARRAY& a, ::collection::index n)
      {

         a.erase_at(a.get_upper_bound(n));

      }


      template < typename ARRAY >
      inline ::collection::index push(ARRAY& a, typename ARRAY::BASE_ARG_TYPE newElement, ::collection::index n)
      {

         return a.insert_at(a.get_upper_bound(n), newElement);

      }


      template < typename ARRAY >
      inline void add(ARRAY& a, typename ARRAY::BASE_ARG_TYPE newElement, ::collection::index n)
      {

         a.insert_at(a.get_upper_bound(n), newElement);

      }


   } //namespace array


} // namespace acme





namespace acme
{


   namespace array2d
   {

      template < typename A >
      ::collection::count predominant_column_count(A& a)
      {

         index_to_index column_count;

         for (::collection::index i = 0; i < a.get_size(); i++)
         {

            column_count[a[i].get_count()]++;

         }

         ::collection::count c = -1;

         ::collection::count cMax = -1;

         for (auto& assoc : column_count)
         {

            if (assoc.element2() > cMax || (assoc.element2() == cMax && assoc.element1() > c))
            {

               c = assoc.element1();

               cMax = assoc.element2();

            }

         }

         return c;

      }


   } //namespace array2d


} // namespace acme



