//
// Created by camilo on 22/10/22 21:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "string_exchange.h"



string_exchange &string_exchange::operator = (const ::scoped_string & scopedstr)const
{

   *m_pstr = scopedstr; return (string_exchange &)(*this);

}



