#include "framework.h"


// /////////////////////////////////////////////////////////////////////////////
// // ___DEBUG_STATE implementation

// #ifndef ___NO_DEBUG_CRT
// //static _CRT_DUMP_CLIENT pfnOldCrtDumpClient = nullptr;

// #ifdef _DEBUG


// void __cdecl __crt_dump_client(void * pvData, size_t nBytes)
// {
//    char sz[1024];
//    try
//    {

// //      if(_CrtReportBlockType(pvData) != ___CLIENT_BLOCK)
//       //       return;

// //      ::object * pca = (::object * ) pvData;

//       ::particle * pparticle = nullptr;

//       if(pparticle == nullptr)
//       {
// // xxx            C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "unknown object at $%p, %u bytes long\n", pvData, nBytes));
//       }
//       else if(::apexacmesystem()->m_pdumpcontext->GetDepth() > 0)
//       {
//          // long form
//          pparticle->dump(*::apexacmesystem()->m_pdumpcontext);
//          *::apexacmesystem()->m_pdumpcontext << "\n";
//       }
//       if(false) // else
//       {
//          //::object & obj = *pparticle;
//          // short form
// // xxx         C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "a %hs object at $%p, %u bytes long\n", typeid(obj).name(), pvData, nBytes));
//          *::apexacmesystem()->m_pdumpcontext << sz;
//       }
//    }
//    catch(...)
//    {
//       *::apexacmesystem()->m_pdumpcontext << sz;
//    }
// }

// int __cdecl __crt_report_hook(int nRptType, char *szMsg, int* pResult)
// {
//    // no hook on asserts or when m_pFile is nullptr
//    if (nRptType == _CRT_ASSERT || ::apexacmesystem()->m_pdumpcontext->m_pfile == nullptr)
//       return false;

//    ASSERT( pResult != nullptr );
//    if( pResult == nullptr )
//       throw ::exception(error_bad_argument);

//    ASSERT( szMsg != nullptr );
//    if( szMsg == nullptr )
//       throw ::exception(error_bad_argument);

//    // non-nullptr m_pFile, so go through ::apexacmesystem()->m_pdumpcontext for the message
//    *pResult = false;
//    *::apexacmesystem()->m_pdumpcontext << szMsg;
//    //Allow other report hooks to be called.
//    return false;
// }


// #endif //__DEBUG


// #endif // ___NO_DEBUG_CRT


