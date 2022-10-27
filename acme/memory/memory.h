#pragma once


#include "acme/primitive/primitive/block.h"


template < typename BLOCK_TYPE >
struct memory_template
{

   BLOCK_TYPE * get_data() const { return (BLOCK_TYPE *)this; }
   memsize get_size() const { return sizeof(BLOCK_TYPE); }
   memsize size() const { return (memsize) sizeof(BLOCK_TYPE); }

   BLOCK_TYPE & operator = (const block & block);

   ::block block() const { return ::block(get_data(), get_size()); }

   inline void reset() { ::zero(get_data(), get_size()); }

};





#define __memory(MEMORY) struct CLASS_DECL_EXPORT MEMORY : public memory_template < MEMORY >





template < typename BLOCK_TYPE >
inline BLOCK_TYPE & memory_template < BLOCK_TYPE > ::operator = (const ::block & block)
{

   if (block.get_size() < get_size())
   {

      throw ::exception(error_bad_argument);

   }

   ::memcpy_dup(get_data(), block.get_data(), (size_t)get_size());

   return *get_data();

}
