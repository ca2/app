#pragma once

#include <string_view>

namespace filemanager
{
   // Presentation only: never replace a provider path with the returned icon path.
   inline bool special_folder_name_equal(std::string_view a, std::string_view b)
   {
      if (a.size() != b.size()) return false;
      for (size_t i = 0; i < a.size(); ++i)
      {
         auto lower = [](char c) { return c >= 'A' && c <= 'Z' ? char(c + ('a' - 'A')) : c; };
         if (lower(a[i]) != lower(b[i])) return false;
      }
      return true;
   }

   inline const char * special_folder_icon(std::string_view path, std::string_view name)
   {
      // Only direct children of supported provider roots receive special treatment.
      auto separator = path.find("://");
      if (separator == std::string_view::npos) return nullptr;
      auto scheme = path.substr(0, separator);
      if (!special_folder_name_equal(scheme, "google-drive")
         && !special_folder_name_equal(scheme, "dropbox")
         && !special_folder_name_equal(scheme, "dropbox-app")
         && !special_folder_name_equal(scheme, "onedrive")) return nullptr;
      auto child = path.substr(separator + 3);
      if (child.empty() || child.find_first_of("/\\") != std::string_view::npos) return nullptr;

      if (special_folder_name_equal(name, "image") || special_folder_name_equal(name, "images")
         || special_folder_name_equal(name, "photo") || special_folder_name_equal(name, "photos")
         || special_folder_name_equal(name, "picture") || special_folder_name_equal(name, "pictures")) return "image://";
      if (special_folder_name_equal(name, "video") || special_folder_name_equal(name, "videos")) return "video://";
      if (special_folder_name_equal(name, "document") || special_folder_name_equal(name, "documents")) return "document://";
      if (special_folder_name_equal(name, "music") || special_folder_name_equal(name, "musical")) return "music://";
      if (special_folder_name_equal(name, "download") || special_folder_name_equal(name, "downloads")) return "download://";
      if (special_folder_name_equal(name, "desktop")) return "desktop://";
      return nullptr;
   }
}
