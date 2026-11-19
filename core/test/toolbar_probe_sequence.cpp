#include "core/platform.h"
#include "berg/user/user/toolbar.h"
#include "acme/user/user/tool_item.h"
#include "aura/message/user.h"
#include "acme/platform/system.h"

namespace
{
   class toolbar : public ::user::toolbar
   {
   public:
      pointer_array<::user::tool_item> items;
      ::collection::count tool_item_count() override { return items.size(); }
      ::user::tool_item * tool_item_at(::collection::index i) override { return items[i]; }
      void update_dialog_controls(::channel *) override {}
      void route_command(::message::command * command, bool) override
      {
         if (command->is_handled(this)) return;
         command->handle(this);
      }
   };
   class owner : public ::user::interaction
   {
   public:
      string_array_base probed;
      void route_command(::message::command * command, bool) override
      {
         if (command->is_handled(this)) return;
         command->handle(this);
         probed.add(command->command_id().as_string());
         command->m_bRet = true;
      }
   };
}
int main()
{
   ::platform::system runtime;
   ::pointer<toolbar> bar(allocate_t{});
   ::pointer<owner> target(allocate_t{});
   for (auto id : {"levelup", "edit_copy", "edit_paste"})
   {
      ::pointer<::user::tool_item> item(allocate_t{});
      item->id() = id;
      bar->items.add(item);
   }
   bar->on_command_probe(target, true);
   bool correct = target->probed.size() == 3 && target->probed[1] == "edit_copy" && target->probed[2] == "edit_paste";
   bar->items.erase_all();
   bar->destroy();
   target->destroy();
   return correct ? 0 : 1;
}
