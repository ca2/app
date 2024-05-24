#pragma once


#include "acid/exception/status.h"


class CLASS_DECL_ACID string_to_string_lookup
{
public:


   virtual ::status < ::string > lookup(const ::scoped_string & scopedstrKey) = 0;


};