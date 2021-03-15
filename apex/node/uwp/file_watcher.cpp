/**
	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
#include "framework.h"
#include "_uwp.h"




namespace file
{

   /// Internal watch data
   ref class watch_ref sealed
   {
   internal:

      watch *                                                        m_pwatch;

   public:

      property Windows::Storage::StorageFolder ^                     m_folder;
      property Windows::Storage::Search::StorageItemQueryResult ^    m_queryresult;
      property Windows::Foundation::EventRegistrationToken           m_evtoken;
      property bool                                                  m_bRecursive;
      property bool                                                  m_bOwn;

      static watch_ref ^ create_watch(String ^ strDirectory, bool bRecursive);

      void ContentsChanged(::Windows::Storage::Search::IStorageQueryResultBase ^ r, ::Object ^ o)
      {

         //::Windows::Storage::Search::StorageItemQueryResult^ results = (::Windows::Storage::Search::StorageItemQueryResult^) r;

         //if (results != nullptr)
         //{

         //   auto items = ::wait(results->GetItemsAsync());

         //   for (index i = 0; i < items->Size; i++)
         //   {

         //auto item = items->GetAt(i);

         action action;

         action.m_pwatch = m_pwatch;

         action.m_pathFolder = m_pwatch->m_pathFolder;

         //psubject->m_ulOsAction = -1;

         //m_pwatch->handle_action(m_pwatch->m_id, m_pwatch->m_strFolder,
           //    "", (::file_watcher::e_action) -1);

         //}
         m_pwatch->handle_action(&action);


         //}


      }

   };


   #pragma region Internal Functions

// forward decl
   bool RefreshWatch(watch_ref ^ pWatch, bool _clear = false);

/// Unpacks events and passes them to a user defined callback.
   /*void CALLBACK WatchCallback(::u32 dwErrorCode, ::u32 dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
   {
   	TCHAR szFile[MAX_PATH];
   	PFILE_NOTIFY_INFORMATION pNotify;
   	watch_struct* pWatch = (watch_struct*) lpOverlapped;
   	size_t offset = 0;

   	if(dwNumberOfBytesTransfered == 0)
   		return;

   	if (dwErrorCode == ERROR_SUCCESS)
   	{
   		do
   		{
   			pNotify = (PFILE_NOTIFY_INFORMATION) &pWatch->m_buffer[offset];
   			offset += pNotify->NextEntryOffset;

   #			if defined(UNICODE)
   			{
   				lstrcpynW(szFile, pNotify->FileName,
   					minimum(MAX_PATH, pNotify->FileNameLength / sizeof(WCHAR) + 1));
   			}
   #			else
   			{
   				int count = WideCharToMultiByte2(CP_ACP, 0, pNotify->FileName,
   					pNotify->FileNameLength / sizeof(WCHAR),
   					szFile, MAX_PATH - 1, nullptr, nullptr);
   				szFile[count] = TEXT('\0');
   			}
   #			endif

   			pWatch->m_pwatcher->handle_action(pWatch, szFile, pNotify->Action);

   		} while (pNotify->NextEntryOffset != 0);
   	}

   	if (!pWatch->m_bStop)
   	{
   		RefreshWatch(pWatch);
   	}
   }

   /// Refreshes the directory monitoring.
   bool RefreshWatch(watch_struct* pWatch, bool _clear)
   {
   	return ReadDirectoryChangesW(
   		pWatch->m_hDirectory, pWatch->m_buffer, sizeof(pWatch->m_buffer), false,
   		pWatch->m_dwNotify, nullptr, &pWatch->m_overlapped, _clear ? 0 : WatchCallback) != 0;
   }*/

/// Stops monitoring a directory.
   void DestroyWatch(watch_ref ^ pwatch)
   {
      if(pwatch != nullptr)
      {
         //delete pWatch;
      }
   }
