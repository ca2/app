#pragma once


//#include "acme/prototype/prototype/block.h"




template < typename RAW_BLOCK >
struct raw_block
{

   using raw_RAW_BLOCK = RAW_BLOCK;

   const RAW_BLOCK * data() const { return (const RAW_BLOCK *)this; }
   RAW_BLOCK * data() { return (RAW_BLOCK *)this; }
   memsize size() const { return (memsize) sizeof(RAW_BLOCK); }

   RAW_BLOCK & operator = (const block & block)
   {

      if ((const void *) this != (const void *)  & block)
      {

         memory_copy(this, block.data(), minimum(sizeof(*this), block.size()));

      }

      return (RAW_BLOCK &) *this;

   }

   ::block block() const { return ::block(data(), size()); }

   inline void clear() { ::zero(data(), size()); }

   bool operator == (const RAW_BLOCK & rectangle) const {return memory_order(this, &rectangle, sizeof(RAW_BLOCK)) == 0; }


};





//#define __memory(MEMORY) struct CLASS_DECL_EXPORT MEMORY : public memory_template < MEMORY >





