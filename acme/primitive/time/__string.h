//
//  _string_format.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 09:29 BRT.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


//// #include "acme/primitive/string/string.h"


struct INTEGRAL_NANOSECOND;
struct INTEGRAL_MICROSECOND;
struct INTEGRAL_MILLISECOND;
struct INTEGRAL_SECOND;
struct INTEGRAL_MINUTE;
struct INTEGRAL_HOUR;
struct INTEGRAL_DAY;


CLASS_DECL_ACME ::string & copy(::string & str, const INTEGRAL_NANOSECOND & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const INTEGRAL_MICROSECOND & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const INTEGRAL_MILLISECOND & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const INTEGRAL_SECOND & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const INTEGRAL_MINUTE & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const INTEGRAL_HOUR & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const INTEGRAL_DAY & integral);



