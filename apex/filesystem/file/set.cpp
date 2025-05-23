#include "framework.h"
#include "set.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/parallelization/happening.h"
#include "apex/platform/application.h"
#include "apex/platform/node.h"
//#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"



namespace file
{


   set::set()
   {

      defer_create_synchronization();

   }


   set::~set()
   {

   }


   void set::on_initialize_particle()
   {

      //auto estatus = ::object::on_initialize_particle();
      ::object::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_ppathaSearch.create_new(this);
      
      m_pbaRecursive.create_new(this);

      //return estatus;

   }


   void set::add_search(const ::file::path & pathSearchFolder, bool bRecursive)
   {

      m_ppathaSearch->add(pathSearchFolder);

      m_pbaRecursive->add(bRecursive);

   }


   void set::add_search(const ::file::path_array & pathaSearchFolder, const bool_array & baRecursive)
   {

      // derived classes may perform specific actions this add_search...

      for (::collection::index i = 0; i < pathaSearchFolder.get_count(); i++)
      {

         // ... or at the add_search overload below.

         add_search(pathaSearchFolder[i], baRecursive[i]);

      }

   }


   void set::add_filter(string_array & stra)
   {

      m_straFilter.append(stra);

   }


   ::collection::count set::get_file_count()
   {

      return m_listing.get_size();

   }


   void set::file_at(::collection::index i, string & str)
   {

      str = m_listing[i];

   }


   ::collection::index set::find_first_file(const ::scoped_string & scopedstr, ::collection::index iStart)

   {

      return m_listing.case_insensitive_find_first(scopedstr, iStart);

   }


   void set::refresh()
   {

      clear_file();

      string strFilter;

      int i;

      string strFile;

      string str;

      for(i = 0; i < m_ppathaSearch->get_size(); i++)
      {

         bool bRecursive = true;

         if(i < m_pbaRecursive->get_size())
         {

            bRecursive = m_pbaRecursive->element_at(i);

         }

         ::file::path & pathFolder = m_ppathaSearch->element_at(i);

         m_listing.m_pathUser = pathFolder;

         m_listing.m_straPattern = m_straFilter;

         if (bRecursive)
         {

            m_listing.m_edepth = e_depth_recursively;

         }

         directory()->enumerate(m_listing);

         //}
         //else
         //{

         //   directory()->ls_file_pattern(m_listing, pathFolder, m_straFilter);

         //}

      }

      m_listing.add_listing(m_listingAddUp);

   }


   void set::clear_file()
   {

      m_listing.clear();

   }


   void set::clear_search()
   {

      m_ppathaSearch->erase_all();

      m_pbaRecursive->erase_all();

   }


   void set::clear_filter()
   {

      m_straFilter.erase_all();

   }


   bool set::get_next_file(const ::scoped_string & scopedstrFile, string & strNext)
   {

      auto iFind = find_first_file(scopedstrFile);

      if(not_found(iFind))
      {

         iFind = -1;

      }

      ::collection::index iNext = iFind + 1;

      if(iNext >= m_listing.get_count())
      {

         iNext = 0;

      }

      if(iNext >= m_listing.get_count())
      {

         return false;

      }

      strNext = m_listing[iNext];

      return true;

   }


   string set::get_next_file(const ::scoped_string & scopedstrFile)
   {

      string strNext;

      if(!get_next_file(scopedstrFile, strNext))
      {

         return "";

      }

      return strNext;

   }


   void set::initialize_os_wallpaper(bool bAddSearch)
   {

      node()->initialize_wallpaper_fileset(this, bAddSearch);
      //{

      //   return false;

      //}

      refresh();

      if(m_listing.is_empty())
      {

         if (!bAddSearch)
         {

            node()->initialize_wallpaper_fileset(this, true);

            ::file::set::refresh();

            if (m_listing.is_empty())
            {

               node()->::platform::node::initialize_wallpaper_fileset(this, bAddSearch);

               ::file::set::refresh();

            }

         }

      }

      //return true;

   }


} // namespace file





