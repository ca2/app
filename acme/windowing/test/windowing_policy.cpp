#include "../windowing_policy.h"
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
using namespace native_windowing_policy;
int main()
{
 assert(effective_override("on_screen", "x11", "wayland", "xcb") == "wayland");
 assert(effective_override("swap_chain", "x11", "wayland", "xcb") == "wayland");
 assert(effective_override("off_screen", "x11", "wayland", "xcb") == "xcb");
 assert(effective_override("", "x11", "wayland", "# unset\n") == "x11");
 assert(effective_override("on_screen", "x11", "bad_value", "xcb") == "bad_value");
 for (auto desktop : {"kde5", "kde6", "gtk3", "gtk4"})
 {
  for (auto output : {"", "off_screen", "invalid"}) {
   auto s=select(true,desktop,output,"",true,false);
   assert(s.toolkit==desktop && s.ambient==desktop && !s.missing_raw_session);
  }
  for (auto output : {"on_screen", "swap_chain", "  ON_SCREEN\n"}) {
   auto s=select(true,desktop,output,"",true,true);
   assert(s.toolkit=="wayland" && s.ambient=="wayland");
   s=select(true,desktop,output,"",false,true);
   assert(s.toolkit=="x11" && s.ambient=="x11");
   s=select(false,desktop,output,"wayland",true,false);
   assert(s.toolkit==desktop && s.ambient==desktop);
  }
 }
 for (auto value : {"xcb", " XCB ", "xcb_windowing", "windowing_xcb", "# saved\nwayland\nxcb # use XCB\n"}) {
  auto s=select(true,"kde6","on_screen",value,true,false);
  assert(s.toolkit=="xcb" && s.ambient=="x11" && !s.invalid_override);
 }
 auto s=select(true,"kde6","on_screen","x11",true,false);
 assert(s.toolkit=="x11");
 s=select(true,"kde6","off_screen","wayland",false,true);
 assert(s.toolkit=="wayland");
 s=select(true,"kde6","off_screen","wayland",false,true,false);
 assert(s.toolkit=="kde6");
 for (auto invalid : {"kde6", "gtk3", "toolkit_windowing", "window_manager", "../wayland"}) {
  s=select(true,"kde6","on_screen",invalid,true,false);
  assert(s.toolkit=="wayland" && s.invalid_override);
  s=select(true,"kde6","off_screen",invalid,true,false);
  assert(s.toolkit=="kde6" && s.invalid_override);
 }
 s=select(true,"kde6","on_screen","",false,false);
 assert(s.missing_raw_session);
 s=select(true,"kde6","on_screen","x11",false,false);
 assert(!s.missing_raw_session && s.toolkit=="x11");
 // Exercise real renames, collision preservation and idempotence in isolation.
 namespace fs=std::filesystem;
 const auto dir=fs::temp_directory_path()/("ca2-windowing-policy-"+std::to_string(
   std::chrono::steady_clock::now().time_since_epoch().count()));
 fs::create_directory(dir);
 std::ofstream(dir/"windowing.txt")<<"old override";
 std::error_code error;
 auto archived=deactivate_legacy(dir/"windowing.txt",error);
 assert(!error && archived==dir/"aaa_windowing.txt" && !fs::exists(dir/"windowing.txt"));
 assert(deactivate_legacy(dir/"windowing.txt",error).empty() && !error);
 std::ofstream(dir/"windowing.txt")<<"new override";
 archived=deactivate_legacy(dir/"windowing.txt",error);
 assert(!error && archived==dir/"aaa_windowing.1.txt");
 std::string original,replacement;
 std::getline(std::ifstream(dir/"aaa_windowing.txt"),original);
 std::getline(std::ifstream(archived),replacement);
 assert(original=="old override" && replacement=="new override");
 fs::remove_all(dir);
 std::cout<<"Windowing policy passed: defaults, Linux-only raw selection, session/forced backends, invalid values, XCB ambient and lossless legacy migration\n";
}
