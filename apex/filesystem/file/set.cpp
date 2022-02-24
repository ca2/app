#include "framework.h"


namespace file
{


   set::set()
   {

      defer_create_mutex();

   }


   set::~set()
   {

   }


   void set::on_initialize_object()
   {

      //auto estatus = ::object::on_initialize_object();
      ::object::on_initialize_object();

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

         m_listing.m_pprovider = m_pcontext->m_papexcontext;

         ::file::path & pathFolder = m_ppathaSearch->element_at(i);

         if(bRecursive)
         {

            m_pcontext->m_papexcontext->dir().rls_file_pattern(m_listing, pathFolder, m_straFilter);

         }
         else
         {

            m_pcontext->m_papexcontext->dir().ls_file_pattern(m_listing, pathFolder, m_straFilter);

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

      m_ppathaSearch->erase_all();

      m_pbaRecursive->erase_all();

   }


   void set::clear_filter()
   {

      m_straFilter.erase_all();

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


   void set::initialize_os_wallpaper(bool bAddSearch)
   {

      m_pcontext->m_papexcontext->os_context()->initialize_wallpaper_fileset(this, bAddSearch);
      //{

      //   return false;

      //}

      refresh();

      if(m_listing.is_empty())
      {

         if (!bAddSearch)
         {

            m_pcontext->m_papexcontext->os_context()->initialize_wallpaper_fileset(this, true);

            ::file::set::refresh();

            if (m_listing.is_empty())
            {

               m_pcontext->m_papexcontext->os_context()->::os_context::initialize_wallpaper_fileset(this, bAddSearch);

               ::file::set::refresh();

            }

         }

      }

      //return true;

   }


} // namespace file





