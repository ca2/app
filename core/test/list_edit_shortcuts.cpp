#include "core/platform.h"
#include "core/user/user/list.h"
#include "aura/message/user.h"
#include "acme/platform/system.h"
namespace
{
   class list : public ::user::list
   {
   public:
      string_array_base commands;
      void route_command(::message::command * command, bool) override
      {
         commands.add(command->command_id().as_string());
         command->m_bRet = true;
      }
   };
}
int main()
{
   ::platform::system runtime;
   ::pointer<list> control(allocate_t{});
   if (control->handle_edit_shortcut(::user::e_key_c, false, nullptr)) return 1;
   if (control->handle_edit_shortcut(::user::e_key_v, false, nullptr)) return 2;
   if (!control->handle_edit_shortcut(::user::e_key_c, true, nullptr)) return 3;
   if (!control->handle_edit_shortcut(::user::e_key_v, true, nullptr)) return 4;
   if (control->commands.size() != 2 || control->commands[0] != "edit_copy" || control->commands[1] != "edit_paste") return 5;
   control->destroy();
   return 0;
}
