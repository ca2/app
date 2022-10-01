#pragma once


namespace papaya
{


   namespace array
   {


      template < typename ARRAY >
      inline void load(ARRAY & a, stream & s)
      {

         ::count cSerialized = 0;

         ::count c = 0;

         s >> c;

         //if (!s.fail())
         /*{

            try
            {*/

               for (::index i = 0; i < c; i++)
               {

                  a.set_size(i + 1, minimum((size_t)(c - i), 96_mb / sizeof(a[0])));

                  auto & item = __typed(a[i]);

                  s >> item;

                  cSerialized++;

                  //if (s.fail())
                  //{

                  //   break;

                  //}

               }

            //}
            //catch (...)
            //{

            //   //s.set_fail_bit();

            //}

            //if (s.fail())
            {

               a.set_size(cSerialized);

            }

         //}

      }


      template < typename TYPE >
      ::stream & exchange_container_as_parent(::stream & stream, const __pointer_array(TYPE) & a)
      {

         ::count c = a.get_count();

         stream.exchange(::atom(), c);

         //if (stream.fail())
         //{

         //   return stream;

         //}

         for (index i = 0; i < c; i++)
         {

            auto & pitem = ((__pointer_array(TYPE) &) a).element_at_grow(i);

            if (!pitem)
            {

               pitem = __new(TYPE(&(__pointer_array(TYPE) &)a));

            }

            pitem->exchange(stream);

            //if (stream.fail())
            //{

            //   break;

            //}

         }

         return stream;

      }


      template < typename TYPE, typename INITIALIZER >
      ::stream & exchange_container(::stream & stream, INITIALIZER * pinitializer, const __pointer_array(TYPE) & a)
      {

         ::count c = a.get_count();

         stream.exchange(::atom(), c);

         //if (stream.fail())
         //{

         //   return stream;

         //}

         for(index i = 0; i < c; i++)
         {

            auto & pitem = ((__pointer_array(TYPE) &) a).element_at_grow(i);

            if (!pitem)
            {

               pinitializer->__initialize(pitem);

               //pitem = __new(TYPE(&(__pointer_array(TYPE) &)a));

            }

            pitem->exchange(stream);

            //if (stream.fail())
            //{

            //   break;

            //}

         }

         return stream;

      }


      template < typename TYPE >
      ::stream & write_container_as_parent(::stream & stream, const __pointer_array(TYPE) & a)
      {

         ::count c = a.get_count();

         stream << c;

         //if (stream.fail())
         //{

         //   return stream;

         //}

         for (auto & item : a)
         {

            stream << item;

            c--;

         }

         return stream;

      }


      template < typename Type, typename RawType, enum_type t_etypePayload >
      ::index add(string_array_base < Type, RawType, t_etypePayload > & array, const ::payload & payload)
      {

         index i = -1;

         if (payload.is_empty())
         {

         }
         else if (payload.get_type() == ::e_type_string_array)
         {

            i = ::papaya::array::add(array, payload.stra());

         }
         else if (payload.cast < string_array_base < Type, RawType, t_etypePayload > >() != nullptr)
         {

            i = ::papaya::array::add(array, *payload.cast < string_array_base < Type, RawType, t_etypePayload > >());

         }
         else if (payload.get_type() == ::e_type_payload_array)
         {

            for (::index i = 0; i < payload.payloada().get_count(); i++)
            {

               index iItem = ::papaya::array::add(array, payload.payloada()[i].string());

               if (i < 0)
               {

                  i = iItem;

               }

            }

         }
         else if (payload.get_type() == ::e_type_i32_array)
         {

            auto ia = payload.ia();

            for (::index i = 0; i < ia.get_count(); i++)
            {

               auto iItem = ::papaya::array::add(array, __string(ia[i]));

               if (i < 0)
               {

                  i = iItem;

               }

            }

         }
         else if (payload.get_type() == ::e_type_property_set)
         {

            for (auto & value : payload.propset().values())
            {

               auto iItem = ::papaya::array::add(array, value.string());

               if (i < 0)
               {

                  i = iItem;

               }

            }

         }
         else
         {
            i = ::papaya::array::add(array, payload.string());

         }

         return i;

      }


      template < typename TYPE >
      ::stream & read_container_as_parent(::stream & stream, __pointer_array(TYPE) & a)
      {

         ::count c = 0;

         stream >> c;

         //if (stream.fail())
         //{

         //   return stream;

         //}

         while (c > 0)
         {

            auto p = __new(TYPE(&a));

            stream >> *p;

  /*          if (stream.fail())
            {

               break;

            }*/

            a.add(p);

            c--;

         }

         return stream;

      }


