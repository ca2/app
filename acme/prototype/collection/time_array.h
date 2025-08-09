// Created by camilo on 2021-10-07 21:31 BRT <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/collection/pointer_array.h"
//#include "acme/prototype/collection/numeric_array.h"


using time_array_base = numeric_array_base < class time >;


using time_array = ::array_particle < ::time_array_base >;


//using integral_microsecond_array = numeric_array < integral_microsecond >;
//
//
//using ::time_array = numeric_array < integral_millisecond >;


using time_array_array = ::pointer_array_base < time_array >;






