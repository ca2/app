//
// Created by camilo on 25/06/2023 20:54 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_string.h"


template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, ::enum_display edisplay)
{

   return textstream << ::as_string(edisplay);

}


template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, ::enum_activation eactivation)
{

   return textstream << ::as_string(eactivation);

}

//
//
//template < typename FILE, primitive_rectangle RECTANGLE >
//inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const RECTANGLE & rectangle)
//{
//
//   return textstream << "xy(" << rectangle.left  << ", " << rectangle.top << ")-wh(" << rectangle.width() << ", " << rectangle.height() << ")";
//
//}
//
//