      template < class TDST,class TSRC >
      ::count copy(TDST & dsta,const TSRC & srca)
      {

         dsta.erase_all();

         for(int i = 0; i < srca.get_size(); i++)
         {

            dsta.add((typename TDST::BASE_TYPE) srca[i]);

         }

         return dsta.get_count();

      }

   
      template < class TDST,class TSRC >
      ::count __copy(TDST & dsta,const TSRC & srca);


      template < typename CONTAINER, class TYPE >
      bool contains_item(const CONTAINER & container, const TYPE & t)
      {

         for (auto & item : container)
         {

            if (equals(item, t))
            {

               return true;

            }

         }

         return false;

      }


      // t1 candidate bigger
      template < typename T1, typename  T2>
      inline bool contains_array(const T1 & t1, const T2 & t2)
      {

         for (auto & t : t2)
         {

            if (!contains_item(t1, t))
            {

               return false;

            }

         }

         return true;

      }




      template < class TINTERSECTION, class TDST, class TSRC >
      void intersection(TINTERSECTION & intersection, const TDST & dsta, const TSRC & srca)
      {

         intersection.clear();

         for (auto & item : dsta)
         {

            if (contains_item(srca, item))
            {

               intersection.add(item);

            }

         }

      }

      template < typename T1, typename  T2>
      inline ::count erase_array(T1 & t1, T2 && t2)
      {

         ::count c = 0;

         for (auto & t : t2)
         {

            c += t1.erase(t);

         }

         return c;

      }




      //template < class TDST, class TSRC >
      //::count copy(TDST & dsta, const TSRC & srca)
      //{

      //   ::count c = srca.get_count();

      //   dsta.set_size(c);

      //   for (int i = 0; i < c; i++)
      //   {

      //      dsta[i] = (typename TDST::BASE_TYPE) srca[i];

      //   }

      //   return c;

      //}

      //template < class ARRAY >
      //::count copy_same_class(ARRAY & dsta, const ARRAY & srca)
      //{

      //   ::count c = srca.get_count();

      //   dsta.set_size(c);

      //   for (int i = 0; i < c; i++)
      //   {

      //      dsta[i] = srca[i];

      //   }

      //   return c;

      //}


      template < typename A, typename PA >
      void copy_points(A & a, const PA * pa, ::count c)
      {

         a.set_size(c);

         for (index i = 0; i < c; i++)
         {

            a[i] = (typename A::BASE_TYPE) pa[i];

         }

      }

   } // namespace array


   template < class TDST, class TSRC >
   ::count copy(__pointer_array(TDST) & dsta, const __pointer_array(TSRC) & srca)
   {

      ::count ca = 0;

      dsta.erase_all();

      for(int i = 0; i < srca.get_size(); i++)
      {
         dsta.add(__new(TSRC(srca(i))));
         ca++;
      }

      return ca;

   }

   namespace ptra
   {

      template < class TDST,class TSRC >
      ::count copy(address_array < TDST > & dsta,const address_array < TSRC > & srca)
      {

         ::count ca = 0;

         dsta.erase_all();

         for(int i = 0; i < srca.get_size(); i++)
         {
            dsta.add(memory_new TSRC(srca(i)));
            ca++;
         }

         return ca;

      }

      template < class TDST, class TSRC >
      ::count ptrcopy(TDST & dsta, const TSRC & srca)
      {

         ::count ca = 0;

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
   void array_permute(A2D & perm, const A & a)
   {
      ::count count = a.get_count();
      if(count == 1)
      {
         perm.add(a);
         return;
      }
      A elema;
      A topermut;
      A2D perm2;
      for(i32 i = 0; i < count; i++)
      {
         elema.erase_all();
         elema.add(a[i]);
         topermut.erase_all();
         for(i32 j = 0; j < i; j++)
         {
            topermut.add(a[j]);
         }
         for(i32 j = i + 1; j < count; j++)
         {
            topermut.add(a[j]);
         }
         perm2.erase_all();
         array_permute(perm2, topermut);
         for(i32 j = 0; j < perm2.get_count(); j++)
         {
            perm.add(elema + perm2[j]);
         }
      }
   }

   template < class A >
   void array_permute(pointer_array < A > & perm,const A & a)
   {
      ::count count = a.get_count();
      if(count == 1)
      {
         perm.add(__new(A(a)));
         return;
      }
      A elema;
      A topermut;
      pointer_array < A > perm2;
      for(i32 i = 0; i < count; i++)
      {
         elema.erase_all();
         elema.add(a[i]);
         topermut.erase_all();
         for(i32 j = 0; j < i; j++)
         {
            topermut.add(a[j]);
         }
         for(i32 j = i + 1; j < count; j++)
         {
            topermut.add(a[j]);
         }
         perm2.erase_all();
         array_permute(perm2,topermut);
         for(i32 j = 0; j < perm2.get_count(); j++)
         {
            perm.add(__new(A(elema + perm2[j])));
         }
      }
   }

} // namespace array






namespace papaya
{


