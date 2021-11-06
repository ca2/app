#pragma once


//#ifdef WINDOWS_DESKTOP
//
//#include <ShlObj.h>
//
//#endif

namespace filemanager
{


   class context_menu  :
      virtual public ::object
   {
   public:


//#ifdef WINDOWS_DESKTOP
//
//      comptr < IContextMenu >    m_pcontextmenu;
//      comptr < IContextMenu2 >   m_pcontextmenu2;
//
//#endif
      ::u32              m_uiMinId;


      context_menu();
      virtual ~context_menu();


      void OnCommand(::u32 uId);
      void GetMessageString(::u32 nID, string & rstrMessage);
      void GetVerb(::u32 nID, string & rwstrMessage);


   };


} // namespace filemanager


