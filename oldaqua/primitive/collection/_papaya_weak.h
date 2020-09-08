#pragma once


namespace papaya
{


   namespace weak
   {


      template < typename TYPE >
      inline TYPE default_value()
      {

         return TYPE();

      }


      template < typename A, typename B >
      inline bool contains(const A & a, const B & b)
      {

         return a.weakly_contains(b);

      }


      template <  >
      inline bool contains(const string & a, const string & b)
      {

         return a.contains_ci(b);

      }


      template <  >
      inline string default_value < string >()
      {

         return string();

      }

      namespace map
      {


         template < typename MAP >
         typename MAP::assoc * get(MAP & m, typename MAP::BASE_KEY key)
         {

            for (auto & assoc : m)
            {

               if (contains(assoc.element1(), key))
               {

                  return &assoc;

               }

            }

            return nullptr;

         }


         template < typename MAP >
         typename MAP::BASE_VALUE * pvalue(MAP & m, typename MAP::BASE_ARG_KEY key)
         {

            for (auto & assoc : m)
            {

               if (contains(assoc.element1(), key))
               {

                  return &assoc.element2();

               }

            }

            return nullptr;

         }

         template < typename MAP >
         typename MAP::BASE_VALUE value(MAP & m, typename MAP::BASE_ARG_KEY key, typename MAP::BASE_VALUE default_value = ::papaya::weak::default_value < typename MAP::BASE_VALUE >())
         {

            auto pval = pvalue(m, key);

            if (pval == nullptr)
            {

               return default_value;

            }

            return *pval;

         }


      } // namespace map


   } // namespace weak


} // namespace papaya
