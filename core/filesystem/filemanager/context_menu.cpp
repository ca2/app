#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   context_menu::context_menu()
   {

   }

   context_menu::~context_menu()
   {

   }


   void context_menu::GetMessageString(UINT nID, string &rstrMessage)
   {

#ifdef WINDOWS_DESKTOP

      if (m_pcontextmenu.is_null())
      {

         return;

      }

      string & str = rstrMessage;

      LPSTR psz = str.get_string_buffer(1024);

      m_pcontextmenu->GetCommandString(
         nID - 0x1000,
         GCS_HELPTEXTA,
         nullptr,
         psz,

         1024);

      str.release_string_buffer();

#endif

   }


   void context_menu::GetVerb(UINT nID, string & rwstrMessage)
   {

#ifdef WINDOWS_DESKTOP

      if (m_pcontextmenu.is_null())
      {

         return;

      }

      string & str = rwstrMessage;

      char * psz = str.get_string_buffer(1024);

      m_pcontextmenu->GetCommandString(
         nID - 0x1000,
         GCS_VERBW,
         nullptr,
         (LPSTR) psz,

         1024);

      str.release_string_buffer();

#endif

   }


   void context_menu::OnCommand(UINT uiId)
   {
#ifdef WINDOWS_DESKTOP
      if(m_pcontextmenu.is_null())
         return;

      CMINVOKECOMMANDINFO info;

      string wstrVerb;
      GetVerb(uiId, wstrVerb);

      info.cbSize = sizeof(info);
      info.fMask = CMIC_MASK_ASYNCOK;
      info.lpParameters = nullptr;

      info.lpDirectory = nullptr;

      auto psession = Session;

      info.hwnd = psession->get_active_ui()->m_puiThis->get_handle();
      info.lpVerb = MAKEINTRESOURCEA(uiId - 0x1000);

      info.nShow = SW_SHOWNORMAL;

      m_pcontextmenu->InvokeCommand((LPCMINVOKECOMMANDINFO) &info);

#endif
   }


} // namespace filemanager



