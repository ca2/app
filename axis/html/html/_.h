#pragma once


typedef string_map < with_status < ::color::color > > string_to_color;
class LiteHTMLEntityResolver;

inline with_status < ::color::color > __indexed_color(::u32 u)
{ 
	
	return with_status < ::color::color >(u, ::success_color_index);

}


namespace html
{


	typedef string_to_color named_color;


} // namespace html


#include "_const.h"


#include "html.h"



