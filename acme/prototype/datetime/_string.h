//Created by camilo on 2021-08-30 17:41 BRT <3ThomasBS__!!
#pragma once


#include "earth_time_shift.h"


namespace earth
{


   CLASS_DECL_ACME string format(const ::scoped_string & scopedstrFormat, const time_span& timespan, const class ::time & timeshift = {});
   CLASS_DECL_ACME string format(const ::scoped_string & scopedstrFormat, const time& time, const class ::time& timeshift = {});


} // namespace earth



