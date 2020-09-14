#include "framework.h"


namespace file
{


   memory_map::memory_map()
   {

      construct();

   }


   memory_map::memory_map(const char * psz, bool bRead, bool bWrite, bool bCreate, memsize size)
   {

      construct();

      if (!open(psz, bRead, bWrite, bCreate, size))
      {

         string strFormat;

         strFormat.Format("failed to open memory_map : \"%s\" bRead %d bWrite %d bCreate %d size %lld ", psz, int(bRead), int(bWrite), int(bCreate), size);

         __throw(::exception::exception(strFormat));

      }

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

      ::file::path path("/var/tmp/ca2/");

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




// SALADA AND PASTA and me pig searching for food is good EAT IT!! But mama te



} /// namespace file


