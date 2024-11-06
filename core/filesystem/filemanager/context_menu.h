#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"


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
      unsigned int              m_uiMinId;


      context_menu();
      ~context_menu() override;


      void OnCommand(unsigned int uId);
      void GetMessageString(unsigned int nID, string & rstrMessage);
      void GetVerb(unsigned int nID, string & rwstrMessage);


   };


} // namespace filemanager


