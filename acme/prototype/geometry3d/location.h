#pragma once


#include "pole.h"


template < prototype_number NUMBER >
using location_type = pole_type < NUMBER >;


using LOCATION_INT = int_pole;
using LOCATION_LONG_LONG = long_long_pole;
using LOCATION_FLOAT = float_pole;
using LOCATION_DOUBLE = double_pole;


using int_location = LOCATION_INT;
using long_long_location = LOCATION_LONG_LONG;
using float_location = LOCATION_FLOAT;
using double_location = LOCATION_DOUBLE;

//{
//   double x;
//   double y;
//   double z;
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

