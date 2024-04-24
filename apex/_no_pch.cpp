//#include <windows.h>
//#include <Shlobj.h>
//#include <stdint.h>
//
//
//LPITEMIDLIST GetItemIdListFromPath(const wchar_t * pwsz)
//{
//
//   LPITEMIDLIST p = nullptr;
//
//   LPSHELLFOLDER pShellFolder = NULL;
//
//   HRESULT         hr;
//
//   ULONG         chUsed;
//
//   // Get desktop IShellFolder interface
//
//   if (SHGetDesktopFolder(&pShellFolder) != NOERROR)
//   {
//
//      return nullptr;     // failed
//
//   }
//
//
//   // convert the path to an ITEMIDLIST
//
//   hr = pShellFolder->ParseDisplayName(
//
//      NULL,           // owner window
//
//      NULL,           // reserved (must be NULL)
//
//      (LPWSTR) pwsz,       // folder name
//
//      &chUsed,    // number of chars parsed
//
//      &p,   // ITEMIDLIST
//
//      NULL            // attributes (can be NULL)
//
//   );
//
//
//   if (FAILED(hr))
//
//   {
//
//      pShellFolder->Release();
//
//      
//      return nullptr;
//
//   }
//
//
//   pShellFolder->Release();
//
//   return p;
//
//}
//
//
//void shell_notify_folder_change(const wchar_t * pwsz)
//{
//
//   auto p = GetItemIdListFromPath(pwsz);
//
//   if (!p)
//   {
//
//      return;
//
//   }
//
//   ::SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, p, nullptr);
//
//   ::CoTaskMemFree(p);
//
//}
//
//
//void shell_notify_item_change(const wchar_t * pwsz)
//{
//
//   auto p = GetItemIdListFromPath(pwsz);
//
//   if (!p)
//   {
//
//      return;
//
//   }
//
//   ::SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, p, nullptr);
//
//   ::CoTaskMemFree(p);
//
//}
//
//
//void shell_notify_assoc_change()
//{
//
//   ::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
//
//}
//
//
//
