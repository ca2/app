// Standalone Windows integration test; link against the matching acme import library.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

__declspec(dllimport) void ca2_enable_standard_trace_file(bool);
__declspec(dllimport) bool ca2_set_standard_trace_path(const wchar_t *);
__declspec(dllimport) void ca2_write_standard_trace_file(const char *, const wchar_t *);

static void require(bool condition, const char *message)
{
   if (!condition) throw std::runtime_error(message);
}

static std::string read_file(const std::wstring &path)
{
   std::ifstream file(std::filesystem::path(path), std::ios::binary);
   require(file.is_open(), "cannot read test log");
   return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

struct test_logs
{
   std::wstring first, second, moved;
   test_logs()
   {
      wchar_t folder[MAX_PATH], path[MAX_PATH];
      require(GetTempPathW(MAX_PATH, folder) > 0, "temporary folder unavailable");
      require(GetTempFileNameW(folder, L"ca2", 0, path) != 0, "temporary file unavailable");
      first = path;
      second = first + L".second";
      moved = first + L".moved";
   }
   ~test_logs()
   {
      ca2_enable_standard_trace_file(false);
      DeleteFileW(first.c_str());
      DeleteFileW(second.c_str());
      DeleteFileW(moved.c_str());
   }
};

int main()
{
   try
   {
      test_logs logs;
      ca2_enable_standard_trace_file(true);
      require(ca2_set_standard_trace_path(logs.first.c_str()), "set first path failed");
      require(!MoveFileW(logs.first.c_str(), logs.moved.c_str())
         && GetLastError() == ERROR_SHARING_VIOLATION, "trace handle is not retained");

      SetLastError(1234);
      errno = ERANGE;
      ca2_write_standard_trace_file("sentinel", logs.first.c_str());
      require(GetLastError() == 1234 && errno == ERANGE, "caller error state changed");

      DWORD handlesBefore = 0, handlesAfter = 0;
      require(GetProcessHandleCount(GetCurrentProcess(), &handlesBefore), "handle count failed");
      for (int i = 0; i < 100; ++i)
         ca2_write_standard_trace_file("serial", logs.first.c_str());
      require(GetProcessHandleCount(GetCurrentProcess(), &handlesAfter), "handle count failed");
      require(handlesBefore == handlesAfter, "serial writes leak handles");

      std::vector<std::thread> writers;
      for (int t = 0; t < 4; ++t)
         writers.emplace_back([&, t]()
         {
            for (int i = 0; i < 20; ++i)
            {
               auto text = "worker-" + std::to_string(t) + "-" + std::to_string(i);
               ca2_write_standard_trace_file(text.c_str(), logs.first.c_str());
            }
         });
      for (auto &writer : writers) writer.join();
      const std::string longRecord(70000, 'X');
      ca2_write_standard_trace_file(longRecord.c_str(), logs.first.c_str());
      auto contents = read_file(logs.first);
      require(contents.find(longRecord + "\r\n") != std::string::npos, "long record incomplete");
      for (int t = 0; t < 4; ++t)
         for (int i = 0; i < 20; ++i)
            require(contents.find("\r\nworker-" + std::to_string(t) + "-"
               + std::to_string(i) + "\r\n") != std::string::npos, "concurrent record incomplete");

      require(ca2_set_standard_trace_path(logs.second.c_str()), "path change failed");
      require(MoveFileW(logs.first.c_str(), logs.moved.c_str()), "old handle not closed");
      ca2_enable_standard_trace_file(false);
      require(MoveFileW(logs.second.c_str(), logs.first.c_str()), "disable did not close handle");
      contents = read_file(logs.first);
      ca2_write_standard_trace_file("disabled", logs.first.c_str());
      require(read_file(logs.first) == contents, "disabled tracing wrote a record");
      ca2_enable_standard_trace_file(true);
      ca2_write_standard_trace_file("re-enabled", logs.first.c_str());
      require(read_file(logs.first) == contents + "re-enabled\r\n", "re-enable did not append");

      const auto invalidPath = logs.first + L"\\missing.log";
      SetLastError(4321);
      errno = EDOM;
      ca2_write_standard_trace_file("cannot open", invalidPath.c_str());
      require(GetLastError() == 4321 && errno == EDOM, "failed open changed caller errors");
      ca2_write_standard_trace_file("recovered", logs.first.c_str());
      require(read_file(logs.first).find("recovered\r\n") != std::string::npos, "open retry failed");
      puts("PASS: persistent handle, cleanup, concurrency, append, retry, and caller errors");
      return 0;
   }
   catch (const std::exception &error)
   {
      fprintf(stderr, "FAIL: %s\n", error.what());
      return 1;
   }
}
