#pragma once


struct lib_main_int
{

   int m_iAny = 0;
   ::millis m_millisProcessAttach = 0;
   ::millis m_millisProcessDetach = 0;
   ::millis m_millisThreadAttach = 0;
   ::millis m_millisThreadDetach = 0;

};

#ifndef CUBE

CLASS_DECL_ACME int_bool _001DefaultDllMain(HINSTANCE hinstance, ::u32 dwReason, LPVOID pReserved, int iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});

#endif








//#include "_error_c.h"
#include "_unicode_c.h"
#include "_file_c.h"