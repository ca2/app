#pragma once


struct lib_main_int
{

   int m_iAny = 0;
   class ::time m_timeProcessAttach = 0;
   class ::time m_timeProcessDetach = 0;
   class ::time m_timeThreadAttach = 0;
   class ::time m_timeThreadDetach = 0;

};

#ifndef CUBE

CLASS_DECL_CORE int_bool _001DefaultDllMain(HINSTANCE hinstance, ::u32 dwReason, LPVOID pReserved, int iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});

#endif








//#include "_error_c.h"
#include "_unicode_c.h"
#include "_file_c.h"
