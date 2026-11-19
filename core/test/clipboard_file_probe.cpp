#include "core/platform.h"
#include "aura/user/user/copydesk.h"
#include "acme/platform/system.h"
namespace
{
   class clipboard : public ::user::copydesk
   {
   public:
      bool _has_filea() override { return false; }
      bool _has_plain_text() override { return true; }
      bool _get_plain_text(::string & text) override { text = "ordinary clipboard text"; return true; }
      bool string_to_filea(::file::path_array_base *, const ::scoped_string &) override { return false; }
   };
}
int main()
{
   ::platform::system runtime;
   ::pointer<clipboard> probe(allocate_t{});
   if (probe->has_filea()) return 1;
   ::pointer<::user::copydesk> parser(allocate_t{});
   ::string backtrace = "#8  0x00007ffff008fc54 in pure_procedure<user::tree::on_message_create(message::message*)::<lambda()>::<lambda()> >::operator()(void) (this=warning: RTTI symbol not found for class '";
   for (int i = 0; i < 8; ++i) backtrace += "long debugger template name ";
   backtrace += "\nstatus = genericFileError\nordinary clipboard text";
   try
   {
      if (parser->string_to_filea(nullptr, backtrace)) return 2;
      ::file::path_array_base files;
      if (parser->string_to_filea(&files, backtrace) || files.has_element()) return 3;
   }
   catch (...) { return 4; }
   probe->destroy();
   parser->destroy();
   return 0;
}
