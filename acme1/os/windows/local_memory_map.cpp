#include "framework.h"


namespace file
{


   bool memory_map::open()
   {

      close();

      string strPath = get_path();

      wstring wstr(strPath);

      if (strPath.begins_ci("Local\\") || strPath.begins_ci("Global\\"))
      {

         m_hfile = INVALID_HANDLE_VALUE;

         m_hfilemap = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, (DWORD)m_size, wstr);

      }
      else
      {

         int iOpen;

         if (m_bCreate)
         {

            iOpen = OPEN_ALWAYS;

         }
         else
         {

            iOpen = OPEN_EXISTING;

         }

         m_hfile = CreateFileW(wstr, (m_bRead | m_bWrite ? FILE_READ_DATA : 0) | (m_bWrite ? FILE_WRITE_DATA : 0), FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr, iOpen, FILE_ATTRIBUTE_NORMAL, nullptr);

         if (m_hfile == INVALID_HANDLE_VALUE)
         {

            close();

            return false;

         }
         else
         {

            ensure_file_size_handle(m_hfile, m_size);

         }

         m_hfilemap = CreateFileMappingW(m_hfile, nullptr, PAGE_READWRITE, 0, 0, nullptr);

      }

      if (m_hfilemap == nullptr)
      {
         close();

         return false;
      }

      m_pdata = MapViewOfFile(m_hfilemap, (m_bRead ? FILE_MAP_READ : 0) | (m_bWrite ? FILE_MAP_WRITE : 0), 0, 0, 0);

      if (m_pdata == nullptr)
      {

         close();

         return false;

      }

      string strMutex;

      strMutex = strPath + "-::mutex";

      m_pmutex = new ::mutex(e_create_new, strMutex, nullptr, false);

      return true;

   }










































   void memory_map::construct()
   {

      m_strName.Empty();
      m_hfile = INVALID_HANDLE_VALUE;
      m_hfilemap = nullptr;
      m_pdata = nullptr;
      m_bRead = false;
      m_bWrite = false;
      m_bCreate = false;

   }


   bool memory_map::is_mapped()
   {

      return m_pdata != nullptr;

   }


   bool memory_map::close()
   {

      sync_lock sl(mutex());

      if (m_pdata != nullptr)
      {

         UnmapViewOfFile(m_pdata);

         m_pdata = nullptr;

      }

      if (m_hfile != nullptr)
      {

         try
         {

            ::CloseHandle(m_hfile);

         }
         catch (...)
         {

         }

         m_hfile = nullptr;

      }


      if (m_hfile != INVALID_HANDLE_VALUE)
      {

         try
         {

            ::CloseHandle(m_hfile);

         }
         catch (...)
         {

         }

         m_hfile = INVALID_HANDLE_VALUE;

      }

      return true;

   }


} // namespace file



