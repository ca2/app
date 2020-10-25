#include "framework.h"
#include <dde.h>


HDDEDATA CALLBACK os_dde_callback(
   u32 uType,
   u32 uFmt,
   HCONV hconv,
   HDDEDATA hsz1,
   HDDEDATA hsz2,
   HDDEDATA hdata,
   HDDEDATA dwData1,
   HDDEDATA dwData2
)
{
   UNREFERENCED_PARAMETER(uFmt);
   UNREFERENCED_PARAMETER(hconv);
   UNREFERENCED_PARAMETER(dwData1);
   UNREFERENCED_PARAMETER(dwData2);
   switch (uType)
   {
   case XTYP_REGISTER:
   case XTYP_UNREGISTER:
      return (HDDEDATA) nullptr;

   case XTYP_ADVDATA:
      return (HDDEDATA)DDE_FACK;

   case XTYP_XACT_COMPLETE:
      return (HDDEDATA) nullptr;

   case XTYP_CONNECT:
   {
      __pointer(application) papp = ::get_thread()->get_context_application();
      if (!DdeCmpStringHandles((HSZ)hsz1, papp->m_hszSystemTopic))
      {
         if (!DdeCmpStringHandles((HSZ)hsz2, papp->m_hszAppName))
         {
            return (HDDEDATA)TRUE;
         }
      }
      return (HDDEDATA)FALSE;
   }

   case XTYP_DISCONNECT:
      return (HDDEDATA) nullptr;

   case XTYP_EXECUTE:
   {
      // get the command string
      u32 dwSize = DdeGetData(
         hdata,
         nullptr,
         0,
         0);

      string str;

      dwSize = DdeGetData(
         hdata,
         (LPBYTE)str.get_string_buffer(dwSize),
         dwSize,
         0);

      str.release_string_buffer();

      //__throw(not_implemented());
      /*
      // execute the command
      if (!System.OnDDECommand( (LPTSTR)(const wchar_t *)str))
         TRACE1("Error: failed to execute DDE command '%S'.\n", str);
      */
      //
      VERIFY(DdeFreeDataHandle(hdata));
      return (HDDEDATA) nullptr;
   }

   default:
      return (HDDEDATA) nullptr;
   }
}

