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


	class core_data;
	class font;


	namespace impl
	{


		class table;


	} // namespace impl


} // namespace html


#include "_constant.h"


class html_document;


#include "html.h"



