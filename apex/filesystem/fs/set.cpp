#include "framework.h"
#include "apex/filesystem/fs/_fs.h"


namespace fs
{


   set::set()
   {

   }


   set::~set()
   {

   }


   string_map < __pointer(::fs::data) > & set::fsmap()
   {

      return m_fsdatamap;

   }


   __pointer_array(::fs::data) & set::fsa()
   {

      return m_spafsdata;

   }


   ::e_status set::destroy()
   {

      for (auto& pdata : m_spafsdata)
      {

         pdata->destroy();


      }

      for (auto& pdata : m_fsdatamap.values())
      {

         pdata->destroy();

      }

      m_spafsdata.erase_all();

      m_fsdatamap.erase_all();
      
      ::fs::data::destroy();

      return ::success;

   }


   ::file::listing & set::root_ones(::file::listing & listing)
   {

      single_lock synchronouslock(mutex(), true);

      m_fsdatamap.erase_all();

      ::file::listing straFsPath;

      for(i32 i = 0; i < m_spafsdata.get_count(); i++)
      {

         straFsPath.clear_results();

         data * pdata =  m_spafsdata[i];

         synchronouslock.unlock();

         pdata->root_ones(straFsPath);

         synchronouslock.lock();

         listing.add(straFsPath);

         listing.m_straTitle.add(straFsPath.m_straTitle);

         for(i32 j = 0; j < straFsPath.get_size(); j++)
         {

            m_fsdatamap[straFsPath[j]] = m_spafsdata[i];

         }

      }

      return listing;

   }


   __pointer(data) set::path_data(const ::file::path & psz)
   {

      single_lock synchronouslock(mutex(), true);

      auto p = m_fsdatamap.begin();

      string strRoot;

      {

         __pointer(::fs::data) pdata;

         for(;p;p++)
         {

            strRoot = p->m_element1;

            pdata = p->m_element2;

            if (pdata.is_set())
            {

               if (::str::begins_ci(psz, strRoot))
               {

                  return pdata;

               }

            }

         }

      }

      {

         __pointer(::fs::data) pdata;

         for (; p; p++)
         {

            strRoot = p->m_element1;

            pdata = p->m_element2;

            if (pdata.is_set())
            {

               if (pdata->is_dir(psz))
               {

                  return pdata;

               }

            }

         }

      }

      return nullptr;

   }


   __pointer(data) set::node_path_data(const  ::file::path & psz)
   {

      __pointer(data) pdata = path_data(psz);

      if(pdata == nullptr)
         return this;

      return pdata->node_path_data(psz);

   }

   ::file::listing & set::ls(::file::listing & listing)
   {

      if(listing.m_pathUser.is_empty())
      {

         return root_ones(listing);

      }

      ::fs::data * pdata = path_data(listing.m_pathFinal);

      if(pdata != nullptr)
      {

         return pdata->ls(listing);

      }

      return listing = ::error_failed;

   }


   ::file::listing & set::ls_relative_name(::file::listing & listing)
   {

      if (listing.m_pathFinal.is_empty())
      {

         return root_ones(listing);

      }

      ::fs::data * pdata = path_data(listing.m_pathFinal);

      if (pdata != nullptr)
      {

         return pdata->ls_relative_name(listing);

      }

      return listing = ::error_failed;

   }


   int set::is_dir(const ::file::path & path)
   {

      if (path.m_iDir >= 0)
      {

         return path.m_iDir;

      }

      ::fs::data * pdata = path_data(path);

      if(pdata != nullptr)
      {

         return pdata->is_dir(path);

      }

      return -1;

   }


   //string set::file_name(const ::file::path & psz)
   //{

   //   ::fs::data * pdata = path_data(psz);

   //   if(pdata != nullptr)
   //   {
   //      return pdata->file_name(psz);
   //   }

   //   return "";

   //}


   bool set::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
   {

      ::fs::data * pdataDst = path_data(pszDst);
      ::fs::data * pdataSrc = path_data(pszSrc);

      if(pdataDst != nullptr && pdataSrc == pdataDst)
      {
         return pdataDst->file_move(pszDst, pszSrc);
      }
      else
      {
         try
         {
            m_pcontext->m_papexcontext->file().copy(pszDst, pszSrc);
         }
         catch(...)
         {
            return false;
         }
         return true;
      }

   }


   bool set::has_subdir(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != nullptr)
      {
         return pdata->has_subdir(path);
      }

      return false;

   }


   bool set::tree_show_subdir(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != nullptr)
      {
         return pdata->tree_show_subdir(path);
      }

      return false;

   }

   bool set::fast_has_subdir(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != nullptr)
      {
         return pdata->fast_has_subdir(path);
      }

      return false;

   }


   bool set::is_link(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != nullptr)
      {

         return pdata->is_link(path);

      }

      return false;

   }


   file_transport set::get_file(const ::file::path & path, const ::file::e_open & eopen)
   {

      ::fs::data * pdata = path_data(path);

      if (pdata == nullptr)
      {

         return nullptr;

      }

      return pdata->get_file(path, eopen);

   }


   //void set::get_ascendants_path(const ::file::path & psz,::file::patha & stra)
   //{

   //   ::fs::data * pdata = path_data(psz);

   //   if(pdata != nullptr)
   //   {
   //      pdata->get_ascendants_path(psz, stra);
   //   }

   //}


   //string set::eat_end_level(const char * psz, i32 iLevel)
   //{

   //   ::fs::data * pdata = path_data(psz);

   //   if(pdata != nullptr)
   //   {
   //      return pdata->eat_end_level(psz, iLevel);
   //   }

   //   return "";

   //}


   //string set::dir_path(const char * pszPath1, const char * pszPath2)
   //{

   //   ::fs::data * pdata = path_data(pszPath1);

   //   if(pdata != nullptr)
   //   {
   //      return pdata->dir_path(pszPath1, pszPath2);
   //   }

   //   return ::file::path(pszPath1) / pszPath2;

   //}


   bool set::is_zero_latency(const ::file::path & psz)
   {

      ::fs::data * pdata = path_data(psz);

      if(pdata != nullptr)
      {
         return pdata->is_zero_latency(psz);
      }

      return ::fs::data::is_zero_latency(psz);

   }


} // namespace fs

