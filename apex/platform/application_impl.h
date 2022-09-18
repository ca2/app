#pragma once


#include "acme/platform/exclusive.h"


namespace apex
{


   class application_impl :
      virtual public object
   {
   public:


      string_map < __pointer(::acme::exclusive) >   m_mapExclusive;


      virtual __pointer(::acme::exclusive) get_exclusive(string str ARG_SEC_ATTRS_DEF);

      virtual bool erase_exclusive(string str ARG_SEC_ATTRS_DEF);


   };


} // namespace apex



