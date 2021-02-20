#include "framework.h"


namespace windows
{


   void window::DeleteTempMap()
   {

      //oswindow_map* pMap = __get_module_state()->m_pmapHWND;

      //if(::is_null(pMap))
      //   return;

      //single_lock synchronizationlock(&pMap->m_mutex, true);

      array < oswindow > oswindowaRemove;
      array < __pointer(::windows::window) > wndptraRemove;

      //POSITION pos = pMap->m_temporaryMap.get_start_position();
      //while (pos != nullptr)
      //{
      //   HANDLE h; // just used for asserts
      //   ::windows::window * pTemp;
      //   pMap->m_temporaryMap.get_next_assoc(pos, h, pTemp);

      //   if(!::IsWindow((oswindow) h))
      //   {
      //      oswindowaRemove.add((oswindow) h);
      //      wndptraRemove.add(pTemp);
      //   }

      //}

      //for(i32 i = 0; i < wndptraRemove.get_count(); i++)
      //{
      //   wndptraRemove[i]->m_handlea[0] = nullptr;
      //   wndptraRemove[i]->m_handlea[1] = nullptr;

      //   (*pMap->m_pfnDestructObject)(wndptraRemove[i]);   // destruct the object
      //}

      //for(i32 i = 0; i < oswindowaRemove.get_count(); i++)
      //{
      //   pMap->m_temporaryMap.remove_key(oswindowaRemove[i]);
      //}

   }


} // namespace windows


