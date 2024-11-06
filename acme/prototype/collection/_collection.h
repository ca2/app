#pragma once



template < typename ITERABLE >
inline ::collection::count __iterable_count(const ITERABLE & iterable);


//#ifdef UNIVERSAL_WINDOWS
//
//
//template < typename T >
//inline ::collection::count __iterable_count(::winrt::Windows::Foundation::Collections::IVectorImpact < T > ^ a)
//{
//
//   return a.Size;
//
//}
//
//
//
//
//#endif


class strid_array;


CLASS_DECL_ACME bool safe_destroy_element(::particle * pparticle);

CLASS_DECL_ACME bool safe_free_memory(void * ptype);







template<class TYPE>
inline void CopyElements(TYPE * pDest, const TYPE * pSrc, ::collection::count nCount);


template<class TYPE>
inline void dump_elements(dump_context & dumpcontext, const TYPE * pElements, ::collection::count nCount);



#define _TYPELIB_INDEX_LENGTH 10
#define _QUOTES_SPACE 2


#define forall(set) for(auto item : set)
#define forallref(set) for(auto & item : set)




#include "single.h"

#include "pair.h"


//
//
//// Range-based for loop support // Thank you PUGIXML
//template < typename CONST_ITERATOR >
//class const_range
//{
//public:
//
//   typedef CONST_ITERATOR const_iterator;
//
//   CONST_ITERATOR m_begin;
//   CONST_ITERATOR m_end;
//
//   const_range(CONST_ITERATOR b,CONST_ITERATOR e): m_begin(b),m_end(e) {}
//
//   CONST_ITERATOR begin() const { return m_begin; }
//   CONST_ITERATOR end() const { return m_end; }
//
//
//   auto & element_at(::collection::index iIndex)
//   {
//
//      CONST_ITERATOR it = begin();
//
//      while(iIndex > 0 && it != end())
//      {
//
//         iIndex--;
//
//      }
//
//      if(iIndex != 0)
//      {
//
//         throw ::exception(error_bad_argument);
//
//      }
//
//      return (*it);
//
//   }
//};
//
////
//// Range-based for loop support // Thank you PUGIXML
//template < typename ITERATOR >
//class range
//{
//public:
//
//
//
//   ITERATOR m_begin;
//   ITERATOR m_end;
//
//   range(ITERATOR b,ITERATOR e): m_begin(b),m_end(e) { }
//
//   auto begin() const { return m_begin; }
//   auto end() const { return m_end; }
//
//   auto & element_at(::collection::index iIndex)
//   {
//
//      ITERATOR it = begin();
//
//      while(iIndex > 0 && it != end())
//      {
//
//         iIndex--;
//
//      }
//
//      if(iIndex != 0)
//      {
//
//         throw ::exception(error_bad_argument);
//
//      }
//
//      return (*it);
//
//   }
//
//};


//#include "comparable_eq_array.h"
//#include "comparable_array.h"
#include "comparable_raw_array.h"
#include "comparable_array.h"


//#include "primitive_array.h"
#include "numeric_array_range.h"
#include "numeric_array.h"

#include "logic_array.h"

#include "list.h"
#include "comparable_eq_list.h"
#include "comparable_list.h"


#include "set_node.h"


#include "set.h"


#include "map.h"


#include "attrib_map.h"
#include "int_map.h"
#include "string_map.h"
#include "strid_map.h"
#include "map_to_smart_pointer.h"
#include "fifo_map.h"
#include "sort_map.h"


#include "sort_array.h"


/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//matter

// Lists
class pointer_list;             // list of void *
class object_list;              // list of matter*

//   // Maps (aka Dictionaries)
//   class CMapWordToOb;         // map from unsigned short to matter*
//   class CMapWordToPtr;        // map from unsigned short to void *
//   class CMapPtrToWord;        // map from void * to unsigned short
//   class map_ptr_to_ptr;         // map from void * to void *
//
//   // Special string variants
//   class string_list;          // list of Strings
//   class CMapStringToPtr;      // map from string to void *
//   class CMapStringToOb;       // map from string to matter*
////   class string_to_string;   // map from string to string




#include "string_list.h"


using map_u16_to_ptr = map < unsigned short, unsigned short, void *, void * >;

using map_ptr_to_u16 = map < void *, void *, unsigned short, unsigned short >;

using map_ptr_to_ptr = map < void *, void *, void *, void * >;

using map_word_to_ob = map < unsigned short, unsigned short, matter *, matter * >;

using map_string_to_ptr = map < string, const string &, void *, void * >;

using map_string_to_ob = map < string, const string &, matter *, matter * >;


#include "string_to_string_map.h"
#include "bit_array.h"
//#include "string_array_base.h"





//#include "acme/parallelization/keep_task_payload.h"


#include "acme/platform/options.h"


typedef CLASS_DECL_ACME pointer_array < u32_array > dword_2darray;
typedef CLASS_DECL_ACME pointer_array < index_array > index_2darray;





#include "acme/prototype/comparison/less.h"


#include "sort.h"

//#include "atom_array.h"

#include "bitset.h"

#include "packset.h"

#include "spreadset.h"

#include "deque.h"

#include "queue.h"

#include "priority_queue.h"




#include "string_list.h"
//#include "string_sort_array.h"
//#include "string_array.h"

#include "_papaya_array.h"







#include "unique_array.h"

#include "stack.h"

#include "set_element.h"

#include "set.h"

//#include "runnable_array.h"

//#include "base_2array.h"


#include "time.h"



