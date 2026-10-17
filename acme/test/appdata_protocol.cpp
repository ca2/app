// Standalone resolver regression; link against the matching acme import library.
// No application startup, cloud provider, browser, file IO or desktop changes.
#include "acme/platform.h"
#include "acme/platform/context.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform_platform.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include <cstdio>
#include <cstdlib>

class local_directory : public ::directory_context
{
public:
   ::file::path appdata(const ::scoped_string &) override
   {
      return "C:/local-appdata/app-core/ambient";
   }
};

class resolver_context : public ::platform::context
{
public:
   local_directory m_directory;
   ::directory_context * directory() override { return &m_directory; }
};

int main()
{
   ::acme::acme runtime;
   ::platform::platform runtimePlatform;
   resolver_context context;
   struct example { const char * uri; const char * expected; } examples[] = {
      {"appdata://", "C:/local-appdata/app-core/ambient"},
      {"appdata:/windowsxp/ambient_lite.theme", "C:/local-appdata/app-core/ambient/windowsxp/ambient_lite.theme"},
      {"appdata://windowsxp/ambient_dark.theme", "C:/local-appdata/app-core/ambient/windowsxp/ambient_dark.theme"},
      {"APPDATA://windowsxp/backup", "C:/local-appdata/app-core/ambient/windowsxp/backup"}
   };
   for (auto & example : examples)
   {
      auto resolved = context.__defer_process_path(example.uri);
      if (resolved != ::file::path(example.expected))
      {
         std::fprintf(stderr, "Resolver failed for %s: %s\n", example.uri, resolved.c_str());
         return 1;
      }
   }
   ::file::path required("appdata://windowsxp/ambient_lite.theme");
   required.flags() += ::file::e_flag_required;
   if (context.__defer_process_path(required).flags().is_clear(::file::e_flag_required))
   {
      std::fputs("Resolver dropped path flags\n", stderr);
      return 1;
   }
   std::puts("Local appdata protocol resolver regressions passed");
   std::fflush(stdout);
   // This isolated test bootstraps memory/factories, not the application's
   // lifecycle. Let the OS reclaim it instead of running full-app teardown.
   std::_Exit(0);
}
