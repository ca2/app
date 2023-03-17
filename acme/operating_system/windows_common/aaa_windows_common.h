// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/parallelization.h"


#include "_c.h"


CLASS_DECL_ACME void throw_last_error(DWORD dwLastError);

CLASS_DECL_ACME void throw_last_error();

CLASS_DECL_ACME::e_status windows_wait_result_to_status(int iResult);

#ifndef CUBE

//CLASS_DECL_ACME int_bool _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, void * pReserved, int iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});
CLASS_DECL_ACME int_bool _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, void * pReserved);

#endif


wstring CLASS_DECL_ACME windows_get_root(const wstring & wstrPath);


//CLASS_DECL_ACME bool ensure_file_size_handle(HANDLE h, u64 iSize);


#include "library.h"



