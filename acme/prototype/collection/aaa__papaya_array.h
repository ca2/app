#pragma once


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type t_etypeContainer = e_type_element >
inline auto & __array_object(::array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & a, ::collection::index i);


template < typename ARRAY_TYPE, typename T >
inline auto & __array_object(::pointer_array_process < ARRAY_TYPE, T > & a, ::collection::index i);


namespace acme
{


   template < class TDST, class TSRC >
   ::collection::count copy(pointer_array < TDST > & dsta, const pointer_array < TSRC > & srca);


   template < class A, class T >
   A make_array(T t1)
   {

      A a;
      a.add(t1);
      return a;

   }


   namespace ptra
   {


      template < class TDST,class TSRC >
      ::collection::count copy(address_array < TDST > & dsta, const address_array < TSRC > & srca);

      template < class TDST, class TSRC >
      ::collection::count ptrcopy(TDST & dsta, const TSRC & srca);


   }


   namespace array
   {


      template < class TDST,class TSRC >
      ::collection::count copy(TDST & dsta,const TSRC & srca);

      template < typename CONTAINER, class TYPE >
      bool contains_item(const CONTAINER & container, const TYPE & t);


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
      void intersection(TINTERSECTION & intersection, const TDST & dsta, const TSRC & srca);

      template < class A >
      void randomize(A & a)
      {

         A b;

         while(a.get_count() > 0)
         {

            ::collection::index i = (index) (rand() % a.get_size());
            b.add(a.element_at(i));
            a.erase_at(i);

         }

         a = b;

      }


      template < class A >
      typename A::BASE_TYPE pick_random(A & a)
      {

         ::collection::index i = (index)(rand() % a.get_size());

         return a.element_at(i);

      }


      template < class A >
      typename A::BASE_TYPE pop_random(A & a)
      {

         ::collection::index i = (index)(rand() % a.get_size());

         auto matter = a.element_at(i);

         a.erase_at(i);

         return matter;

      }


