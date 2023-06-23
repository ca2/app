//
// Created by camilo on 24/12/2022 02:35 <3ThomasBorregaardSorensen!!
//
#pragma once



template < typename BLOCK_TYPE >
inline BLOCK_TYPE & memory_template < BLOCK_TYPE > ::operator = (const ::block & block)
{

   if (block.size() < size())
   {

      throw_exception(error_bad_argument);

   }

   ::memory_copy(data(), block.data(), (size_t)size());

   return *data();

}



