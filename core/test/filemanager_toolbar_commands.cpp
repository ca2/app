#include "core/platform.h"
#include "core/filesystem/filemanager/frame.h"
#include "core/filesystem/filemanager/file_list.h"
#include "berg/user/user/document.h"
#include "aura/message/user.h"
#include "acme/platform/system.h"

namespace
{
   class test_list : public ::filemanager::file_list
   {
   public:
      int copies = 0;
      int pastes = 0;
      int probes = 0;
      void route_command(::message::command * command, bool) override
      {
         if (command->m_bProbing) { ++probes; command->enable(true); }
         else if (command->command_id() == "edit_copy") ++copies;
         else if (command->command_id() == "edit_paste") ++pastes;
         else return;
         command->m_bRet = true;
      }
   };
}

int main()
{
   ::platform::system runtime;
   ::pointer<::user::document> document(allocate_t{});
   ::pointer<test_list> list(allocate_t{});
   ::pointer<::filemanager::frame> frame(allocate_t{});
   ::pointer<::user::impact> otherView(allocate_t{});
   static_cast<::user::impact *>(list.m_p)->m_pdocument = document;
   document->m_impacta.add(list);
   frame->m_pimpactMain = list;
   // Toolbar commands must reach the list even when another view is active.
   frame->set_active_impact(otherView, false);
   for (auto id : {"edit_copy", "edit_paste"})
   {
      ::message::command command(id, nullptr);
      frame->_001SendCommand(&command);
      if (!command.m_bRet) return 1;
      ::message::command probe(id, nullptr);
      frame->_001SendCommandProbe(&probe);
      if (!probe.m_bRet) return 2;
   }
   if (list->copies != 1 || list->pastes != 1 || list->probes != 2) return 3;
   frame->m_pimpactMain.release();
   frame->set_active_impact(nullptr, false);
   document->m_impacta.erase_all();
   static_cast<::user::impact *>(list.m_p)->m_pdocument.release();
   frame->destroy();
   list->destroy();
   document->destroy();
   return 0;
}
