#include "framework.h"

#ifdef WINDOWS_DESKTOP
static void TraceDDE(const_char_pointer lpszPrefix, const MSG* pMsg)
{
   ENSURE_ARG(pMsg != nullptr);
   if (pMsg->message == WM_DDE_EXECUTE)
   {
      uptr nDummy;
      HGLOBAL hCommands;
      if (!UnpackDDElParam(WM_DDE_EXECUTE, pMsg->lParam,
                           &nDummy, (uptr*)&hCommands))
      {
//         ::information(::apex::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_EXECUTE lParam %08lX.\n",
         //          pMsg->lParam);
         return;
      }
      ASSERT(hCommands != nullptr);

      const_char_pointer lpszCommands = (const_char_pointer )::GlobalLock(hCommands);
      ENSURE_THROW(lpszCommands != nullptr, throw ::exception(error_no_memory));
//      ::information(::apex::trace::category_AppMsg, 0, "%s: Execute '%s'.\n", lpszPrefix, lpszCommands);
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
//         ::information(::apex::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_ADVISE lParam %08lX.\n",
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
      if (((unsigned int)0xC000 <= (unsigned int)lpAdvise->cfFormat) &&
            ((unsigned int)lpAdvise->cfFormat <= (unsigned int)0xFFFF))
      {
         ::GetClipboardFormatName(lpAdvise->cfFormat,
                                  szFormat, _countof(szFormat));

         // User defined clipboard formats have a range of 0xC000->0xFFFF
         // ::apexacmesystem() clipboard formats have other ranges, but no printable
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


