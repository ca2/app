#include "framework.h"
//#include "acme/primitive/primitive/function.h"
//#include "acme/exception/exception.h"
#include "acme/primitive/primitive/memory.h"

#include "acme/_operating_system.h"


#include <vector>

void __wide_append(memory & memory, const ::scoped_string & scopedstr);
void __wide_append_null(memory & memory);


#if defined(_WIN32)
#  ifndef NOMINMAX
#  define NOMINMAX 1
#  endif
//#  include <windows.h>
#include <commdlg.h>
#endif

#if !defined(__APPLE__)


void file_dialog_from_platform(
   void * poswindow,
   const ::array < ::pair < ::string, ::string > > & filetypesParam,
   const ::function < void(const ::file::path_array &) > & function,
   bool save, bool multiple)
{

   if (save && multiple)
   {

      throw ::exception(error_bad_argument, "save and multiple must not both be true.");

   }
   auto filetypes = filetypesParam;

   main_asynchronous([poswindow, filetypes, function, save, multiple]
      {


         ::file::path_array patha;


#if defined(EMSCRIPTEN)

         throw std::runtime_error("Opening files is not supported when NanoGUI is compiled via Emscripten");

#elif defined(WINDOWS_DESKTOP)

         //array <  wstring_pair> wfiletypes;

         //for (auto & p : filetypes)
         //{
         //   wfiletypes.add(wstring_pair( wstring(p.first.c_str()), wstring(p.second.c_str()) ));

         //}

         OPENFILENAME ofn;
         ZeroMemory(&ofn, sizeof(OPENFILENAME));
         ofn.lStructSize = sizeof(OPENFILENAME);
         memory tmp1;
         static const int FILE_DIALOG_MAX_BUFFER = 16384;
         tmp1.set_size(FILE_DIALOG_MAX_BUFFER);
         tmp1.zero();
         wchar_t * tmp = (wchar_t *)tmp1.data();
         ofn.lpstrFile = tmp;
         //;; ZeroMemory(tmp, FILE_DIALOG_MAX_BUFFER);
         ofn.nMaxFile = (DWORD) tmp1.size();
         ofn.nFilterIndex = 1;

         memory filter;

         if (!save && filetypes.size() > 1) {
            __wide_append(filter, "Supported file types (");
            for (size_t i = 0; i < filetypes.size(); ++i) {
               __wide_append(filter, "*.");
               __wide_append(filter, filetypes[i].element1().c_str());
               if (i + 1 < filetypes.size())
                  __wide_append(filter, ";");
            }
            __wide_append(filter, ")");
            __wide_append_null(filter);
            for (size_t i = 0; i < filetypes.size(); ++i) {
               __wide_append(filter, "*.");
               __wide_append(filter, filetypes[i].element1().c_str());
               if (i + 1 < filetypes.size())
                  __wide_append(filter, ";");
            }
            __wide_append_null(filter);
         }
         for (auto pair : filetypes) {
            __wide_append(filter, pair.element2().c_str());
            __wide_append(filter, " (*.");
            __wide_append(filter, pair.element1().c_str());
            __wide_append(filter, ")");
            __wide_append_null(filter);
            __wide_append(filter, "*.");
            __wide_append(filter, pair.element1().c_str());
            __wide_append_null(filter);
         }
         __wide_append_null(filter);
         ofn.lpstrFilter = (LPWSTR)filter.data();

         if (save) {
            ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
            if (GetSaveFileNameW(&ofn) == FALSE)
            {
               function({});

               return;

            }
         }
         else {
            ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            if (multiple)
               ofn.Flags |= OFN_ALLOWMULTISELECT;
            if (GetOpenFileNameW(&ofn) == FALSE)
            {
               function({});
               return;
            }
         }

         size_t i = 0;
         while (*tmp != L'\0') {

            wstring wstr(tmp);
            patha.add(string(wstr).c_str());

            tmp += wcslen(tmp) + 1;
         }

         //if (result.size() > 1) {
         //   for (i = 1; i < result.size(); ++i) {
         //      result[i] = result[0] + "\\" + result[i];
         //   }
         //   result.erase(begin(result));
         //}

#elif defined(LINUX)


         throw ::exception(todo);

//         static const int FILE_DIALOG_MAX_BUFFER = 16384;
//
//         char buffer[FILE_DIALOG_MAX_BUFFER];
//
//         buffer[0] = '\0';
//
//         ::string cmd = "zenity --file-selection ";
//         // The safest separator for multiple selected paths is /, since / can never occur
//         // in file names. Only where two paths are concatenated will there be two / following
//         // each other.
//         if (multiple)
//            cmd += "--multiple --separator=\"/\" ";
//         if (save)
//            cmd += "--save ";
//         cmd += "--file-filter=\"";
//         for (auto pair : filetypes)
//            cmd += "\"*." + pair.first + "\" ";
//         cmd += "\"";
//         FILE * output = popen(cmd.c_str(), "r");
//         if (output == nullptr)
//            throw std::runtime_error("popen() failed -- could not launch zenity!");
//         while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
//            ;
//         pclose(output);
//         ::string paths(buffer);
//         paths.erase(std::remove(paths.begin(), paths.end(), '\n'), paths.end());
//
//         while (!paths.empty()) {
//            size_t end = paths.find("//");
//            if (end == ::string::npos) {
//               result.emplace_back(paths);
//               paths = "";
//            }
//            else {
//               result.emplace_back(paths.substr(0, end));
//               paths = paths.substr(end + 1);
//            }
//         }

#endif

         function(patha);

      });

}

#endif
