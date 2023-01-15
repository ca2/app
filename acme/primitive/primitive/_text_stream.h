// Created by camilo on 2022-11-09 10:16 <3ThomasBorregaardSørensen!!
#pragma once


template < typename FILE >
text_stream < FILE >& text_stream < FILE >::operator <<(const ::atom& atom)
{

   operator <<(atom.string());

   return *this;

}




