//
// Created by camilo on 22/10/22 21:00 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "string_exchange.h"
// #include "acme/primitive/string/string.h"


string_exchange &string_exchange::operator = (const ::string & str )const
{

   *m_pstr = str; return (string_exchange &)(*this);

}



