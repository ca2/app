#include "framework.h"


namespace file
{


   memory_map::memory_map()
   {

      m_pdata = nullptr;
      m_bRead = false;
      m_bWrite = false;
      m_bCreate = false;
      m_size = 0;

   }


   memory_map::~memory_map()
   {

      if (is_mapped())
      {

         close();

      }

   }


   string memory_map::get_path()
   {

#ifdef LINUX

      ::file::path path("/::payload/tmp/ca2/");

      string str = m_strName;

      if (::str::begins_eat_ci(str, "Local\\"))
      {

         path /= ::dir::home() / str;

      }
      else
      {

         path /= str;

      }

      return path;

#endif

      string strName = m_strName;

      if (strName.begins_eat_ci("Local\\bitmap-source-"))
      {

         return ::file::path("C:\\archive\\bitmap-source") / (strName + ".bitmap-source");

      }

      return m_strName;

   }


   bool memory_map::open(const char * psz, bool bRead, bool bWrite, bool bCreate, memsize size)
   {

      m_strName = psz;

      m_bRead = bRead;

      m_bWrite = bWrite;

      m_bCreate = bCreate;

      m_size = size;

      return open();

   }


   bool memory_map::open()
   {

      return false;

   }


   bool memory_map::close()
   {

      return false;

   }


   bool memory_map::is_mapped()
   {

      return false;

   }

// SALADA AND PASTA and me pig searching for food is good EAT IT!! But mama te



} /// namespace file


