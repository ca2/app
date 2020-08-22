#pragma once


struct lib_main_int
{

   int m_iAny = 0;
   int m_iProcessAttach = 0;
   int m_iProcessDetach = 0;
   int m_iThreadAttach = 0;
   int m_iThreadDetach = 0;

};

#ifndef CUBE

CLASS_DECL_AXIS WINBOOL _001DefaultDllMain(HINSTANCE hinstance, DWORD dwReason, LPVOID pReserved, int iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});

#endif








//#include "_error_c.h"
#include "_unicode_c.h"
#include "_file_c.h"