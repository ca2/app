#include "framework.h"
//#include "universal_windows.h"


//namespace universal_windows
//{
//
//
//   folder_watch::folder_watch(::particle * pparticle) :
//      ::matter(pparticle),
//      ::thread(pparticle)
//   {
//
//   }
//
//
//   bool folder_watch::watch(const ::file::path & path)
//   {
//      if(!::file::folder_watch::watch(pszPath))
//         return false;
//
//      if(!begin())
//         return false;
//
//      return true;
//   }
//
//
//   void folder_watch::run() // thread procedure
//   {
//
//#ifdef WINDOWS_DESKTOP
//      HANDLE hDirectory = ::CreateFileW(utf8_to_unicode(m_strPath),
//                                        FILE_LIST_DIRECTORY,
//                                        FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
//                                        nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
//
//      if(INVALID_HANDLE_VALUE == hDirectory)
//      {
//         ::u32 dwError = ::get_last_error();
//         // handle error (see this FAQ)
//         return dwError;
//      }
//
//      ::u32 dwBytesReturned = 0;
//      const ::u32 dwBuffLength = 4096;
//      ::u8 buffer[dwBuffLength];
//      WCHAR wchFileName[dwBuffLength];
//
//
//      while(::ReadDirectoryChangesW(hDirectory, buffer, dwBuffLength, true,
//                                    FILE_NOTIFY_CHANGE_FILE_NAME |
//                                    FILE_NOTIFY_CHANGE_LAST_WRITE |
//                                    FILE_NOTIFY_CHANGE_CREATION, &dwBytesReturned,
//                                    nullptr, nullptr))
//      {
//         ::u32 dwNextEntryOffset = 0;
//         PFILE_NOTIFY_INFORMATION pfni = nullptr;
//         do
//         {
//            pfni = (PFILE_NOTIFY_INFORMATION)(buffer + dwNextEntryOffset);
//            ::memory_copy(wchFileName, pfni->FileName, pfni->FileNameLength);
//            wchFileName[pfni->FileNameLength / sizeof(WCHAR)] = L'\0';
//            e_action eaction = translate_os_action(pfni->Action);
//            //if(eaction != action_unexpected)
//            {
//               on_file_action(eaction, unicode_to_utf8(wchFileName));
//            }
//            dwNextEntryOffset += pfni->NextEntryOffset; // next please!
//         }
//         while(pfni->NextEntryOffset != 0);
//      }
//      ::CloseHandle(hDirectory);
//      return 0;
//#else
//
//      throw ::exception(todo);
//
//#endif
//   }
//
//   folder_watch::e_action folder_watch::translate_os_action(int iAction)
//   {
//      switch(iAction)
//      {
//      case FILE_ACTION_ADDED:
//         // The file was added to the directory.
//         return action_added;
//      case FILE_ACTION_REMOVED:
//         // The file was erased from the directory.
//         return action_erased;
//      case FILE_ACTION_RENAMED_OLD_NAME:
//         // The file was renamed and this is the old name.
//         return action_renamed_old_name;
//      case FILE_ACTION_RENAMED_NEW_NAME:
//         // The file was renamed and this is the memory_new name.
//         return action_renamed_new_name;
//      // ...
//      default:
//         return action_unexpected;
//      }
//   }
//
//
//} // namespace universal_windows
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
