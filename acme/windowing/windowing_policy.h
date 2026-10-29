#pragma once
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <string>
#include <string_view>
#include <system_error>
#include <mutex>

namespace native_windowing_policy
{
   inline std::string trim_lower(std::string_view text)
   {
      const auto first = text.find_first_not_of(" \t\r\n");
      if (first == text.npos) return {};
      const auto last = text.find_last_not_of(" \t\r\n");
      std::string value(text.substr(first, last - first + 1));
      std::transform(value.begin(), value.end(), value.begin(),
         [](unsigned char c) { return (char)std::tolower(c); });
      return value;
   }

   inline std::string forced_value(std::string_view text)
   {
      std::string result;
      while (!text.empty())
      {
         const auto end = text.find('\n');
         const auto line = text.substr(0, end);
         const auto value = trim_lower(line.substr(0, line.find('#')));
         if (!value.empty()) result = value;
         if (end == text.npos) break;
         text.remove_prefix(end + 1);
      }
      return result;
   }

   struct selection
   {
      std::string toolkit;
      std::string ambient;
      bool invalid_override = false;
      bool missing_raw_session = false;
   };

   inline std::string effective_override(std::string_view output, std::string_view general,
      std::string_view onScreen, std::string_view offScreen)
   {
      const auto mode = trim_lower(output);
      const auto specific = forced_value(mode == "on_screen" || mode == "swap_chain" ? onScreen : offScreen);
      return specific.empty() ? forced_value(general) : specific;
   }

   inline selection select(bool onLinux, std::string_view desktop,
      std::string_view output, std::string_view forced, bool wayland, bool x11,
      bool allowForcedOffscreen = true)
   {
      selection result{std::string(desktop), std::string(desktop)};
      if (!onLinux) return result;
      const auto mode = trim_lower(output);
      const bool onScreen = mode == "on_screen" || mode == "swap_chain";
      auto raw = forced_value(forced);
      const bool specified = !raw.empty();
      if (raw.starts_with("windowing_")) raw.erase(0, 10);
      if (raw.ends_with("_windowing")) raw.erase(raw.size() - 10);
      const bool valid = raw == "wayland" || raw == "x11" || raw == "xcb";
      result.invalid_override = specified && !valid;
      if (valid && (onScreen || allowForcedOffscreen))
      {
         result.toolkit = raw;
         // XCB has windowing/Acme/nano factories but shares the X11 ambient.
         result.ambient = raw == "xcb" ? "x11" : raw;
      }
      else if (onScreen)
      {
         if (wayland) result.toolkit = result.ambient = "wayland";
         else if (x11) result.toolkit = result.ambient = "x11";
         else result.missing_raw_session = true;
      }
      return result;
   }

   // Preserve existing backups. Subsequent legacy files get a numbered name;
   // none of these names are read as active configuration.
   inline std::filesystem::path deactivate_legacy(const std::filesystem::path & source,
      std::error_code & error)
   {
      static std::mutex migrationMutex;
      std::lock_guard<std::mutex> lock(migrationMutex);
      error.clear();
      if (!std::filesystem::exists(source, error) || error) return {};
      auto destination = source.parent_path() / "aaa_windowing.txt";
      unsigned suffix = 0;
      while (std::filesystem::exists(destination, error) && !error)
         destination = source.parent_path() / ("aaa_windowing." + std::to_string(++suffix) + ".txt");
      if (error) return {};
      std::filesystem::rename(source, destination, error);
      if (error) return {};
      return destination;
   }
}
