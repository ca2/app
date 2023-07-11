//
// Created by camilo on 22/10/22 21:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "string_exchange.h"



string_exchange &string_exchange::operator = (const ::string & str )const
{

   *m_pstr = str; return (string_exchange &)(*this);

}



