#include "acme/platform.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/platform/node.h"
#include "acme/windowing/windowing.h"
#include "acme/windowing/file_icon_provider.h"

class desktop_icons : public ::acme::windowing::windowing,
   public ::acme::windowing::file_icon_provider
{
public:
   ::string file_icon_path(const ::scoped_string & path, ::i32 size) override
   {
      return path == "/tmp/folder" && size == 16 ? "folder-icon.png" : "type-icon.png";
   }
};

int main()
{
   ::acme::acme runtime;
   ::platform::system system;
   ::platform::application app;
   app.m_papplication = &app;
   app.m_psystem = &system;
   ::platform::node node;
   node.initialize(&app);
   system.m_pacmewindowing = ::pointer<desktop_icons>(allocate_t{});
   if (node.get_file_icon_path("/tmp/folder", 16) != "folder-icon.png") return 1;
   if (node.get_file_icon_path("file.pdf", 48) != "type-icon.png") return 2;
   system.m_pacmewindowing = ::pointer<::acme::windowing::windowing>(allocate_t{});
   if (node.get_file_icon_path("/tmp/folder", 16).has_character()) return 3;
   system.m_pacmewindowing.release();
}
