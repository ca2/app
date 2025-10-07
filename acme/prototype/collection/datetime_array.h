// Created by camilo on 2022-11-16 21:15 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/collection/numeric_array.h"
////#include "acme/prototype/datetime/earth_time.h"


namespace earth
{

   using time_array_base = numeric_array_base < ::earth::time >;

   using time_array = ::array_particle < time_array_base >;


} // namespace earth




