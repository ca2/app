// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/include/_c_swap.h"


//#include "acme/primitive/datetime/file_time.h"


inline file_time __file_time(const FILETIME & file_time) { return make64_from32(file_time.dwLowDateTime, file_time.dwHighDateTime); }


CLASS_DECL_ACME HANDLE duplicate_handle(HANDLE h);


CLASS_DECL_ACME::file::path get_module_path(HMODULE hmodule);



