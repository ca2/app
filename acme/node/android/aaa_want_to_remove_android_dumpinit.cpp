#include "framework.h"


// /////////////////////////////////////////////////////////////////////////////
// // ___DEBUG_STATE implementation

// #ifndef ___NO_DEBUG_CRT
// //static _CRT_DUMP_CLIENT pfnOldCrtDumpClient = nullptr;

// #ifdef __DEBUG


// void __cdecl __crt_dump_client(void * pvData, size_t nBytes)
// {
//    char sz[1024];
//    try
//    {

// //      if(_CrtReportBlockType(pvData) != ___CLIENT_BLOCK)
//       //       return;

// //      ::generic * pca = (::generic * ) pvData;

//       ::generic * pobject = nullptr;

//       if(pobject == nullptr)
//       {
// // xxx            C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "unknown generic at $%p, %u bytes long\n", pvData, nBytes));
//       }
//       else if(::get_context_system()->m_pdumpcontext->GetDepth() > 0)
//       {
//          // long form
//          pobject->dump(*::get_context_system()->m_pdumpcontext);
//          *::get_context_system()->m_pdumpcontext << "\n";
//       }
//       if(false) // else
//       {
//          //::generic & obj = *pobject;
//          // short form
// // xxx         C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "a %hs generic at $%p, %u bytes long\n", typeid(obj).name(), pvData, nBytes));
//          *::get_context_system()->m_pdumpcontext << sz;
//       }
//    }
//    catch(...)
//    {
//       *::get_context_system()->m_pdumpcontext << sz;
//    }
// }

// i32 __cdecl __crt_report_hook(i32 nRptType, char *szMsg, i32* pResult)
// {
//    // no hook on asserts or when m_pFile is nullptr
//    if (nRptType == _CRT_ASSERT || ::get_context_system()->m_pdumpcontext->m_pfile == nullptr)
//       return FALSE;

//    ASSERT( pResult != nullptr );
//    if( pResult == nullptr )
//       __throw(invalid_argument_exception());

//    ASSERT( szMsg != nullptr );
//    if( szMsg == nullptr )
//       __throw(invalid_argument_exception());

//    // non-nullptr m_pFile, so go through ::get_context_system()->m_pdumpcontext for the message
//    *pResult = FALSE;
//    *::get_context_system()->m_pdumpcontext << szMsg;
//    //Allow other report hooks to be called.
//    return FALSE;
// }


// #endif //__DEBUG


// #endif // ___NO_DEBUG_CRT


