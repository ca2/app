#include "framework.h"
#include "link.h"
#include "acme/filesystem/filesystem/listing.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/platform/context.h"


namespace fs
{


   link::link()
   {
      
   }


   link::~link()
   {

   }


   void link::initialize(::particle * pparticle) 
   {

      //auto estatus =
      ::fs::native::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __construct_new(m_plisting);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   // optional if ls_dir is implemented
   bool link::has_subdir(const ::file::path & path)
   {

      if(path == m_plisting->m_pathUser)
      {

         return true;

      }
      else
      {

         return native::has_subdir(path);

      }

   }


   bool link::enumerate(::file::listing & listing)
   {

      listing.clear_results();

      defer_fill_folder(m_strTitle, m_plisting->m_pathUser);

      if (listing.m_pathUser != m_plisting->m_pathUser)
      {

         return false;

      }

      listing = *m_plisting;

      return true;

   }


   int link::is_dir(const ::file::path & path)
   {

      if(path == m_plisting->m_pathUser)
      {

         return 1;

      }
      else
      {

         return native::is_dir(path);

      }

   }


   ::file::listing & link::root_ones(::file::listing & listing)
   {

      auto & path = listing.add_get(m_plisting->m_pathUser);

      path.m_iDir = 1;

      listing.m_straTitle.add(m_strTitle);

      return listing;

   }



   bool link::tree_show_subdir(const ::file::path & path)
   {

      if(path == m_plisting->m_pathUser)
      {

         return true;

      }
      else
      {

         return false;

      }

   }


   void link::defer_fill_folder(string strTitle, ::file::path pathFolder)
   {

      if (strTitle.is_empty() || pathFolder.is_empty())
      {

         return;

      }

      m_strTitle = strTitle;

      m_plisting->m_pathUser = pathFolder;

      m_plisting->clear_results();

      m_pcontext->m_papexcontext->dir().enumerate(*m_plisting);

   }


   void link::fill_os_user()
   {

      defer_fill_folder("Bookmark", "bookmark://");

   }


   void link::fill_os_user_desktop()
   {

      defer_fill_folder("Desktop", "desktop://");


   }


} // namespace fs



