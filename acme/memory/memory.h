#pragma once


//#include "acme/primitive/primitive/block.h"


template < typename BLOCK_TYPE >
struct raw_block
{

   const BLOCK_TYPE * data() const { return (const BLOCK_TYPE *)this; }
   BLOCK_TYPE * data() { return (BLOCK_TYPE *)this; }
   memsize size() const { return (memsize) sizeof(BLOCK_TYPE); }

   BLOCK_TYPE & operator = (const block & block)
   {

      if ((const void *) this != (const void *)  & block)
      {

         memcpy(this, block.data(), minimum(sizeof(*this), block.size()));

      }

      return (BLOCK_TYPE &) *this;

   }

   ::block block() const { return ::block(data(), size()); }

   inline void reset() { ::zero(data(), size()); }

   bool operator == (const BLOCK_TYPE & rectangle) const {return memory_order(this, &rectangle, sizeof(BLOCK_TYPE)) == 0; }


};





//#define __memory(MEMORY) struct CLASS_DECL_EXPORT MEMORY : public memory_template < MEMORY >





