// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSørensen!!
#pragma once





inline filetime __filetime(const FILETIME & filetime) { return make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime); }


CLASS_DECL_ACME HANDLE duplicate_handle(HANDLE h);