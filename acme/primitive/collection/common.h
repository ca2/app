#pragma once





struct __POSITION {};
typedef __POSITION* POSITION;
#define BEFORE_START_POSITION ((POSITION)-1L)



#define forall(set) for(auto item : set)
#define forallref(set) for(auto & item : set)


typedef void(*ARG_SWAP_FUNCTION)(void * lpVoidSwapArg, index, index);
typedef i32(*ARG_COMPARE_FUNCTION)(void * lpVoidCompareArg, index, index);



//#include "collection_iterator.h"



// Range-based for loop support // Thank you PUGIXML
template < typename CONST_ITERATOR >
class const_range
{
public:

   typedef CONST_ITERATOR const_iterator;

   CONST_ITERATOR m_begin;
   CONST_ITERATOR m_end;

   const_range(CONST_ITERATOR b, CONST_ITERATOR e) : m_begin(b), m_end(e) {}

   CONST_ITERATOR begin() const { return m_begin; }
   CONST_ITERATOR end() const { return m_end; }


   typename CONST_ITERATOR::TYPE & element_at(::index iIndex)
   {

      CONST_ITERATOR it = begin();

      while (iIndex > 0 && it != end())
      {

         iIndex--;

      }

      if (iIndex == 0)
      {

         return (*it);

      }
      else
      {

         __throw(error_invalid_argument);

      }

   }
};


// Range-based for loop support // Thank you PUGIXML
template < typename ITERATOR >
class range
{
public:

   typedef ITERATOR const_iterator;

   ITERATOR m_begin;
   ITERATOR m_end;

   range(ITERATOR b, ITERATOR e) : m_begin(b), m_end(e) { }

   ITERATOR begin() const { return m_begin; }
   ITERATOR end() const { return m_end; }

   typename ITERATOR::TYPE& element_at(::index iIndex)
   {

      ITERATOR it = begin();

      while (iIndex > 0 && it != end())
      {

         iIndex--;

      }

      if (iIndex == 0)
      {

         return (*it);

      }
      else
      {

         __throw(error_invalid_argument);

      }

   }

};
