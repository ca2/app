#pragma once


#include "pole.h"


template < primitive_number NUMBER >
using location_type = pole_type < NUMBER >;


using LOCATION_I32 = pole_i32;
using LOCATION_I64 = pole_i64;
using LOCATION_F32 = pole_f32;
using LOCATION_F64 = pole_f64;


using location_i32 = LOCATION_I32;
using location_i64 = LOCATION_I64;
using location_f32 = LOCATION_F32;
using location_f64 = LOCATION_F64;

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

