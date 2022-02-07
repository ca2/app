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

// //      ::matter * pca = (::matter * ) pvData;

//       ::matter * pobject = nullptr;

//       if(pobject == nullptr)
//       {
// // xxx            C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "unknown matter at $%p, %u bytes long\n", pvData, nBytes));
//       }
//       else if(::acme::get_system()->m_pdumpcontext->GetDepth() > 0)
//       {
//          // long form
//          pobject->dump(*::acme::get_system()->m_pdumpcontext);
//          *::acme::get_system()->m_pdumpcontext << "\n";
//       }
//       if(false) // else
//       {
//          //::matter & obj = *pobject;
//          // short form
// // xxx         C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "a %hs matter at $%p, %u bytes long\n", typeid(obj).name(), pvData, nBytes));
//          *::acme::get_system()->m_pdumpcontext << sz;
//       }
//    }
//    catch(...)
//    {
//       *::acme::get_system()->m_pdumpcontext << sz;
//    }
// }

// i32 __cdecl __crt_report_hook(i32 nRptType, char *szMsg, i32* pResult)
// {
//    // no hook on asserts or when m_pFile is nullptr
//    if (nRptType == _CRT_ASSERT || ::acme::get_system()->m_pdumpcontext->m_pfile == nullptr)
//       return false;

//    ASSERT( pResult != nullptr );
//    if( pResult == nullptr )
//       throw ::exception(error_bad_argument);

//    ASSERT( szMsg != nullptr );
//    if( szMsg == nullptr )
//       throw ::exception(error_bad_argument);

//    // non-nullptr m_pFile, so go through ::acme::get_system()->m_pdumpcontext for the message
//    *pResult = false;
//    *::acme::get_system()->m_pdumpcontext << szMsg;
//    //Allow other report hooks to be called.
//    return false;
// }


// #endif //__DEBUG


// #endif // ___NO_DEBUG_CRT


