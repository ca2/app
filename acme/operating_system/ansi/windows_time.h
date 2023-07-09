//
//  windows_time.hpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  14:35
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


typedef struct _FILETIME FILETIME;

typedef struct _SYSTEMTIME SYSTEMTIME;


CLASS_DECL_ACME int_bool FileTimeToSystemTime(const FILETIME * pfiletime, SYSTEMTIME * psystemtime);


CLASS_DECL_ACME int_bool SystemTimeToFileTime(const SYSTEMTIME * psystemtime, FILETIME * pfiletime);


CLASS_DECL_ACME void GetSystemTime(SYSTEMTIME * psystemtime);



