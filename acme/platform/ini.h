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
//typedef ::u32 UINT;

//#ifndef TRUE
//#define TRUE 1
//#endif
//
//#ifndef FALSE
//#define FALSE 0
//#endif

CLASS_DECL_ACME int WritePrivateProfileString(
                                const char *lpAppName,
                                const char *lpKeyName,
                                const char *lpString,
                                const char *lpFileName
                                );

CLASS_DECL_ACME ::u32 GetPrivateProfileString(
                               const char *lpAppName,
                               const char *lpKeyName,
                               const char *lpDefault,
                               char *lpReturnedString, ::u32 nSize,
                               const char *lpFileName
                               );

CLASS_DECL_ACME ::u32 GetPrivateProfileInt(
                           const char *lpAppName,
                           const char *lpKeyName,
                           int nDefault,
                           const char *lpFileName
                           );

CLASS_DECL_ACME ::u32 GetPrivateProfileSection(
                                const char *lpAppName,
                                char *lpReturnedString, ::u32 nSize,
                                const char *lpFileName
                                );

CLASS_DECL_ACME ::u32 GetPrivateProfileSectionNames(
                                     char *lpszReturnBuffer, ::u32 nSize,
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
