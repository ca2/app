// Recreated by camilo on 2022-10-22 20:39 <3ThomasBorregaardSorensen!!
#pragma once


#include "string_base.h"


class CLASS_DECL_ACME string :
   public ansistring
{
public:


   using ansistring::ansistring;

   string(const ::atom & atom);
   string(const ::payload & payload);
   string(const ::property & property);

};



