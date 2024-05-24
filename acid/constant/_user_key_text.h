//
// Created by camilo on 2023-10-10 21:59 <3ThomasBorregaardSorensen!!.
//
#pragma once


CLASS_DECL_ACID ::string as_string(::user::enum_key ekey);


inline ::write_text_stream & operator <<(::write_text_stream  & textstream, ::user::enum_key ekey)
{

   return textstream << ::as_string(ekey);

}






