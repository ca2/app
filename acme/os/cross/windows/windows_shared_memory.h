#pragma once


#ifndef WINDOWS


struct CLASS_DECL_ACME hglobal
{

   char        m_szFile[256];
   i32     m_fd;
   void *      m_map;

};


typedef struct hglobal * HGLOBAL;


HGLOBAL WINAPI GlobalAlloc(UINT uFlags, SIZE_T dwBytes);
HGLOBAL WINAPI GlobalReAlloc(HGLOBAL hMem, SIZE_T dwBytes, UINT uFlags);
HGLOBAL WINAPI GlobalFree(HGLOBAL hMem);

LPVOID WINAPI GlobalLock(HGLOBAL hMem);
int_bool WINAPI GlobalUnlock(HGLOBAL hMem);

SIZE_T WINAPI GlobalSize(HGLOBAL hMem);


#endif




