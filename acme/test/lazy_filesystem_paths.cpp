// Standalone regression; link against the matching acme library.
// Define TEST_MACOS_DIRECTORY_CONTEXT and link acme_macos to exercise its override.
#include "acme/platform.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform_platform.h"
#include "acme/platform/system.h"
#include "acme/platform/application.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#if defined(TEST_MACOS_DIRECTORY_CONTEXT)
#include "acme_macos/_.h"
#include "acme_macos/directory_context.h"
#endif
#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>

class test_directory_system : public ::directory_system
{
public:
   ::file::path home() override { return "/test/home"; }
   ::file::path roaming() override { return "/test/roaming"; }
   ::string appid() override { return "test/app"; }
};

class test_file_context : public ::file_context
{
public:
   int m_attempts = 0;
   void calculate_main_resource_memory() override
   {
      if (++m_attempts == 1)
      {
         throw 1;
      }
      m_memoryMainResource.set_size(1);
   }
};

static void require(bool condition, const char * message)
{
   if (!condition)
   {
      ::std::fprintf(stderr, "%s\n", message);
      ::std::exit(1);
   }
}

int main()
{
   ::acme::acme runtime;
   ::platform::platform runtimePlatform;
   ::platform::system system;
   runtimePlatform.m_psystem = &system;
   ::platform::application application;
   application.m_papplication = &application;
   system.m_papplication = &application;
#if defined(TEST_MACOS_DIRECTORY_CONTEXT)
   ::pointer<test_directory_system> platformDirectory(allocate_t{});
   system.m_pdirectorysystem = platformDirectory;
   system.m_bFileSystemComponentsInitialized = true;
   application.m_strAppId = "test/app";
   ::acme_macos::directory_context directory;
   directory.m_papplication = &application;
   require(platformDirectory->m_pathAppData.is_empty(), "platform path unexpectedly eager");
   require(directory.appdata() == "/test/roaming/test/app", "macOS default appdata empty");
   require(directory.appdata("other/app") == "/test/roaming/other/app", "macOS explicit appdata");
   require(platformDirectory->m_pathAppData.is_empty(), "macOS read the legacy cache");
#endif

   test_directory_system first;
   test_directory_system second;

   // The base and per-application caches must be independent in either order.
   require(first.app_data_path() == "/test/home/application", "default base path");
   require(first.application_app_data_path() == "/test/roaming/test/app", "app path after base path");
   require(first.app_data_path() == "/test/home/application", "base cache overwritten");
   require(second.application_app_data_path() == "/test/roaming/test/app", "initial app path");
   require(second.app_data_path() == "/test/home/application", "base path after app path");
   require(second.appdata() == "/test/roaming/test/app", "appdata alias cache overwritten");

   // Early lookups must not freeze a later application id or app_folder value.
   require(first.application_app_data_path("other/app") == "/test/roaming/other/app", "different app id");
   system.payload("app_folder") = "/test/override";
   require(first.application_app_data_path() == "/test/override", "late app_folder override");
   require(first.app_data_path() == "/test/override", "late base path override");
   system.payload("app_folder") = "";
   require(first.application_app_data_path() == "/test/roaming/test/app", "empty override fallback");

   ::std::atomic<bool> correct{true};
   ::std::vector<::std::thread> readers;
   for (int i = 0; i < 8; ++i)
   {
      readers.emplace_back([&]
      {
         for (int j = 0; j < 100; ++j)
         {
            if (first.app_data_path() != "/test/home/application"
               || first.application_app_data_path() != "/test/roaming/test/app")
            {
               correct = false;
            }
         }
      });
   }
   for (auto & reader : readers) reader.join();
   require(correct, "concurrent path cache reads");

   test_file_context file;
   require(!file.m_bMainResourceMemoryCalculated, "resource cache initialized prematurely");
   try { file.get_main_resource_block(); } catch (int) {}
   require(!file.m_bMainResourceMemoryCalculated, "failed resource calculation cached");
   file.get_main_resource_block();
   file.get_main_resource_block();
   require(file.m_attempts == 2 && file.m_bMainResourceMemoryCalculated, "resource calculation retry/cache");

   ::std::puts("Lazy filesystem path regressions passed");
   ::std::fflush(stdout);
   ::std::_Exit(0);
}
