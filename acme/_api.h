// Created by camilo on 2022-09-26 18:31 <3ThomasBorregaardSorensen!!
#pragma once


#include "operating_system/_api.h"





CLASS_DECL_ACME void throw_resource_exception(const char * pszMessage);

CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const char * pszMessage = nullptr, const char * pszDetails = nullptr, i32 iSkip = -1);






/////////////////////////////////////////////////////////////////////////////
// Verify that a nullptr-terminated string points to valid memory
inline bool __is_valid_string(const widechar * psz, memsize nMaxLength = INT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != nullptr);
}

// Verify that a nullptr-terminated string points to valid memory
inline bool __is_valid_string(const char * psz, memsize nMaxLength = UINT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != nullptr);
}

// Verify that a pointer points to valid memory
inline bool __is_valid_address(const void * p, memsize nBytes, bool bReadWrite = true)
{
#ifdef WINDOWS
   (bReadWrite);
   (nBytes);
#endif
   return (p != nullptr);
}
