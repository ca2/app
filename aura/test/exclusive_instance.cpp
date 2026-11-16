#include "aura/platform.h"
#include "aura/platform/application.h"
#include "aura/user/user/interaction.h"
#include "acme/platform/system.h"
#include "acme/exception/exit.h"
#include "acme/parallelization/mutex.h"
#include "acme/handler/request.h"
#include "apex/interprocess/caller.h"
#include "apex/interprocess/communication.h"
#include "apex/interprocess/call.h"
#include "apex/interprocess/task.h"
#if defined(WINDOWS)
#include "acme/_operating_system.h"
#endif
namespace
{
   class test_app : public ::aura::application
   {
   public:
      using ::task::m_pacmeuserinteractionMain;
      bool m_handled = true;
      int m_requests = 0;
      void defer_process_command_line() override {}
      bool check_exclusive(bool & handled) override { handled = m_handled; return false; }
      void post_request(::request *) override { ++m_requests; }
   };
   class test_window : public ::user::interaction
   {
   public:
      int m_display = 0;
      int m_front = 0;
      int m_foreground = 0;
      int m_posts = 0;
      bool m_visible = false;
      void user_post(const ::procedure & procedure) override { ++m_posts; procedure(); }
      bool is_this_visible(::user::enum_layout) override { return m_visible; }
      void display(::e_display, const ::user::activation &) override { ++m_display; }
      void order(::zorder) override {}
      void bring_to_front() override { ++m_front; }
      void set_foreground_window(::user::activation_token *) override { ++m_foreground; }
   };
   class test_caller : public ::interprocess::caller
   {
   public:
      bool m_fail = false;
      int m_calls = 0;
      void call(const ::scoped_string &, const class ::time &) override
      {
         ++m_calls;
         if (m_fail) throw ::exception(error_failed);
      }
   };
   class test_communication : public ::interprocess::communication
   {
   public:
      ::pointer<test_caller> m_caller;
      ::interprocess::caller & caller(const ::scoped_string &, const ::atom &) override { return *m_caller; }
   };
}
int main()
{
   ::platform::system runtime;
   ::exception::s_bEnableCallStackBackTrace = false;
   ::pointer<test_app> app(allocate_t{});
   app->m_papplication = app;
   try { app->on_prepare_application(); return 1; }
   catch (const ::exit_exception & exit)
   {
      if (exit.m_estatus != error_exit_system || exit.m_estatusSecond != ::success) return 2;
   }
   app->m_handled = false;
   try { app->on_prepare_application(); return 3; }
   catch (const ::exit_exception & exit) { if (exit.m_estatus != error_exit_system) return 4; }
   ::pointer<test_window> window(allocate_t{});
   window->m_papplication = app;
   app->m_pacmeuserinteractionMain = window;
   bool handled = false;
   app->on_additional_local_instance(handled, "weather.exe", 999999, "weather.exe : build=test");
   if (!handled || app->m_requests != 1 || window->m_display != 1
      || window->m_front != 1 || window->m_foreground != 1 || window->m_posts != 1) return 5;
   window->m_visible = true;
   app->on_additional_local_instance(handled, "weather.exe", 999999, "weather.exe : build=test");
   if (window->m_display != 1 || window->m_front != 2) return 6;
   ::pointer<test_communication> communication(allocate_t{});
   communication->m_papplication = app;
   communication->m_strApp = "test";
   communication->m_atomApp = "123";
   communication->m_caller = ::pointer<test_caller>(allocate_t{});
   communication->m_caller->m_papplication = app;
   ::pointer<::interprocess::call> call(allocate_t{}, communication, "test", "application", "on_additional_local_instance");
   ::interprocess::task delivered(call, 999999, 1);
   ::property_set properties;
   delivered.do_task("application", "on_additional_local_instance", properties);
   if (communication->m_caller->m_calls != 1) return 12;
   if (!delivered.m_tristateHandled.is_set_true()) return 7;
   communication->m_caller->m_fail = true;
   ::interprocess::task failed(call, 999999, 2);
   failed.do_task("application", "on_additional_local_instance", properties);
   if (failed.m_tristateHandled.is_set_true()) return 8;
   delivered.do_task("application", "on_additional_local_instance", properties);
   if (delivered.m_tristateHandled.is_set_true()) return 13;
#if defined(WINDOWS)
   auto name = "Local\\exclusive-test-" + ::as_string(::GetCurrentProcessId());
   {
      ::parallelization::mutex first(app, false, name, nullptr);
      if (first.has_already_exists_flag()) return 9;
      ::parallelization::mutex second(app, false, name, nullptr);
      if (!second.has_already_exists_flag()) return 10;
   }
   ::parallelization::mutex reopened(app, false, name, nullptr);
   if (reopened.has_already_exists_flag()) return 11;
#endif
   app->m_pacmeuserinteractionMain.release();
   return 0;
}
