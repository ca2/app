#pragma once



// This is acme API library.
// 
// 
//
// 
// 
// 
// 
// 


#ifndef __DEBUGAPI_H__
#define __DEBUGAPI_H__

#pragma once

#ifdef __cplusplus

namespace acme
{
extern "C" {
#endif
#define TRACE_MAX_NAME_SIZE 64


uptr __stdcall gen_TraceOpenProcess( u32 idProcess );
void __stdcall gen_TraceCloseProcess( uptr dwProcess );
void __stdcall gen_TraceSnapshotProcess( uptr dwProcess );


void __cdecl gen_TraceVA(uptr dwModule, const char *pszFileName, i32 nLineNo,
                  uptr dwCategory, UINT nLevel, const CHAR *pszFormat, va_list ptr);
void __cdecl gen_TraceVU(uptr dwModule,const char *pszFileName, i32 nLineNo,
                  uptr dwCategory, UINT nLevel, const WCHAR *pszFormat, va_list ptr);

bool __stdcall gen_TraceLoadSettingsA(const CHAR *pszFileName, uptr dwProcess = 0);
bool __stdcall gen_TraceLoadSettingsU(const WCHAR *pszFileName, uptr dwProcess = 0);
bool __stdcall gen_TraceSaveSettingsA(const CHAR *pszFileName, uptr dwProcess = 0);
bool __stdcall gen_TraceSaveSettingsU(const WCHAR *pszFileName, uptr dwProcess = 0);

/*typedef struct TRACESETTINGS
{
   UINT nLevel;
   TRACESTATUS eStatus;
} TRACESETTINGS;

typedef struct TRACEPROCESSSETTINGS
{
   UINT nLevel;
   bool bEnabled, bFuncAndCategoryNames, bFileNameAndLineNo;
} TRACEPROCESSSETTINGS;

typedef struct TRACEPROCESSINFO
{
   WCHAR szName[TRACE_MAX_NAME_SIZE], szPath[MAX_PATH];
   u32 dwId;
   TRACEPROCESSSETTINGS settings;
   i32 nModules;
} TRACEPROCESSINFO;

typedef struct TRACEMODULEINFO
{
   WCHAR szName[TRACE_MAX_NAME_SIZE], szPath[MAX_PATH];
   TRACESETTINGS settings;
   uptr dwModule;
   i32 nCategories;
} TRACEMODULEINFO;

typedef struct TRACECATEGORYINFO
{
   WCHAR szName[TRACE_MAX_NAME_SIZE];
   TRACESETTINGS settings;
   uptr dwCategory;
} TRACECATEGORYINFO;

bool __stdcall gen_TraceGetProcessInfo(uptr dwProcess, TRACEPROCESSINFO* pProcessInfo);
void __stdcall gen_TraceGetModuleInfo(uptr dwProcess, i32 iModule, TRACEMODULEINFO* pModuleInfo);
void __stdcall gen_TraceGetCategoryInfo(uptr dwProcess, uptr dwModule, i32 iCategory, TRACECATEGORYINFO* pAtlTraceCategoryInfo);
*/

#ifdef UNICODE
#define gen_TraceRegisterCategory AtlTraceRegisterCategoryU
#define gen_TraceGetUpdateEventName AtlTraceGetUpdateEventNameU
#define gen_TraceGetUpdateEventName_s AtlTraceGetUpdateEventNameU_s
#define gen_Trace AtlTraceU
#define gen_TraceV AtlTraceVU
#define gen_TraceLoadSettings AtlTraceLoadSettingsU
#define gen_TraceSaveSettings AtlTraceSaveSettingsU

#else
#define gen_TraceRegisterCategory AtlTraceRegisterCategoryA
#define gen_TraceGetUpdateEventName AtlTraceGetUpdateEventNameA
#define gen_TraceGetUpdateEventName_s AtlTraceGetUpdateEventNameA_s
#define gen_Trace AtlTraceA
#define gen_TraceV AtlTraceVA
#define gen_TraceLoadSettings AtlTraceLoadSettingsA
#define gen_TraceSaveSettings AtlTraceSaveSettingsA

#endif

#ifdef __cplusplus
};

};  // namespace acme
#endif

#endif  // __DEBUGAPI_H__