   namespace array
   {



      ///////////////////
      //
      //   Adding ITEM
      //      to array

      inline ::index add(string_array & stra, const char * psz) { return stra.add_item(psz); }
      inline ::index add(string_array & stra, const char & ch) { return stra.add_item(ch); }
      inline ::index add(string_array & stra, const ansistring & str) { return stra.add_item(str); }
      inline ::index add(string_array & stra, const wd16string & str) { return stra.add_item(str); }
      inline ::index add(string_array & stra, const wd32string & str) { return stra.add_item(str); }
      inline ::index add(string_array & stra, const ::file::path & path) { return stra.add_item(path); }


      inline ::index add(::file::path_array & patha, const char * psz) { return patha.add_item(psz); }
      inline ::index add(::file::path_array & patha, const char & ch) { return patha.add_item(ch); }
      inline ::index add(::file::path_array & patha, const ansistring & str) { return patha.add_item(str); }
      inline ::index add(::file::path_array & patha, const wd16string & str) { return patha.add_item(str); }
      inline ::index add(::file::path_array & patha, const wd32string & str) { return patha.add_item(str); }
      inline ::index add(::file::path_array & patha, const ::file::path & path) { return patha.add_item(path); }


      inline ::index add(string_array & stra, const ::payload & payload)
      {

         ::index iInsert = -1;

         if (payload.is_array())
         {

            ::count c = payload.array_get_count();

            for (::index i = 0; i < c; i++)
            {

               auto iItem = stra.add_item(payload.at(i));

               if (iInsert < 0)
               {

                  iInsert = iItem;

               }

            }

         }
         else
         {

            iInsert = stra.add_item(payload);

         }

         return iInsert;

      }

      inline ::index add(string_array & stra, const ::property & property)
      {

         return add(stra, (const ::payload & ) property);

      }

      inline ::index add(string_array & stra, const ::property_set & propertyset)
      {

         ::index iInsert = -1;

         ::count c = propertyset.get_count();

         for (::index i = 0; i < c; i++)
         {

            auto iItem = stra.add_item(*propertyset.element_at(i));

            if (iInsert < 0)
            {

               iInsert = iItem;

            }

         }

         return iInsert;

      }



      ///////////////////////////////////////
      //
      //   Appending ARRAY
      //          to array

      inline ::index add(string_array & stra, const string_array & straSource) { return add_array(stra, straSource); }

      inline ::index add(::file::path_array & patha, const string_array & stra) { return add_array(patha, stra); }
      inline ::index add(::file::path_array & patha, const ::file::path_array & pathaSrc) { return add_array(patha, pathaSrc); }
      inline ::index add(::file::path_array & patha, const ::file::listing & listing) { return add_array(patha, listing); }


      template < typename TYPE, enum_type t_etypePayload >
      ::count ensure_sequence(::numeric_array < TYPE, t_etypePayload > & aParam, TYPE start, TYPE end, TYPE increment)
      {

         ::count c = 0;

         ::numeric_array < TYPE, t_etypePayload > a;

         ::papaya::array::set_sequence(a, start, end, increment);

         c += erase_lesser_than_or_greater_than(aParam, start, end);

         for(index i = aParam.get_upper_bound(); i >= 0; i--)
         {

            index iFind = 0;

            if(::papaya::array::binary_search(a, aParam.element_at(i), iFind, &::numeric_compare < typename ::numeric_array < TYPE, t_etypePayload >::BASE_ARG_TYPE >))
            {

               a.erase_at(iFind);

               c++;

            }
            else
            {

               aParam.erase_at(i);

               c++;

            }

         }

         c += aParam.add(a);

         return c;

      }


      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index & iIndex,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE))
      {

         if(a.get_size() == 0)
         {
            return false;
         }

         index iLowerBound = 0;
         index iMaxBound   = a.get_upper_bound();
         index iUpperBound = iMaxBound;
         index iCompare;
         // do binary search
         iIndex = (iUpperBound + iLowerBound) / 2;
         while(iUpperBound - iLowerBound >= 8)
         {
            iCompare = fCompare(a.element_at(iIndex),t);
            if(iCompare == 0)
            {
               return true;
            }
            else if(iCompare > 0)
            {
               iUpperBound = iIndex - 1;
               if(iUpperBound < 0)
               {
                  iIndex = 0;
                  break;
               }
            }
            else
            {
               iLowerBound = iIndex + 1;
               if(iLowerBound > iMaxBound)
               {
                  iIndex = iMaxBound + 1;
                  break;
               }
            }
            iIndex = (iUpperBound + iLowerBound) / 2;
         }
         // do sequential search
         while(iIndex < a.get_count())
         {
            iCompare = fCompare(a.element_at(iIndex),t);
            if(iCompare == 0)
               return true;
            else if(iCompare < 0)
               iIndex++;
            else
               break;
         }
         if(iIndex >= a.get_count())
            return false;
         while(iIndex >= 0)
         {
            iCompare = fCompare(a.element_at(iIndex),t);
            if(iCompare == 0)
               return true;
            else if(iCompare > 0)
               iIndex--;
            else
               break;
         }
         iIndex++;
         return false;

      }


