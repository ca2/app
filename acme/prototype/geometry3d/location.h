#pragma once


#include "pole.h"


template < prototype_number NUMBER >
using location_type = pole_type < NUMBER >;


using LOCATION_INT = int_pole;
using LOCATION_LONG_LONG = i64_pole;
using LOCATION_FLOAT = f32_pole;
using LOCATION_DOUBLE = f64_pole;


using int_location = LOCATION_INT;
using i64_location = LOCATION_LONG_LONG;
using f32_location = LOCATION_FLOAT;
using f64_location = LOCATION_DOUBLE;

//{
//   ::f64 x;
//   ::f64 y;
//   ::f64 z;
//};

//using LPLOCATIOND = LOCATIOND * ;
//using LPCLOCATIOND = const LOCATIOND*;
//
//class CLASS_DECL_ACME locationd :
//   public LOCATIOND
//{
//public:
//
//
//
//};

