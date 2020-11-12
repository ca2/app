//
//
//	   Main header for the file_watcher class. Declares all implementation
//	   classes to reduce compilation overhead.
//
//	   @author James Wynn
//	   @date 4/15/2009
//
//	   Copyright (c) 2009 James Wynn (james@jameswynn.com)
//
//	   Permission is hereby granted, free of charge, to any person obtaining a copy
//	   of this software and associated documentation files (the "Software"), to deal
//	   in the Software without restriction, including without limitation the rights
//	   to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
//	   copies of the Software, and to permit persons to whom the Software is
//	   furnished to do so, subject to the following conditions:
//
//
#include "framework.h"
#include "file_os_watcher.h"


namespace file
{


   /// Starts monitoring a directory.
   os_watch::os_watch()
   {


   }


   os_watch::~os_watch()
   {

      m_bRefresh = false;

      m_bStop = TRUE;

      CancelIo(m_hDirectory);

      step();

      if (!HasOverlappedIoCompleted(&m_overlapped))
      {

         SleepEx(5, TRUE);

      }

      if (m_overlapped.hEvent != INVALID_HANDLE_VALUE)
      {

         CloseHandle(m_overlapped.hEvent);

         m_overlapped.hEvent = INVALID_HANDLE_VALUE;

      }

      if (m_hDirectory != INVALID_HANDLE_VALUE)
      {

         CloseHandle(m_hDirectory);

         m_hDirectory = INVALID_HANDLE_VALUE;

      }

   }


   bool os_watch::open(const ::file::path & pathFolder, bool bRecursive)
   {

      if (!watch::open(pathFolder, bRecursive))
      {

         return false;

      }

      wstring wstrFolder(pathFolder);

      xxf_zero(m_overlapped);

      m_bRefresh = true;

      m_overlapped.hEvent = INVALID_HANDLE_VALUE;

      m_hDirectory = INVALID_HANDLE_VALUE;

      m_hDirectory = CreateFileW(wstrFolder, FILE_LIST_DIRECTORY,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                                 OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

      ::u32 dwLen = GetFinalPathNameByHandleW(m_hDirectory, nullptr, 0, 0);

      if (dwLen > 0)
      {

         wstring wstr;

         auto pwsz = wstr.get_string_buffer(dwLen + 1);

         if (GetFinalPathNameByHandleW(m_hDirectory, pwsz, dwLen + 1, 0) > 0)
         {

            CloseHandle(m_hDirectory);

            m_hDirectory = CreateFileW(pwsz, FILE_LIST_DIRECTORY,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                                       OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

         }


      }

      if (m_hDirectory == INVALID_HANDLE_VALUE)
      {

         return false;

      }

      m_overlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

      m_overlapped.Pointer = this;

      m_dwNotify = FILE_NOTIFY_CHANGE_CREATION
                   | FILE_NOTIFY_CHANGE_SIZE
                   | FILE_NOTIFY_CHANGE_FILE_NAME
                   | FILE_NOTIFY_CHANGE_LAST_WRITE;

      m_bRecursive = bRecursive;

      m_bStop = false;

      m_bRefresh = true;

      return true;

   }


   void CALLBACK os_watch::callback(::u32 dwErrorCode,::u32 dwNumberOfBytesTransfered,LPOVERLAPPED pOverlapped)

   {

      //TCHAR szFile[MAX_PATH];

      PFILE_NOTIFY_INFORMATION pNotify;

      os_watch * pwatch = (os_watch*)pOverlapped->Pointer;


      size_t offset = 0;

      if (dwNumberOfBytesTransfered == 0)
      {

         return;

      }

      if(dwErrorCode == ERROR_SUCCESS)
      {

         do
         {

            pNotify = (PFILE_NOTIFY_INFORMATION)&pwatch->m_buffer[offset];

            offset += pNotify->NextEntryOffset;

            wstring wstrFile(pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR));

            string strFile = wstrFile;

            ULONG ulAction = pNotify->Action;

            action action;

            action.m_pwatch = pwatch;

            action.m_id = pwatch->m_id;

            action.m_pathFolder = pwatch->m_pathFolder;

            action.m_pathFile = strFile;

            e_action eaction = action_none;

            switch (ulAction)
            {
            case FILE_ACTION_RENAMED_NEW_NAME:
            case FILE_ACTION_ADDED:
               eaction = action_add;
               break;
            case FILE_ACTION_RENAMED_OLD_NAME:
            case FILE_ACTION_REMOVED:
               eaction = action_delete;
               break;
            case FILE_ACTION_MODIFIED:
               eaction = action_modify;
               break;
            };

            action.m_eaction = eaction;

            pwatch->handle_action(&action);

         }
         while(pNotify->NextEntryOffset != 0);

      }

      if(!pwatch->m_bStop)
      {

         pwatch->m_bRefresh = true;

      }

   }


   bool os_watch::step()
   {

      return ReadDirectoryChangesW(
             m_hDirectory,
             m_buffer,
             sizeof(m_buffer),
             m_bRecursive ? TRUE : FALSE,
             m_dwNotify,
             nullptr,
             &m_overlapped,
             m_bStop ? NULL : &os_watch::callback) != 0;

   }


   os_watcher::os_watcher()
   {

   }


   os_watcher::~os_watcher()
   {

      m_watchmap.clear();

   }


   bool os_watcher::step()
   {

      MsgWaitForMultipleObjectsEx(0,nullptr,500,QS_ALLINPUT,MWMO_ALERTABLE);

      if (!::thread_get_run())
      {

         return false;

      }

      if (!watcher::step())
      {

         return false;

      }

      return true;

   }


} // namespace file




