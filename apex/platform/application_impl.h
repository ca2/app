#pragma once


#include "acme/platform/exclusive.h"


class application_impl :
   virtual public object
{
public:


   string_map < __composite(::acme::exclusive) >   m_mapExclusive;


   virtual __pointer(::acme::exclusive) get_exclusive(string str ARG_SEC_ATTRS_DEF);


};



