#include "core/filesystem/filemanager/special_folder.h"
#include <algorithm>
#include <cassert>
#include <string>
#include <string_view>
#include <vector>

int main()
{
   using filemanager::special_folder_icon;
   for (auto provider : {"google-drive", "dropbox", "dropbox-app", "onedrive"})
   {
      std::string path = std::string(provider) + "://opaque-id";
      assert(std::string_view(special_folder_icon(path, "Pictures")) == "image://");
      assert(std::string_view(special_folder_icon(path, "PHOTOS")) == "image://");
      assert(std::string_view(special_folder_icon(path, "Image")) == "image://");
      assert(std::string_view(special_folder_icon(path, "Documents")) == "document://");
      assert(std::string_view(special_folder_icon(path, "Videos")) == "video://");
      assert(std::string_view(special_folder_icon(path, "Musical")) == "music://");
      assert(std::string_view(special_folder_icon(path, "Downloads")) == "download://");
      assert(std::string_view(special_folder_icon(path, "Desktop")) == "desktop://");
      assert(!special_folder_icon(path + "/nested-id", "Pictures"));
      assert(!special_folder_icon(std::string(provider) + "://", "Pictures"));
      assert(!special_folder_icon(path, "Holiday Pictures"));
   }
   assert(!special_folder_icon("/home/me/Pictures", "Pictures"));
   assert(!special_folder_icon("image://Pictures", "Pictures"));
   assert(!special_folder_icon("unknown://Pictures", "Pictures"));
   std::vector<std::string_view> names = {"Zoo", "Pictures", "Archive", "Music", "Documents", "Image"};
   std::sort(names.begin(), names.end(), [](auto a, auto b)
   {
      bool specialA = special_folder_icon("google-drive://id", a);
      bool specialB = special_folder_icon("google-drive://id", b);
      return specialA != specialB ? specialA : a < b;
   });
   assert((names == std::vector<std::string_view>{"Documents", "Image", "Music", "Pictures", "Archive", "Zoo"}));
}
