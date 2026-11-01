#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace aura::graphics_configuration
{
   inline std::string normalize(std::string value, const std::string & prefix = {})
   {
      auto first = value.find_first_not_of(" \t\r\n");
      if (first == std::string::npos) return {};
      value = value.substr(first, value.find_last_not_of(" \t\r\n") - first + 1);
      std::transform(value.begin(), value.end(), value.begin(),
         [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
      if (!prefix.empty() && value.compare(0, prefix.size(), prefix) == 0)
         value.erase(0, prefix.size());
      return value;
   }

   // An application override wins over its file setting; otherwise retain the
   // ordinary application defaults. These rules are also used by Options.
   inline std::string gpu_api(const std::string & overrideValue, const std::string & setting)
   {
      auto value = normalize(overrideValue, "gpu_");
      if (value.empty()) value = normalize(setting, "gpu_");
      if (value == "opengl" || value == "vulkan" || value == "directx11"
         || value == "directx12" || value == "metal") return value;
      return "opengl";
   }

   inline std::string output(const std::string & overrideValue, const std::string & setting)
   {
      auto value = normalize(overrideValue);
      if (value.empty()) value = normalize(setting);
      return value == "on_screen" || value == "swap_chain" ? "on_screen" : "off_screen";
   }

   inline std::vector<std::string> draw2d_apis(const std::string & gpu,
      bool offscreen, bool windows, bool apple)
   {
      std::vector<std::string> result{gpu};
      if (gpu == "opengl") result.push_back("nanovg");
      else if (gpu == "vulkan") result.push_back("vkvg");
      else if (windows && gpu == "directx11") result.push_back("direct2d_for_directx11");
      else if (windows && gpu == "directx12") result.push_back("direct2d_for_directx12");
      if (offscreen)
      {
         if (windows) { result.push_back("gdiplus"); result.push_back("direct2d"); }
         else result.push_back(apple ? "quartz2d" : "cairo");
      }
      return result;
   }

   inline std::string draw2d_api(const std::string & setting,
      const std::vector<std::string> & available)
   {
      auto value = normalize(setting, "draw2d_");
      if (std::find(available.begin(), available.end(), value) != available.end()) return value;
      return available.empty() ? std::string{} : available.front();
   }
}
