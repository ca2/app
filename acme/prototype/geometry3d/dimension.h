#pragma once


template < prototype_number NUMBER >
using dimension_type = pole_type < NUMBER >;

using INT_DIMENSION = i32_pole;
using LONG_LONG_DIMENSION = i64_pole;
using FLOAT_DIMENSION = f32_pole;
using DOUBLE_DIMENSION = f64_pole;


using i32_dimension = INT_DIMENSION;
using i64_dimension = LONG_LONG_DIMENSION;
using f32_dimension = FLOAT_DIMENSION;
using f64_dimension = DOUBLE_DIMENSION;


//{
//
//   ::f64 cx;
//   ::f64 cy;
//   ::f64 cz;
//
//};


//class CLASS_DECL_ACME dimensiond :
//   public DIMENSIOND
//{
//public:
//
//};

