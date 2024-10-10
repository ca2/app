#pragma once


#include "acme/exception/status.h"


class CLASS_DECL_ACME string_to_string_lookup
{
public:


   virtual ::status < ::string > lookup(const ::scoped_string & scopedstrKey) = 0;


};