/// Starts monitoring a directory.
   watch_ref ^ watch_ref::create_watch(String ^ strDirectory, bool bRecursive)
   {

      try
      {

         watch_ref ^ pwatch = ref new watch_ref;

         Windows::Storage::Search::QueryOptions ^ options = ref new Windows::Storage::Search::QueryOptions();

         pwatch->m_bRecursive = bRecursive;

         if (pwatch->m_bRecursive)
         {

            options->FolderDepth = ::Windows::Storage::Search::FolderDepth::Deep;

         }
         else
         {

            options->FolderDepth = ::Windows::Storage::Search::FolderDepth::Shallow;

         }

         options->IndexerOption = ::Windows::Storage::Search::IndexerOption::DoNotUseIndexer;

         string strPrefix;

         pwatch->m_folder = winrt_get_folder(strDirectory, strPrefix);

         if (pwatch->m_folder == nullptr)
         {

            return nullptr;

         }

         pwatch->m_queryresult = pwatch->m_folder->CreateItemQuery();

         if (pwatch->m_queryresult == nullptr)
            return nullptr;

         pwatch->m_evtoken = pwatch->m_queryresult->ContentsChanged += ref new ::Windows::Foundation::TypedEventHandler < ::Windows::Storage::Search::IStorageQueryResultBase ^,
                 ::Object ^ >(pwatch, &watch_ref::ContentsChanged);

         return pwatch;

      }
      catch (...)
      {

      }

      return nullptr;

   }


   #pragma endregion


   os_watcher::os_watcher()
   {

      m_bCreateWatchThread = false;

   }


   os_watcher::~os_watcher()
   {

      //watch_map::pair * ppair = m_watchmap.get_start();
      //for(; ppair != nullptr; m_watchmap.get_next(ppair))
      //{
      //   DestroyWatch(ppair->element2().w);
      //}
      //m_watchmap.remove_all();

   }


   bool os_watch::open(const ::file::path& pathFolderParam, bool bRecursive)
   {

      ::file::path pathFolder = get_context()->defer_process_path(pathFolderParam);

      if (!watch::open(pathFolderParam, bRecursive))
      {

         return false;

      }

      //watch_struct ^ pwatch = watch_struct::create_watch(m_str(directory), FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_FILE_NAME);
      watch_ref^ watchref = watch_ref::create_watch(pathFolder, bRecursive);

      if (watchref == nullptr)
      {

         return false;

      }

      m_watchref = watchref;

      return true;

   }


   //watch_id os_watcher::add_watch(const ::file::path& pathFolderParam, listener* plistenerParam, bool bRecursive)
   //{

   //   synchronization_lock synchronizationlock(mutex());

   //   id watchid = ++m_idLast;

   //   ::file::path pathFolder = get_context()->defer_process_path(pathFolderParam);

   //   //watch_struct ^ pwatch = watch_struct::create_watch(m_str(directory), FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_FILE_NAME);
   //   watch_ref ^ watchref = watch_ref::create_watch(pathFolder, bRecursive);

   //   if (watchref == nullptr)
   //   {

   //      return -1;

   //   }

   //   //watchref->m_bOwn           = bOwn;

   //   watchref->m_bRecursive     = bRecursive;

   //   auto pwatch = __new(os_watch);

   //   pwatch->m_id               = watchid;

   //   pwatch->m_listenera.add(plistenerParam);

   //   pwatch->m_pwatcher         = this;

   //   pwatch->m_pathFolder        = pathFolder;

   //   pwatch->m_watchref         = watchref;

   //   m_watchmap.set_at(watchid, pwatch);

   //   return watchid;

   //}


   //void os_file_watcher::remove_watch(const string & directory)
   //{

   //   watch_map::pair * ppair = m_watchmap.get_start();

   //   String ^ strDir = directory;

   //   for(; ppair != nullptr; m_watchmap.get_next(ppair))
   //   {

   //      if(strDir == ppair->element2()->m_strFolder)
   //      {

   //         remove_watch(ppair->element1());

   //         return;

   //      }

   //   }

   //}


   //void os_file_watcher::remove_watch(id watchid)
   //{

   //   watch_map::pair * ppair = m_watchmap.plookup(watchid);

   //   if(ppair == nullptr)
   //      return;

   //   m_watchmap.remove_key(ppair->element1());

   //}


   //string os_file_watcher::watch_path(id watchid)
   //{

   //   return m_watchmap[watchid]->m_strFolder;

   //}


   //bool os_file_watcher::update()
   //{
   //   //MsgWaitForMultipleObjectsEx(0, nullptr, 0, QS_ALLINPUT, MWMO_ALERTABLE);

   //   return true;

   //}


   //void os_file_watcher::handle_action(action * psubject)
   //{
   //   /*Action fwAction;

   //   switch(action)
   //   {
   //   case FILE_ACTION_RENAMED_NEW_NAME:
   //   case FILE_ACTION_ADDED:
   //   	fwAction = Actions::Add;
   //   	break;
   //   case FILE_ACTION_RENAMED_OLD_NAME:
   //   case FILE_ACTION_REMOVED:
   //   	fwAction = Actions::Delete;
   //   	break;
   //   case FILE_ACTION_MODIFIED:
   //   	fwAction = Actions::Modified;
   //   	break;
   //   };

   //   watch->mFileWatchListener->handleFileAction(watch->mWatchid, watch->m_strDirName, filename, fwAction);*/
   //}

} // namespace file_watcher




