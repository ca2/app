// Created by camilo on 2026-01-07 12:03 <3ThomasBorregaardSørensen!!
#pragma once


template < typename ARRAY >
class array_map :
   public ARRAY
{
public:

   using KEY = decltype(&ARRAY::BASE_TYPE::key());

   array_map() = default;
   ~array_map() override = default;

   ARRAY::BASE_TYPE & find(const KEY & key) 
   {
      for (auto & item : *this)
      {
         if (item.key() == key)
         {
            return item;
         }
      }
      throw ::exception(error_not_found);
   }
   ARRAY::BASE_TYPE &operator[](const KEY &key)
   {
      for (auto &item: *this)
      {
         if (item.key() == key)
         {
            return item;
         }
      }
      throw ::exception(error_not_found);
   }

   ARRAY::BASE_TYPE &ø(const KEY &key)
   {
      for (auto &item: *this)
      {
         if (item.key() == key)
         {
            return item;
         }
      }
      this->add(key);
      return this->last();
   }
};



template<typename ARRAY>
class pointer_array_map : public ARRAY
{
public:

   using MAIN_TYPE = typename ARRAY::MAIN_TYPE;
   using KEY = ::std::invoke_result_t < decltype(&MAIN_TYPE::key), const MAIN_TYPE >;

   pointer_array_map() = default;
   ~pointer_array_map() override = default;

   MAIN_TYPE * find(const KEY &key)
   {
      for (auto & pitem: *this)
      {
         if (pitem->key() == key)
         {
            return pitem;
         }
      }
      //throw ::exception(error_not_found);
      return nullptr;
   }
   MAIN_TYPE * operator[](const KEY &key)
   {
      for (auto & pitem: *this)
      {
         if (pitem->key() == key)
         {
            return pitem;
         }
      }
      //throw ::exception(error_not_found);
      return nullptr;
   }

   MAIN_TYPE * &ø(const KEY &key)
   {
      for (auto &pitem: *this)
      {
         if (pitem->key() == key)
         {
            return pitem;
         }
      }

      this->add(::øallocate MAIN_TYPE(key));

      return this->last();

   }
};

template<typename TYPE>
using pointer_map = ::pointer_array_map < ::pointer_array < TYPE > >;


