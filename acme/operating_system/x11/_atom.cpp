//
// Created by camilo on 09/04/2022 16:18 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_.h"


namespace x11
{


   const char * g_pszAtomName[] = {
      "_NET_WM_STATE",
      "_NET_WM_STATE_ABOVE",
      "_NET_WM_STATE_BELOW",
      "_NET_WM_STATE_HIDDEN",
      "_NET_WM_STATE_MAXIMIZED_HORZ",
      "_NET_WM_STATE_MAXIMIZED_VERT",
      "_NET_WM_STATE_FULLSCREEN",
      "_NET_WM_STATE_SKIP_TASKBAR",
      "WM_NAME",
      "WM_STATE",
      "_NET_ACTIVE_WINDOW",
      "_NET_CLIENT_LIST_STACKING",
      "_NET_CLIENT_LIST",
      "_NET_WM_WINDOW_TYPE",
      "_NET_WM_WINDOW_TYPE_NORMAL",
      "_NET_WM_WINDOW_TYPE_SPLASH",
      "_NET_WM_CM_S0",

   };


   const char * atom_name(enum_atom eatom)
   {

      int iAtom = (int) eatom;

      if (iAtom < 0 || iAtom >= e_atom_count)
      {

         return nullptr;

      }

      return g_pszAtomName[iAtom];

   }


   int atom_count()
   {

      return e_atom_count;

   }


} // namespace x11



