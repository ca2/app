//
// Created by camilo on 27/11/2022 15:02 <3ThomasBorregaardSørensen!!
//
#pragma once



template < typename FILE, primitive_point POINT >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const POINT & point)
{

   return textstream << "(" << point.x  << ", " << point.y << ")";

}


template < typename FILE, primitive_size SIZE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const SIZE & size)
{

   return textstream << "(" << size.cx  << ", " << size.cy << ")";

}



template < typename FILE, primitive_rectangle RECTANGLE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const RECTANGLE & rectangle)
{

   return textstream << "xy(" << rectangle.left  << ", " << rectangle.top << ")-wh(" << rectangle.width() << ", " << rectangle.height() << ")";

}


