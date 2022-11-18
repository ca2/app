// Created by camilo on 2021-10-07 21:31 BRT <3ThomasBorregaardS�rensen!!
#pragma once


#include "acme/primitive/collection/pointer_array.h"
#include "acme/primitive/collection/numeric_array.h"


using duration_array = numeric_array < duration >;


using integral_microsecond_array = numeric_array < integral_microsecond >;


using integral_millisecond_array = numeric_array < integral_millisecond >;


using duration_2darray = pointer_array < duration_array >;