      template<class ARRAY>
      bool binary_search(ARRAY & a, typename ARRAY::BASE_ARG_TYPE t, index & iIndex, less_predicateicate_base < typename ARRAY::BASE_ARG_TYPE > * pless, index_array & ia)
      {

         if(a.get_size() == 0)
         {

            return false;

         }

         index iLowerBound = 0;
         index iMaxBound   = a.get_upper_bound();
         index iUpperBound = iMaxBound;
         index iCompare;

         // do binary search
         iIndex = (iUpperBound + iLowerBound) / 2;

         while(iUpperBound - iLowerBound >= 8)
         {

            iCompare = pless->less(a.element_at(iIndex), t);

            if(iCompare == 0)
            {

               return true;

            }
            else if(iCompare > 0)
            {

               iUpperBound = iIndex - 1;

               if(iUpperBound < 0)
               {

                  iIndex = 0;

                  break;

               }

            }
            else
            {

               iLowerBound = iIndex + 1;

               if(iLowerBound > iMaxBound)
               {

                  iIndex = iMaxBound + 1;

                  break;

               }

            }

            iIndex = (iUpperBound + iLowerBound) / 2;

         }

         // do sequential search
         while(iIndex < a.get_count())
         {

            iCompare = pless->less(a.element_at(iIndex), t);

            if(iCompare == 0)
            {

               return true;

            }

            else if(iCompare < 0)
            {

               iIndex++;

            }
            else
            {

               break;

            }

         }

         if(iIndex >= a.get_count())
         {

            return false;

         }

         while(iIndex >= 0)
         {

            iCompare = pless->less(a.element_at(iIndex), t);

            if(iCompare == 0)
            {

               return true;

            }

            else if(iCompare > 0)
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


      template < typename TYPE, enum_type t_etypePayload >
      ::count append_sequence(::numeric_array < TYPE, t_etypePayload > & a, TYPE iterator,TYPE end,TYPE increment)
      {
         if(increment == 0)
         {
            a.add(iterator);
            a.add(end);
            return 2;
         }
         else if(increment > 0)
         {
            ::count ca = 0;
            for(; iterator <= end; iterator +=increment)
            {
               a.add(iterator);
               ca++;
            }
            return ca;
         }
         else
         {
            ::count ca = 0;
            for(; iterator >= end; iterator +=increment)
            {
               a.add(iterator);
               ca++;
            }
            return ca;
         }
      }


      template < typename TYPE, enum_type t_etypePayload >
      ::count set_sequence(::numeric_array < TYPE, t_etypePayload > & a, TYPE start,TYPE end,TYPE increment)
      {
         a.erase_all();
         return append_sequence(a, start,end,increment);
      }


      template < typename ARRAY >
      inline typename ARRAY::BASE_TYPE pop(ARRAY & a, index n)
      {

         index i = a.get_upper_bound(n);

         typename ARRAY::TYPE t = a.element_at(i);

         a.erase_at(i);

         return t;

      }


      template < typename ARRAY >
      inline void pop_back(ARRAY & a, index n)
      {

         a.erase_at(a.get_upper_bound(n));

      }


      template < typename ARRAY >
      inline index push(ARRAY & a,typename ARRAY::BASE_ARG_TYPE newElement,index n)
      {

         return a.insert_at(a.get_upper_bound(n),newElement);

      }


      template < typename ARRAY >
      inline void push_back(ARRAY & a,typename ARRAY::BASE_ARG_TYPE newElement,index n)
      {

         a.insert_at(a.get_upper_bound(n),newElement);

      }


   } //namespace array


} // namespace papaya



