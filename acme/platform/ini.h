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

//typedef ulong DWORD;
//typedef ::i32 BOOL;
//typedef ::u32 UINT;

//#ifndef TRUE
//#define TRUE 1
//#endif
//
//#ifndef FALSE
//#define FALSE 0
//#endif

CLASS_DECL_ACME ::i32 WritePrivateProfileString(
                                const_char_pointer lpAppName,
                                const_char_pointer lpKeyName,
                                const_char_pointer lpString,
                                const_char_pointer lpFileName
                                );

CLASS_DECL_ACME ::u32 GetPrivateProfileString(
                               const_char_pointer lpAppName,
                               const_char_pointer lpKeyName,
                               const_char_pointer lpDefault,
                               char_pointer lpReturnedString, ::u32 nSize,
                               const_char_pointer lpFileName
                               );

CLASS_DECL_ACME ::u32 GetPrivateProfileInt(
                           const_char_pointer lpAppName,
                           const_char_pointer lpKeyName,
                           ::i32 nDefault,
                           const_char_pointer lpFileName
                           );

CLASS_DECL_ACME ::u32 GetPrivateProfileSection(
                                const_char_pointer lpAppName,
                                char_pointer lpReturnedString, ::u32 nSize,
                                const_char_pointer lpFileName
                                );

CLASS_DECL_ACME ::u32 GetPrivateProfileSectionNames(
                                     char_pointer lpszReturnBuffer, ::u32 nSize,
                                     const_char_pointer lpFileName
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
