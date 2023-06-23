//
//  _string_format.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 15/10/21 09:29 BRT.
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


//// #include "acme/primitive/string/string.h"


struct integral_nanosecond;
struct integral_microsecond;
struct integral_millisecond;
struct integral_second;
struct integral_minute;
struct integral_hour;
struct integral_day;


CLASS_DECL_ACME ::string & copy(::string & str, const integral_nanosecond & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const integral_microsecond & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const integral_millisecond & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const integral_second & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const integral_minute & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const integral_hour & integral);
CLASS_DECL_ACME ::string & copy(::string & str, const integral_day & integral);



