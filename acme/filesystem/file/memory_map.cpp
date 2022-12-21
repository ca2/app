#include "framework.h"
#include "memory_map.h"
#include "acme/exception/interface_only.h"


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

//#ifdef LINUX
//
//      ::file::path path("/::payload/tmp/ca2/");
//
//      string str = m_strName;
//
//      if (str.case_insensitive_begins_eat("Local\\"))
//      {
//
//         path /=          auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->home() / str;
////
//      }
//      else
//      {
//
//         path /= str;
//
//      }
//
//      return path;
//
//#endif
//
//      string strName = m_strName;
//
//      if (strName.case_insensitive_begins_eat("Local\\bitmap-source-"))
//      {
//
//         return ::file::path("C:\\archive\\bitmap-source") / (strName + ".bitmap-source");
//
//      }
//
//      return m_strName;

      return m_strPath;

   }




   bool memory_map::open_name(const ::scoped_string & scopedstrName, bool bRead, bool bWrite, bool bCreate, memsize size)
   {

      string strPath = calculate_path_from_name(scopedstrName);

      if(strPath.is_empty())
      {

         return false;

      }

      return open(strPath, scopedstrName, bRead, bWrite, bCreate, size);

   }


   bool memory_map::open_path(const ::file::path & path, bool bRead, bool bWrite, bool bCreate, memsize size)
   {

      return open(path, path, bRead, bWrite, bCreate, size);

   }


   bool memory_map::open(const ::scoped_string & scopedstrName, const ::file::path & path, bool bRead, bool bWrite, bool bCreate, memsize size)
   {

      m_strPath = path;

      m_strName = scopedstrName;

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


   string memory_map::calculate_path_from_name(const ::string & strName)
   {

      throw ::interface_only();

      return "";

   }


// SALADA AND PASTA and me pig searching for food is good EAT IT!! But mama te



} /// namespace file


