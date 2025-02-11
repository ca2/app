#pragma once


template < primitive_number NUMBER >
using dimension_type = pole_type < NUMBER >;

using DIMENSION_I32 = pole_int;
using DIMENSION_I64 = pole_long_long;
using DIMENSION_F32 = pole_float;
using DIMENSION_F64 = pole_double;


using dimension_int = DIMENSION_I32;
using dimension_long_long = DIMENSION_I64;
using dimension_float = DIMENSION_F32;
using dimension_double = DIMENSION_F64;


//{
//
//   double cx;
//   double cy;
//   double cz;
//
//};


//class CLASS_DECL_ACME dimensiond :
//   public DIMENSIOND
//{
//public:
//
//};

