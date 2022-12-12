#pragma once


//#include "acme/primitive/primitive/block.h"


template < typename BLOCK_TYPE >
struct memory_template
{

   const BLOCK_TYPE * data() const { return (const BLOCK_TYPE *)this; }
   BLOCK_TYPE * data() { return (BLOCK_TYPE *)this; }
   memsize size() const { return (memsize) sizeof(BLOCK_TYPE); }

   BLOCK_TYPE & operator = (const block & block);

   ::block block() const { return ::block(data(), size()); }

   inline void reset() { ::zero(data(), size()); }

};





#define __memory(MEMORY) struct CLASS_DECL_EXPORT MEMORY : public memory_template < MEMORY >





template < typename BLOCK_TYPE >
inline BLOCK_TYPE & memory_template < BLOCK_TYPE > ::operator = (const ::block & block)
{

   if (block.size() < size())
   {

      throw_exception(error_bad_argument);

   }

   ::memcpy_dup(data(), block.data(), (size_t)size());

   return *data();

}
