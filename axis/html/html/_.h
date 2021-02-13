#pragma once


typedef string_map < __status < ::color::color > > string_to_color;
class LiteHTMLEntityResolver;

inline __status < ::color::color > __indexed_color(::u32 u)
{ 
	
	return __status < ::color::color >(::success_color_index, u);

}


namespace html
{


	typedef string_to_color named_color;


} // namespace html


#include "_const.h"


#include "html.h"



