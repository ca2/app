#pragma once


#include "collection/common.h"
#include "collection/pair.h"


#include "collection/map_association.h"
#include "collection/map.h"
#include "collection/string_map.h"
#include "collection/int_map.h"
#include "collection/string_to_string_map.h"




using string_to_int_to_string = string_map < int_to_string >;

using string_to_string_to_int = string_map < string_to_int >;

namespace acme
{

   class CLASS_DECL_ACME session_map :
      virtual public ::map < index, index, ::acme::session *, ::acme::session * >
   {


   };

} // namespace acme


#include "collection/map_impl.inl"


