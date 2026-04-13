//
//  ini.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


//#ifdef _WIN32
//#include <windows.h>
//#else
//#include <stddef.h>
//
//#ifndef MAX_PATH
//#define MAX_PATH 260
//#endif

namespace acme
{

//typedef unsigned long DWORD;
//typedef int BOOL;
//typedef unsigned int UINT;

//#ifndef TRUE
//#define TRUE 1
//#endif
//
//#ifndef FALSE
//#define FALSE 0
//#endif

CLASS_DECL_ACME bool WritePrivateProfileString(
                                const char *lpAppName,
                                const char *lpKeyName,
                                const char *lpString,
                                const char *lpFileName
                                );

CLASS_DECL_ACME unsigned int GetPrivateProfileString(
                               const char *lpAppName,
                               const char *lpKeyName,
                               const char *lpDefault,
                               char *lpReturnedString, unsigned int nSize,
                               const char *lpFileName
                               );

CLASS_DECL_ACME unsigned int GetPrivateProfileInt(
                           const char *lpAppName,
                           const char *lpKeyName,
                           int nDefault,
                           const char *lpFileName
                           );

CLASS_DECL_ACME unsigned int GetPrivateProfileSection(
                                const char *lpAppName,
                                char *lpReturnedString, unsigned int nSize,
                                const char *lpFileName
                                );

CLASS_DECL_ACME unsigned int GetPrivateProfileSectionNames(
                                     char *lpszReturnBuffer, unsigned int nSize,
                                     const char *lpFileName
                                     );
//
//#ifndef WritePrivateProfileString
//#define WritePrivateProfileString WritePrivateProfileStringA
//#endif
//
//#ifndef GetPrivateProfileString
//#define GetPrivateProfileString GetPrivateProfileStringA
//#endif
//
//#ifndef GetPrivateProfileInt
//#define GetPrivateProfileInt GetPrivateProfileIntA
//#endif
//
//#ifndef GetPrivateProfileSection
//#define GetPrivateProfileSection GetPrivateProfileSectionA
//#endif
//
//#ifndef GetPrivateProfileSectionNames
//#define GetPrivateProfileSectionNames GetPrivateProfileSectionNamesA
//#endif
//
//#endif /* _WIN32 */
//
//#endif /* WINPROFILE_COMPAT_V2_H */


} // namespace acme
