#include "framework.h"

#ifndef _UWP

CLASS_DECL_APEX i32 __cdecl _CrtReportBlockType(const void * p);

CLASS_DECL_APEX i32 __cdecl _CrtSetReportMode(i32, i32);

CLASS_DECL_APEX i32 __cdecl _CrtSetReportHook2(i32, i32(__cdecl*)(i32, char *, i32 *));

//CLASS_DECL_APEX _CRT_DUMP_CLIENT DECL_C _CrtSetDumpClient(_CRT_DUMP_CLIENT _PFnNewDump);

CLASS_DECL_APEX i32 __cdecl _CrtSetDbgFlag(i32);

CLASS_DECL_APEX i32 __cdecl _CrtDumpMemoryLeaks();

#endif

/*
void * DECL_C _malloc_dbg(size_t _Size, i32 _BlockType, const char * _Filename, i32 _LineNumber)
{
return malloc(_Size);
}

void * DECL_C _calloc_dbg(size_t _Count, size_t _Size, i32 _BlockType, const char * _Filename, i32 _LineNumber)
{
return malloc(_Count * _Size);
}

void * DECL_C _realloc_dbg(void * _Memory, size_t _NewSize, i32 _BlockType, const char * _Filename, i32 _LineNumber)
{
return realloc(_Memory, _NewSize);
}

void * DECL_C _recalloc_dbg(void * _Memory, size_t _NumOfElements, size_t _SizeOfElements, i32 _BlockType, const char * _Filename, i32 _LineNumber)
{
return realloc(_Memory, _NumOfElements * _SizeOfElements);
}

void * DECL_C _expand_dbg(void * _Memory, size_t _NewSize, i32 _BlockType, const char * _Filename, i32 _LineNumber)
{
return realloc(_Memory, _NewSize);
}

void DECL_C _free_dbg(void * _Memory, i32 _BlockType)
{
free(_Memory);
}

*/

//CLASS_DECL_APEX int __cdecl debug_report(
//   int _ReportType,
//   const char * _Filename,
//   int _LineNumber,
//   const char * _ModuleName,
//   const char * _Format,
//   ...)
//{
//   return 0;
//}


#ifndef _UWP

CLASS_DECL_APEX i32 __cdecl _CrtReportBlockType(const void * p)
{
   return ___CLIENT_BLOCK;
}

CLASS_DECL_APEX i32 __cdecl _CrtSetReportMode(i32, i32)
{
   return true;
}

CLASS_DECL_APEX i32 __cdecl _CrtSetReportHook2(i32, i32(__cdecl*)(i32, char *, i32 *))
{
   return true;
}

//CLASS_DECL_APEX _CRT_DUMP_CLIENT DECL_C _CrtSetDumpClient(_CRT_DUMP_CLIENT _PFnNewDump)
//{
//   return nullptr;
//}

CLASS_DECL_APEX i32 __cdecl _CrtSetDbgFlag(i32)
{
   return true;
}

CLASS_DECL_APEX i32 __cdecl _CrtDumpMemoryLeaks()
{
   return true;
}


// #ifndef _UWP
#endif