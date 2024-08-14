// Recreated by camilo on 2022-10-22 20:39 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/memory/malloc.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/primitive/string/string.h(1))"
//#endif
#include  "acme/primitive/primitive/block.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/primitive/string/string.h(2))"
//#endif


//#include "simple_string_base.h"


#include "__begin.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/primitive/string/string.h(3))"
//#endif


#include "utf8_character.h"

//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/primitive/string/string.h(4))"
//#endif

#include "string_base.h"

//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/primitive/string/string.h(5))"
//#endif

using string_array = string_array_base < string, string, e_type_string_array >;
using wstring_array = string_array_base < wstring, wstring >;


#include "__end.h"

//
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/primitive/string/string.h(__end))"
//#endif
//
