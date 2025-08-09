#include "framework.h"
#include "set.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/listener.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


namespace fs
{


   set::set()
   {

   }


   set::~set()
   {

   }


   string_map < ::pointer<::fs::data >>& set::fsmap()
   {

      return m_fsdatamap;

   }


   pointer_array < ::fs::data > & set::fsa()
   {

      return m_spafsdata;

   }


   void set::destroy()
   {

      for (auto& pdata : m_spafsdata)
      {

         pdata->destroy();


      }

      for (auto& pdata : m_fsdatamap.payloads())
      {

         pdata->destroy();

      }

      m_spafsdata.erase_all();

      m_fsdatamap.erase_all();
      
      ::fs::data::destroy();

      //return ::success;

   }


   ::file::listing_base & set::root_ones(::file::listing_base & listing)
   {

      _synchronous_lock synchronouslock(synchronization());

      m_fsdatamap.erase_all();

      ::file::listing_base listingFsPath;

      for(int i = 0; i < m_spafsdata.get_count(); i++)
      {

         listingFsPath.clear_results();

         data * pdata =  m_spafsdata[i];

         synchronouslock.unlock();

         pdata->root_ones(listingFsPath);

         synchronouslock._lock();

         listing.add_listing(listingFsPath);

         for(int j = 0; j < listingFsPath.get_size(); j++)
         {

            auto p = listing[j];

            m_fsdatamap[p] = m_spafsdata[i];

         }

      }

      return listing;

   }


   ::pointer<data>set::path_data(const ::payload & payloadFile)
   {

      auto filepath = payloadFile.as_file_path();

      auto range = filepath();

      _synchronous_lock synchronouslock(synchronization());

      auto p = m_fsdatamap.begin();

      string strRoot;

      {

         ::pointer<::fs::data>pdata;

         for(;p.is_set();p++)
         {

            strRoot = p->m_element1;

            pdata = p->m_element2;

            if (pdata.is_set())
            {

               if (range.case_insensitive_begins(strRoot))
               {

                  return pdata;

               }
               
               auto pathRoot = m_papplication->defer_process_path(strRoot);
               
               if(pathRoot.has_character())
               {
                  
                  if (range.case_insensitive_begins(pathRoot))
                  {
                     
                     return pdata;
                     
                  }
                  
               }
               
            }

         }

      }

      {

         ::pointer<::fs::data>pdata;

         for (; p.is_set(); p++)
         {

            strRoot = p->m_element1;

            pdata = p->m_element2;

            if (pdata.is_set())
            {

               if (pdata->is_dir(range))
               {

                  return pdata;

               }

            }

         }

      }

      return nullptr;

   }


   ::pointer<data>set::node_path_data(const ::file::path & path)
   {

      ::pointer<data>pdata = path_data(path);

      if(pdata == nullptr)
      {

         return this;

      }

      return pdata->node_path_data(path);

   }

   
   bool set::enumerate(::file::listing_base & listing)
   {

      if(listing.m_pathUser.is_empty())
      {

         return root_ones(listing);

      }

      ::fs::data * pdata = path_data(listing.m_pathFinal);

      if(pdata != nullptr)
      {

         return pdata->enumerate(listing);

      }

      //return listing = ::error_failed;

      return listing;

   }


   //::file::listing_base & set::ls_relative_name(::file::listing_base & listing)
   //{

   //   if (listing.m_pathFinal.is_empty())
   //   {

   //      return root_ones(listing);

   //   }

   //   ::fs::data * pdata = path_data(listing.m_pathFinal);

   //   if (pdata != nullptr)
   //   {

   //      return pdata->ls_relative_name(listing);

   //   }

   //   //return listing = ::error_failed;

   //   return listing;

   //}


   int set::is_dir(const ::file::path & path)
   {

      if (path.m_etype & ::file::e_type_exists)
      {

         return path.m_etype & ::file::e_type_folder2;

      }

      ::fs::data * pdata = path_data(path);

      if(pdata != nullptr)
      {

         return pdata->is_dir(path);

      }

      return -1;

   }


   ::file::e_type set::file_type(const ::file::path& path)
   {

      if (path.is_file_or_folder())
      {

         return path.type();

      }

      ::fs::data* pdata = path_data(path);

      if (pdata != nullptr)
      {

         return pdata->file_type(path);

      }

      return ::file::e_type_unknown;

   }


   //string set::file_name(const ::file::path & path)
   //{

   //   ::fs::data * pdata = path_data(scopedstr);

   //   if(pdata != nullptr)
   //   {
   //      return pdata->file_name(scopedstr);
   //   }

   //   return "";

   //}


   bool set::file_move(const ::file::path & pathTarget, const ::file::path & pathSource)
   {

      ::fs::data * pdataDst = path_data(pathTarget);
      ::fs::data * pdataSrc = path_data(pathSource);

      if(pdataDst != nullptr && pdataSrc == pdataDst)
      {
         return pdataDst->file_move(pathTarget, pathSource);
      }
      else
      {
         try
         {
            file()->copy(pathTarget, pathSource);
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


   file_pointer set::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
   {

      ::fs::data * pdata = path_data(payloadFile);

      if (pdata == nullptr)
      {

         return nullptr;

      }

      return pdata->get_file(payloadFile, eopen, ppfileexception);

   }


   //void set::get_ascendants_path(const ::file::path & path,::file::path_array_base & stra)
   //{

   //   ::fs::data * pdata = path_data(scopedstr);

   //   if(pdata != nullptr)
   //   {
   //      pdata->get_ascendants_path(scopedstr, stra);
   //   }

   //}


   //string set::eat_end_level(const ::scoped_string & scopedstr, int iLevel)
   //{

   //   ::fs::data * pdata = path_data(scopedstr);

   //   if(pdata != nullptr)
   //   {
   //      return pdata->eat_end_level(scopedstr, iLevel);
   //   }

   //   return "";

   //}


   //string set::dir_path(const ::file::path & path1, const ::file::path & path2)
   //{

   //   ::fs::data * pdata = path_data(scopedstrPath1);

   //   if(pdata != nullptr)
   //   {
   //      return pdata->dir_path(scopedstrPath1, pszPath2);
   //   }

   //   return ::file::path(scopedstrPath1) / pszPath2;

   //}


   bool set::is_zero_latency(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != nullptr)
      {
         return pdata->is_zero_latency(path);
      }

      return ::fs::data::is_zero_latency(path);

   }


} // namespace fs

