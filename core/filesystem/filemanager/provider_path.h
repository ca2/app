#pragma once

#include "special_folder.h"
#include "acme/filesystem/filesystem/listing.h"
#include "apex/filesystem/fs/data.h"

namespace filemanager
{
   inline bool is_provider_folder_path(const ::file::path & path)
   {
      ::string text(path);
      auto separator = text.find_index("://");
      if (separator < 0) return false;
      ::string scheme = text.left(separator);
      return special_folder_name_equal(scheme.c_str(), "google-drive")
         || special_folder_name_equal(scheme.c_str(), "dropbox")
         || special_folder_name_equal(scheme.c_str(), "dropbox-app")
         || special_folder_name_equal(scheme.c_str(), "onedrive");
   }

   // Presentation uses cached names only; navigation continues to use IDs.
   inline ::file::path provider_display_folder(::fs::data & filesystem, const ::file::path & canonical)
   {
      if (!is_provider_folder_path(canonical)) return canonical;
      ::string text(canonical);
      auto separator = text.find_index("://");
      ::file::path root(text.left(separator + 3));
      ::file::path current = canonical;
      string_array_base names;
      while (current != root)
      {
         ::file::image_info info;
         if (!filesystem.get_file_image_info(current, info) || info.m_strName.is_empty()
            || info.m_strName.contains("/") || info.m_strName.contains("\\")) return canonical;
         names.add(info.m_strName);
         auto parent = current.folder();
         if (parent == current || parent.is_empty()) return canonical;
         current = parent;
      }
      for (::collection::index i = names.get_upper_bound(); i >= 0; --i) root /= names[i];
      return root;
   }

   // Resolve names through real provider listings; keep provider IDs in the result.
   // Call on the browse worker, since both validation and enumeration may use the network.
   inline ::file::path resolve_provider_folder(::fs::data & filesystem, const ::file::path & requested)
   {
      if (!is_provider_folder_path(requested)) return requested;
      try { if (filesystem.is_dir(requested) > 0) return requested; }
      catch (...) {}

      ::string text(requested);
      auto separator = text.find_index("://");
      ::file::path current(text.left(separator + 3));
      string_array_base components;
      components.add_tokens(text.substr(separator + 3), "/", false);
      for (const auto & component : components)
      {
         auto candidate = current / component;
         try
         {
            if (filesystem.is_dir(candidate) > 0)
            {
               current = candidate;
               continue;
            }
         }
         catch (...) {}

         ::file::listing_base folders;
         folders.set_folder_listing(current);
         if (!filesystem.enumerate(folders))
            throw ::exception(error_failed, "Could not list the provider folder");
         ::file::path exact, insensitive;
         int exactCount = 0, insensitiveCount = 0;
         for (::collection::index i = 0; i < folders.size(); ++i)
         {
            auto name = i < folders.m_straTitle.size() && folders.m_straTitle[i].has_character()
               ? folders.m_straTitle[i] : folders[i].name();
            if (name == component) { exact = folders[i]; ++exactCount; }
            if (name.case_insensitive_order(component) == 0) { insensitive = folders[i]; ++insensitiveCount; }
         }
         if (exactCount == 1) current = exact;
         else if (exactCount == 0 && insensitiveCount == 1) current = insensitive;
         else if (exactCount > 1 || insensitiveCount > 1)
            throw ::exception(error_failed, "More than one folder has this name; use its provider ID.");
         else
            throw ::exception(error_not_found, "Provider folder not found: " + component);
      }
      return current;
   }
}
