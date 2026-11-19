#include "core/platform.h"
#include "core/filesystem/filemanager/file_list.h"
#include "aura/message/user.h"
#include "acme/platform/system.h"

int main()
{
   ::platform::system runtime;
   ::pointer<::filemanager::file_list> list(allocate_t{});
   list->install_message_routing(list);
   ::message::command copy("edit_copy", nullptr);
   ::message::command paste("edit_paste", nullptr);
   bool copyRegistered = list->has_command_handler(&copy);
   bool pasteRegistered = list->has_command_handler(&paste);
   list->destroy();
   if (!copyRegistered) return 1;
   if (!pasteRegistered) return 2;
   return 0;
}
