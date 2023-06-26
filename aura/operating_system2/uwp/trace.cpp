#include "framework.h"

#ifdef WINDOWS_DESKTOP
static void TraceDDE(const ::string & lpszPrefix, const MSG* pMsg)
{
   ENSURE_ARG(pMsg != nullptr);
   if (pMsg->message == WM_DDE_EXECUTE)
   {
      uptr nDummy;
      HGLOBAL hCommands;
      if (!UnpackDDElParam(WM_DDE_EXECUTE, pMsg->lParam,
                           &nDummy, (uptr*)&hCommands))
      {
//         ::infomration(::aura::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_EXECUTE lParam %08lX.\n",
         //          pMsg->lParam);
         return;
      }
      ASSERT(hCommands != nullptr);

      const char * lpszCommands = (const ::string &)::GlobalLock(hCommands);
      ENSURE_THROW(lpszCommands != nullptr, throw ::exception(error_no_memory));
//      ::infomration(::aura::trace::category_AppMsg, 0, "%s: Execute '%s'.\n", lpszPrefix, lpszCommands);
      ::GlobalUnlock(hCommands);
   }
   else if (pMsg->message == WM_DDE_ADVISE)
   {
      uptr nItem;
      ATOM aItem;
      HGLOBAL hAdvise;
      if (!UnpackDDElParam(WM_DDE_ADVISE, pMsg->lParam,
                           (uptr*)&hAdvise, &nItem))
      {
//         ::infomration(::aura::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_ADVISE lParam %08lX.\n",
//            pMsg->lParam);
         return;
      }
      aItem = (ATOM)nItem;
      ASSERT(aItem != nullptr);
      ASSERT(hAdvise != nullptr);

      DDEADVISE* lpAdvise = (DDEADVISE*)::GlobalLock(hAdvise);
      ENSURE_THROW(lpAdvise != nullptr, throw ::exception(error_no_memory));
      char szItem[80];
      szItem[0] = '\0';

      if (aItem != 0)
         ::GlobalGetAtomName(aItem, szItem, _countof(szItem));

      char szFormat[80];
      szFormat[0] = '\0';
      if (((::u32)0xC000 <= (::u32)lpAdvise->cfFormat) &&
            ((::u32)lpAdvise->cfFormat <= (::u32)0xFFFF))
      {
         ::GetClipboardFormatName(lpAdvise->cfFormat,
                                  szFormat, _countof(szFormat));

         // User defined clipboard formats have a range of 0xC000->0xFFFF
         // ::auraacmesystem() clipboard formats have other ranges, but no printable
         // format names.
      }

      information(
      "%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n",
      lpszPrefix, szItem, szFormat, lpAdvise->fAckReq,
      lpAdvise->fDeferUpd);
      ::GlobalUnlock(hAdvise);
   }
}
#endif


