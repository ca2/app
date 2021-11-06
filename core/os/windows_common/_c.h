#pragma once


struct lib_main_int
{

   int m_iAny = 0;
   ::duration m_durationProcessAttach = 0;
   ::duration m_durationProcessDetach = 0;
   ::duration m_durationThreadAttach = 0;
   ::duration m_durationThreadDetach = 0;

};

#ifndef CUBE

CLASS_DECL_CORE int_bool _001DefaultDllMain(HINSTANCE hinstance, ::u32 dwReason, LPVOID pReserved, int iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});

#endif








//#include "_error_c.h"
#include "_unicode_c.h"
#include "_file_c.h"
