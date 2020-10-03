#include "framework.h"


namespace file
{


   set::set() :
      m_ppathaSearch(e_create_new),
      m_pbaRecursive(e_create_new)
   {

      defer_create_mutex();

   }


   set::~set()
   {

   }


   void set::add_search(const ::file::path & pathSearchFolder, bool bRecursive)
   {

      m_ppathaSearch->add(pathSearchFolder);

      m_pbaRecursive->add(bRecursive);

   }


   void set::add_search(const ::file::patha & pathaSearchFolder, const bool_array & baRecursive)
   {

      // derived classes may perform specific actions this add_search...

      for (index i = 0; i < pathaSearchFolder.get_count(); i++)
      {

         // ... or at the add_search overload below.

         add_search(pathaSearchFolder[i], baRecursive[i]);

      }

   }


   void set::add_filter(string_array & stra)
   {

      m_straFilter.add(stra);

   }


   ::count set::get_file_count()
   {

      return m_listing.get_size();

   }


   void set::file_at(::index i, string & str)
   {

      str = m_listing[i];

   }


   ::index set::find_first_file(const char * pcsz, ::index iStart)

   {

      return m_listing.find_first_ci(pcsz, iStart);

   }


   void set::refresh()
   {

      clear_file();

      string strFilter;

      i32 i;

      string strFile;

      string str;

      for(i = 0; i < m_ppathaSearch->get_size(); i++)
      {

         bool bRecursive = true;

         if(i < m_pbaRecursive->get_size())
         {

            bRecursive = m_pbaRecursive->element_at(i);

         }

         m_listing.m_pprovider = get_context();

         ::file::path & pathFolder = m_ppathaSearch->element_at(i);

         if(bRecursive)
         {

            Context.dir().rls_pattern(m_listing, pathFolder, m_straFilter);

         }
         else
         {

            Context.dir().ls_pattern(m_listing, pathFolder, m_straFilter);

         }

      }

      m_listing.add(m_listingAddUp);

   }


   void set::clear_file()
   {

      m_listing.clear();

   }


   void set::clear_search()
   {

      m_ppathaSearch->remove_all();

      m_pbaRecursive->remove_all();

   }


   void set::clear_filter()
   {

      m_straFilter.remove_all();

   }


   bool set::get_next_file(const char * pszFile, string & strNext)
   {

      index iFind = find_first_file(pszFile);

      if(iFind < 0)
      {

         iFind = -1;

      }

      index iNext = iFind + 1;

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


   string set::get_next_file(const char * pszFile)
   {

      string strNext;

      if(!get_next_file(pszFile, strNext))
      {

         return "";

      }

      return strNext;

   }


   bool set::initialize_os_wallpaper(bool bAddSearch)
   {

      if (!Context.os().initialize_wallpaper_fileset(this, bAddSearch))
      {

         return false;

      }

      refresh();

      if(m_listing.is_empty())
      {

         if (!bAddSearch)
         {

            Context.os().initialize_wallpaper_fileset(this, true);

            ::file::set::refresh();

            if (m_listing.is_empty())
            {

               Context.os().::os_context::initialize_wallpaper_fileset(this, bAddSearch);

               ::file::set::refresh();

            }

         }

      }

      return true;

   }


} // namespace file





