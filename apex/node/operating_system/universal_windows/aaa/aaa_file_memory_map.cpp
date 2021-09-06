#include "framework.h"


namespace file
{


   bool memory_map::open()
   {


      close();

      int iOpen;

      if (m_bCreate)
      {
         iOpen = OPEN_ALWAYS;
      }
      else
      {
         iOpen = OPEN_EXISTING;
      }

      wstring wstr(get_path());

      CREATEFILE2_EXTENDED_PARAMETERS ps;
      zero(&ps, sizeof(ps));
      ps.dwSize = sizeof(ps);
      ps.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;

      m_hfile = CreateFile2(wstr, (m_bRead ? FILE_READ_DATA : 0) | (m_bWrite ? FILE_WRITE_DATA : 0), FILE_SHARE_WRITE | FILE_SHARE_READ, iOpen, &ps);

      if (m_hfile == INVALID_HANDLE_VALUE)
      {

         close();

         return false;

      }

      ensure_file_size_handle(m_hfile, m_size);

      m_hfilemap = CreateFileMappingFromApp(m_hfile, nullptr, PAGE_READWRITE, m_size, nullptr);

      if (m_hfilemap == nullptr)
      {

         close();

         return false;

      }

      m_pdata = MapViewOfFileFromApp(m_hfilemap, (m_bRead ? FILE_MAP_READ : 0) | (m_bWrite ? FILE_MAP_WRITE : 0), 0, 0);

      if (m_pdata == nullptr)
      {

         close();

         return false;

      }

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

      synchronous_lock synchronouslock(mutex());

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

      //   ::acme::del(mutex());

      return true;

   }


} // namespace file




