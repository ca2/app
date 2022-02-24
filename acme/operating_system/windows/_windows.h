// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSørensen!!
#pragma once


inline filetime __filetime(const FILETIME & filetime) { return make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime); }


CLASS_DECL_ACME HANDLE duplicate_handle(HANDLE h);


inline void __throw_last_error(DWORD dwLastError)
{

   auto estatus = last_error_to_status(dwLastError);

   throw ::exception(estatus);

}


inline void __throw_last_error()
{

   auto lastError = ::GetLastError();

   __throw_last_error(lastError);

}



