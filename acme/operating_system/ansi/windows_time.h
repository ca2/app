//
//  windows_time.hpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Sørensen on 14/02/22.
//  14:35
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


CLASS_DECL_ACME int_bool FileTimeToSystemTime(const file_time_t * pfile_time, system_time_t * psystemtime);


CLASS_DECL_ACME int_bool SystemTimeToFileTime(const system_time_t * psystemtime, file_time_t * pfile_time);


CLASS_DECL_ACME void GetSystemTime(system_time_t * systime);



