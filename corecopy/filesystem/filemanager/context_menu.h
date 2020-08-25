#pragma once


#ifdef WINDOWS_DESKTOP

#include <ShlObj.h>

#endif

namespace filemanager
{


   class context_menu  :
      virtual public ::object
   {
   public:


#ifdef WINDOWS_DESKTOP

      comptr < IContextMenu >    m_pcontextmenu;
      comptr < IContextMenu2 >   m_pcontextmenu2;

#endif
      UINT              m_uiMinId;


      context_menu();
      virtual ~context_menu();


      void OnCommand(UINT uiId);
      void GetMessageString(UINT nID, string & rstrMessage);
      void GetVerb(UINT nID, string & rwstrMessage);


   };


} // namespace filemanager


