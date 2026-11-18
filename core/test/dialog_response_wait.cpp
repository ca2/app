#include "acme/platform.h"
#include "acme/platform/system.h"
#include "acme/parallelization/task.h"
#include "acme/user/implementation/dialog_implementation.h"

namespace
{
   class responding_task : public ::task
   {
   public:
      ::user_interface::dialog_implementation * dialog = nullptr;
      int dispatched = 0;
      bool handle_messages() override
      {
         ++dispatched;
         dialog->set_dialog_response("continue");
         return true;
      }
      bool task_iteration() override { return true; }
   };
}

int main()
{
   ::platform::system runtime;
   ::pointer<::user_interface::dialog_implementation> early(allocate_t{});
   early->on_initialize_dialog();
   early->set_dialog_response("early");
   if (early->wait_for_dialog_response(0_s) != "early") return 1;

   ::pointer<responding_task> caller(allocate_t{});
   ::pointer<::user_interface::dialog_implementation> dialog(allocate_t{});
   dialog->on_initialize_dialog();
   caller->dialog = dialog;
   caller->m_bMessageThread = true;
   ::pointer<::task> previous = ::get_task();
   caller->m_taskindex = ::current_task_index();
   if (previous) caller->increment_reference_count();
   ::set_task(caller);
   auto response = dialog->wait_for_dialog_response(1_s);
   if (previous)
   {
      previous->increment_reference_count();
      ::set_task(previous);
   }
   if (response != "continue" || caller->dispatched != 1) return 2;
   early->m_pdialog.release();
   dialog->m_pdialog.release();
   early->destroy();
   dialog->destroy();
   return 0;
}
