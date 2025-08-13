#pragma once


#include "acme/prototype/collection/map.h"


template < class PAYLOAD, typename PAIR = pair < string, PAYLOAD > >
class string_map_base :
   public map_base < string, PAYLOAD, PAIR >
{
public:

   using BASE_PAIR_MAP = map_base < string, PAYLOAD, PAIR >;

   using BASE_PAIR_MAP::BASE_PAIR_MAP;
   using BASE_PAIR_MAP::operator = ;

   using iterator = typename BASE_PAIR_MAP::iterator;



};


template < class PAYLOAD, typename PAIR = pair < string, PAYLOAD > >
using string_map = map_particle < string_map_base < PAYLOAD, PAIR > >;

using string_to_iptr_base = string_map_base < iptr > ;

using string_to_int_base =  string_map_base < int > ;

using string_to_ptr_base =  string_map_base < void * > ;

using iptr_to_string_base = map_base < iptr, string >;

using iptr_to_iptr_to_string_base = map_base < iptr, iptr_to_string_base >;

using index_to_string_base = map_base < ::collection::index, string >;

using index_to_index_to_string_base = map_base < ::collection::index, index_to_string_base >;

using string_to_string_base = string_map_base < string > ;

using string_to_string = map_particle < string_to_string_base > ;

using string_table_base = string_map_base < string_to_string_base >;

using string_table = string_map < ::pointer < string_to_string > >;


//#define strmap(T) string_map_base < T >



