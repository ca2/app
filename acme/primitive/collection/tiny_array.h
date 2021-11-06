#pragma once


#define TINY_ARRAY_BUILTIN_SIZE 4


template < typename TYPE >
class tiny_array
{
public:


   TYPE *      m_p;
   ::i32       m_iCount;
   ::i32       m_iAllocation;
   TYPE        m_typea[TINY_ARRAY_BUILTIN_SIZE];



   tiny_array() : m_iCount(0), m_iAllocation(0), m_p(nullptr) { }
   ~tiny_array() { free(); }


   void allocate(::i32 iCount);
   void free();
   void zero();
   void set_at_grow(::i32 iIndex, const TYPE& t);
   

   TYPE& element_at_grow(::i32 iIndex);


};



