//
// Created by camilo on Sep/10/23 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_string.h"


inline ::write_text_stream & operator <<(::write_text_stream & textstream, const ::experience::e_frame & eframe)
{

   return textstream << ::as_string(eframe);

}




