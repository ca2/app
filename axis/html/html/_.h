#pragma once


typedef string_map < status < ::color::color > > string_to_color;
class LiteHTMLEntityResolver;

inline status < ::color::color > __indexed_color(::u32 u)
{ 
	
	return status < ::color::color >(u, ::success_color_index);

}


namespace html
{


	typedef string_to_color named_color;


} // namespace html


#include "_const.h"


#include "html.h"



