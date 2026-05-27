#ifndef ___NSIS_PLUGIN__H___
#define ___NSIS_PLUGIN__H___

#ifdef __cplusplus
extern "C" {
#endif

#include "api.h"
#include "nsis_tchar.h" // BUGBUG: Why cannot our plugins use the compilers tchar.h?

#ifndef NSISCALL
#  define NSISCALL WINAPI
#endif

#define EXDLL_INIT()           {  \
        g_stringsize=string_size; \
        g_stacktop=stacktop;      \
        g_variables=variables; }

typedef struct _stack_t {
  struct _stack_t *next;
#ifdef UNICODE
  WCHAR text[1]; // this should be the length of g_stringsize when allocating
#else
  ::i8 text[1];
#endif
} stack_t;

enum
{
INST_0,         // $0
INST_1,         // $1
INST_2,         // $2
INST_3,         // $3
INST_4,         // $4
INST_5,         // $5
INST_6,         // $6
INST_7,         // $7
INST_8,         // $8
INST_9,         // $9
INST_R0,        // $R0
INST_R1,        // $R1
INST_R2,        // $R2
INST_R3,        // $R3
INST_R4,        // $R4
INST_R5,        // $R5
INST_R6,        // $R6
INST_R7,        // $R7
INST_R8,        // $R8
INST_R9,        // $R9
INST_CMDLINE,   // $CMDLINE
INST_INSTDIR,   // $INSTDIR
INST_OUTDIR,    // $OUTDIR
INST_EXEDIR,    // $EXEDIR
INST_LANG,      // $LANGUAGE
__INST_LAST
};

extern ::u32 g_stringsize;
extern stack_t **g_stacktop;
extern char_pointer g_variables;

void NSISCALL pushstring(LPCTSTR str);
void NSISCALL pushintptr(INT_PTR value);
#define pushint(v) pushintptr((INT_PTR)(v))
::i32 NSISCALL popstring(char_pointer str); // 0 on success, 1 on empty stack
::i32 NSISCALL popstringn(char_pointer str, ::i32 maxlen); // with length limit, pass 0 for g_stringsize
INT_PTR NSISCALL popintptr();
#define popint() ( (::i32) popintptr() )
::i32 NSISCALL popint_or(); // with support for or'ing (2|4|8)
INT_PTR NSISCALL nsishelper_str_to_ptr(LPCTSTR s);
#define myatoi(s) ( (::i32) nsishelper_str_to_ptr(s) ) // converts a string to an integer
::u32 NSISCALL myatou(LPCTSTR s); // converts a string to an ::u32 integer, decimal only
::i32 NSISCALL myatoi_or(LPCTSTR s); // with support for or'ing (2|4|8)
char_pointer NSISCALL getuservariable(const ::i32 varnum);
void NSISCALL setuservariable(const ::i32 varnum, LPCTSTR ::payload);

#ifdef UNICODE
#define PopStringW(x) popstring(x)
#define PushStringW(x) pushstring(x)
#define SetUserVariableW(x,y) setuservariable(x,y)

::i32  NSISCALL PopStringA(char_pointer ansiStr);
void NSISCALL PushStringA(const ::string & ansiStr);
void NSISCALL GetUserVariableW(const ::i32 varnum, LPWSTR wideStr);
void NSISCALL GetUserVariableA(const ::i32 varnum, char_pointer ansiStr);
void NSISCALL SetUserVariableA(const ::i32 varnum, const ::string & ansiStr);

#else
// ANSI defs

#define PopStringA(x) popstring(x)
#define PushStringA(x) pushstring(x)
#define SetUserVariableA(x,y) setuservariable(x,y)

::i32  NSISCALL PopStringW(LPWSTR wideStr);
void NSISCALL PushStringW(LPWSTR wideStr);
void NSISCALL GetUserVariableW(const ::i32 varnum, LPWSTR wideStr);
void NSISCALL GetUserVariableA(const ::i32 varnum, char_pointer ansiStr);
void NSISCALL SetUserVariableW(const ::i32 varnum, const ::wide_character * wideStr);

#endif

#ifdef __cplusplus
}
#endif

#endif//!___NSIS_PLUGIN__H___
