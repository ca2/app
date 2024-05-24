// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acid/include/_c_swap.h"


//#include "acid/primitive/datetime/file_time.h"


inline file_time __file_time(const FILETIME & file_time) { return make64_from32(file_time.dwLowDateTime, file_time.dwHighDateTime); }


CLASS_DECL_ACID HANDLE duplicate_handle(HANDLE h);


CLASS_DECL_ACID::file::path get_module_path(HMODULE hmodule);



