#pragma once


#include "pole.h"


template < primitive_number NUMBER >
using location_type = pole_type < NUMBER >;


using LOCATION_I32 = pole_int;
using LOCATION_I64 = pole_long_long;
using LOCATION_F32 = pole_float;
using LOCATION_F64 = pole_double;


using location_int = LOCATION_I32;
using location_long_long = LOCATION_I64;
using location_float = LOCATION_F32;
using location_double = LOCATION_F64;

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

