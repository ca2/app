// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/parallelization.h"


#include "_c.h"


CLASS_DECL_ACME void throw_last_error_exception(DWORD dwLastError);

CLASS_DECL_ACME void throw_last_error_exception();

CLASS_DECL_ACME::e_status windows_wait_result_to_status(::i32 iResult);

#ifndef CUBE

//CLASS_DECL_ACME i32_bool _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, void * pReserved, ::i32 iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});
CLASS_DECL_ACME i32_bool _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, void * pReserved);

#endif


wstring CLASS_DECL_ACME windows_get_root(const wstring & wstrPath);


//CLASS_DECL_ACME bool ensure_file_size_handle(HANDLE h, ::u64 iSize);


#include "library.h"



