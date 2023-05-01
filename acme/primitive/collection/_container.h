// Created by camilo on 2022-11-08 17:25 <3ThomasBorregaardSørensen!!
// Created by camilo on 2023-01-20 22:25 <3ThomasBorregaardSørensen!!
// 2023-01-20 22:25 - Mummi, Lucinho, Bilbo, Blue, Carol e Zibia contribution through ca2 HQ!!
// 2023-01-20 22:25 - lowluds, shegotmad, mrsteinbergplease and octaelliptical contribution through Twitch.TV!!
#pragma once


CLASS_DECL_ACME void copy(::string & str, const ::payload & payload);
CLASS_DECL_ACME void copy(::payload & payload, const int & i);
CLASS_DECL_ACME void copy(::payload & payload, const ::string & str);

namespace generic
{


    namespace container
    {


        template < primitive_container CONTAINER1, primitive_container CONTAINER2 >
        CONTAINER1& append(CONTAINER1& container1, const CONTAINER2& container2)
        {

            for (auto& item : container2)
            {

                ::copy(container1.add_new(), item);

            }

            return container1;

        }


        template < primitive_container CONTAINER1, primitive_container CONTAINER2 >
        CONTAINER1& copy(CONTAINER1& container1, const CONTAINER2& container2)
        {

            container1.clear();

            return append(container1, container2);

        }


    } // namespace container


} // namespace generic


template < primitive_container CONTAINER >
inline ::string as_string(const CONTAINER& container, const ::scoped_string& scopedstrSeparator = "|")
{

   ::string str;

   for (const auto& item : container)
   {

      if (str.has_char())
      {

         str += scopedstrSeparator;

      }

      str += ::as_string(item);

   }

   return str;

}

template < typename ITEM >
inline ::string as_string(const ::set < ITEM > & set, const ::scoped_string& scopedstrSeparator = "|")
{

   ::string str;

   for (const auto& item : set)
   {

      if (str.has_char())
      {

         str += scopedstrSeparator;

      }

      str += ::as_string(item.item());

   }

   return str;

}


template < primitive_container CONTAINER >
inline void from_string(CONTAINER & container, const ::scoped_string  & scopedstr, const ::scoped_string  & scopedstrSeparator = "|")
{

   ::tokenizer tokenizer(scopedstr);

   ::string strToken;

   while(tokenizer.get_next_token(strToken, scopedstrSeparator))
   {

      typename CONTAINER::BASE_TYPE t;

      ::from_string(t, strToken);

      container.add(t);

   }

}


template < typename ITEM >
inline void from_string(::set < ITEM > & set, const ::scoped_string& scopedstr, const ::scoped_string& scopedstrSeparator = "|")
{

   ::tokenizer tokenizer(scopedstr);

   ::string strToken;

   while (tokenizer.get_next_token(strToken, scopedstrSeparator))
   {

      typename ::set < ITEM >::ITEM item;

      ::from_string(item, strToken);

      set.set_at(item);

   }

}



