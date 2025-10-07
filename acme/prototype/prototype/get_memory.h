#pragma once


//#include "block.h"


class CLASS_DECL_ACME get_memory
{
public:


   memory_base *        m_pmemory;
   block                m_block;


   get_memory(memory_base & memory);
   get_memory(memory_base * pmemory);
   // block is const, its memory not!!!!
   get_memory(const block & block);
   // VOID * NOT const!!
   get_memory(/* NOTTTT const!!!!! */ void * p, memsize s);

   ~get_memory();


   void * get(memsize s);

   bool get_base64(const ::scoped_string & scopedstr);

   bool get(const void * pdata, memsize s);
   
   bool get(const memory_base & memory);
   
   bool get(const block & block);

   unsigned char * data() const;

   memsize size() const;


};