      template < class A, class TYPE >
      ::collection::count populate(A & a, TYPE start, TYPE end, TYPE step, bool bIncludeStart = true, bool bIncludeEnd = true, bool bIncludeEndOnStep = true)
      {

         ::collection::count count = 0;

         TYPE cur = start;

         if(bIncludeStart)
         {

            if(start == end)
            {

               if(bIncludeEnd)
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

         if(end > start)
         {

            if (step == 0)
            {

               return count;

            }

            if (step < 0)
            {

               step = -step;

            }

            while(true)
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

            while(true)
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

         if(bIncludeEnd)
         {

            if(bIncludeEndOnStep)
            {

               if(cur == end)
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
      ::collection::index find_first(const ARRAY & a, typename ARRAY::BASE_ARG_TYPE t,index(* pfnCompare)(typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index find = 0,index last = -1)
      {

         if (find < 0)
         {

            find += a.get_count();

         }

         if (last < 0)
         {

            last += a.get_count();

         }

         for(; find <= last; find++)
         {

            if (pfnCompare((typename ARRAY::BASE_ARG_TYPE)a.element_at(find), (typename ARRAY::BASE_ARG_TYPE)t) == 0)
            {

               return find;

            }

         }

         return -1;

      }


      template < typename T >
      inline bool are_all_elements_equal(const pointer_array < T > & a1, const pointer_array < T > & a2)
      {

         if (a1.get_count() != a2.get_count())
         {

            return false;

         }

         for (int i = 0; i < a1.get_count(); i++)
         {

            if (a1.at(i) != a2.at(i))
            {

               return false;

            }

         }

         return true;

      }



      namespace every
      {

         template < typename A >
         bool ci_is(const A & a, const typename A::BASE_TYPE & t)
         {

            for (auto & i : a)
            {

               if (::case_insensitive_ansi_compare(i, t))
               {

                  return false;

               }

            }

            return true;

         }

         template < typename A >
         bool is_true(A && a)
         {

            for (auto & i : a)
            {

               if ((bool) i)
               {

                  return true;

               }

            }

            return false;

         }


      }


   } // namespace array



   template < class A >
   void array_merge(A & a, const A & a1, const A & a2)
   {
      a = a1 + a2;
   }

   template < class A >
   void array_makecombination(pointer_array < A > & comb, const A & a, A blindprefixa = A(), ::collection::index idx = 0)
   {
      comb.add(__allocate A(blindprefixa));
      for(::collection::index i = idx; i < a.get_count(); i++)
      {
         array_makecombination(comb, a, blindprefixa + make_array < A > (a[i]), i + 1);
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
   void array_permute(A2D & perm,const A & a);

   template < class A >
   void array_permute(pointer_array < A > & perm,const A & a);

   CLASS_DECL_ACME string_array x1_decode_ida(const ::scoped_string & scopedstr);

   CLASS_DECL_ACME string x1_encode_ida(const string_array & stra);


   template < class A >
   void x1_on_erase(const A & a, typename A::BASE_TYPE & n)
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
      ::collection::index add(string_array_base < Type, RawType, t_etypeContainer > & array, const Type & psz)
      {

         auto iIndex = __index(array.m_nSize);

         array.set_at_grow(iIndex, psz);

         return iIndex;

      }


      template < typename Type, typename RawType, ::enum_type t_etypeContainer >
      ::collection::index add(string_array_base < Type, RawType, t_etypeContainer > & array, const ::payload & payload);


      template < typename Type, typename RawType, ::enum_type t_etypeContainer >
      ::collection::index unfold_add(string_array_base < Type, RawType, t_etypeContainer > & array, const ::payload & payload);

      template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
      ::collection::count ensure_sequence(::numeric_array < TYPE, t_etypeContainer > & a, TYPE start, TYPE end, TYPE increment = 1);

      template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
      ::collection::count append_sequence(::numeric_array < TYPE, t_etypeContainer > & a, TYPE iterator, TYPE end, TYPE increment = 1);

      template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
      ::collection::count set_sequence(::numeric_array < TYPE, t_etypeContainer > & a, TYPE start, TYPE end, TYPE increment = 1);

      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,::collection::index & iIndex,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE));

      template<class ARRAY>
      bool binary_search(ARRAY & a, typename ARRAY::BASE_ARG_TYPE t, ::collection::index & iIndex, less_predicate_base < typename ARRAY::BASE_ARG_TYPE > * pcompare, index_array & ia);

      template<class ARRAY>
      ::collection::index sort_add(ARRAY & a, typename ARRAY::BASE_ARG_TYPE t, index(*fCompare) (typename ARRAY::BASE_ARG_TYPE, typename ARRAY::BASE_ARG_TYPE), index_array & ia);

      template<class ARRAY, class ARRAY2>
      ::collection::count sort_add_array(ARRAY & a, ARRAY2 & a2, index(*fCompare) (typename ARRAY::BASE_ARG_TYPE, typename ARRAY::BASE_ARG_TYPE), index_array & ia);

      template<class ARRAY>
      inline typename ARRAY::BASE_TYPE pop(ARRAY & a, ::collection::index n = -1);

      template<class ARRAY>
      inline void pop_back(ARRAY & a, ::collection::index n = -1);

      template<class ARRAY>
      inline ::collection::index push(ARRAY & a, typename ARRAY::BASE_ARG_TYPE newElement, ::collection::index n = 0);

      template<class ARRAY>
      inline void push_back(ARRAY & a, typename ARRAY::BASE_ARG_TYPE newElement, ::collection::index n = 0);

      template<class TARGET, class SOURCE> inline ::collection::index add(TARGET & target, const SOURCE & source)
      {

         return target.add(source);

      }


      template < typename ARRAY1, typename ARRAY2>
      inline ::collection::index add_array(ARRAY1 & array1, const ARRAY2 & array2)
      {

         ::collection::index i = -1;

         for (auto & item : array2)
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
      inline ::collection::index unfold_array(ARRAY1 & array1, const ARRAY2 & array2)
      {

         ::collection::index i = -1;

         for (auto & item : array2)
         {

            ::collection::index iItem = add(array1, item);

            if (i < 0)
            {

               i = iItem;

            }

         }

         return i;

      }


      inline ::collection::index add(string_array & stra, const ::scoped_string & scopedstr);
      inline ::collection::index add(string_array & stra, const char & ch);
      inline ::collection::index add(string_array & stra, const ansi_string & str);
      inline ::collection::index add(string_array & stra, const wide_string & str);
      inline ::collection::index add(string_array & stra, const ::file::path & path);
      inline ::collection::index add(string_array & stra, const ::payload & payload);
      inline ::collection::index add(string_array & stra, const ::property & property);
      inline ::collection::index add(string_array & stra, const ::property_set & propertyset);

      inline ::collection::index add(::file::path_array & patha, const ::string & str);

      inline ::collection::index add(string_array & stra, const string_array & straSource);

      inline ::collection::index add(::file::path_array & patha, const string_array & stra);
      inline ::collection::index add(::file::path_array & patha, const ::file::path_array & pathaSrc);
      inline ::collection::index add(::file::path_array & patha, const ::file::listing & listing);

      template < typename T >
      inline bool are_all_elements_equal(const pointer_array < T > & a1, const pointer_array < T > & a2);

      // t1 candidate bigger
      template < typename T1, typename  T2>
      inline bool contains_array(const T1 & t1, const T2 & t2);


      template < typename T1, typename  T2>
      inline ::collection::count erase_array(T1 & t1, T2 && t2);


      template < typename T1, typename  T2>
      inline bool equals_non_unique_unordered(const T1 & t1, const T2 & t2)
      {

         return ::papaya::array::contains_array(t1, t2) && ::papaya::array::contains_array(t2, t1);

      }

      template < typename A, typename PTRA >
      void ptra(PTRA & ptra, const A & a)
      {

         for (auto & item : a)
         {

            ptra.add((typename PTRA::BASE_TYPE) item);

         }

      }


      template < typename A >
      ::array < const char * > psza(const A & a)
      {

         ::array < const char * > pa;

         ptra(pa, a);

         pa.add(nullptr);

         return pa;

      }


      template < typename A, typename PA >
      void copy_points(A & a, const PA * pa, ::collection::count c);


   } // namespace array

   namespace array2d
   {

      template < typename A >
      ::collection::count predominant_column_count(A & a);

   } // namespace array2d

   
   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_greater_than(::numeric_array < TYPE, t_etypeContainer > & a, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_greater_than_or_equal(::numeric_array < TYPE, t_etypeContainer > & a, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than(::numeric_array < TYPE, t_etypeContainer > & a, TYPE lo);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_equal(::numeric_array < TYPE, t_etypeContainer > & a, TYPE lo);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_greater_than(::numeric_array < TYPE, t_etypeContainer > & a, TYPE lo, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_greater_than_or_equal(::numeric_array < TYPE, t_etypeContainer > & a, TYPE lo, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_equal_or_greater_than(::numeric_array < TYPE, t_etypeContainer > & a, TYPE lo, TYPE hi);


   template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
   ::collection::count erase_lesser_than_or_equal_or_greater_than_or_equal(::numeric_array < TYPE, t_etypeContainer > & a, TYPE lo, TYPE hi);


}   // namespace acme



