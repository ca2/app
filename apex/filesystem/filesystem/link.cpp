// Created by camilo on 2023-03-13 23:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "link.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"


namespace file
{


   link::link()
   {

      m_iIcon = 0;

   }


   link::~link()
   {


   }


   void link::clear()
   {

      m_path.clear();

      m_elink = ::file::e_link_none;

      m_pathTarget.clear();

      m_pathFolder.clear();

      m_pathIcon.clear();

      m_iIcon = 0;

   }


   ::pointer < ::file::link > link::create_clean_new() const
   {

      return ((link *)this)->__create_new < ::file::link >();

   }


   void link::open(const ::file::path & path, ::file::e_link elink)
   {


   }


   ::file::e_link link::write(const ::file::path & pathWriteAs)
   {

      return ::file::e_link_none;

   }


   ::file::e_link link::path_find_replace(const ::scoped_string & scopedstrSource, const ::scoped_string & scopedstrTarget)
   {

      ::file::e_link elinkChanged = ::file::e_link_none;

      auto pparticle = (::particle *)this;

      if (m_elink & ::file::e_link_target)
      {

         auto pathNew = path_find_replace(m_pathTarget, scopedstrSource, scopedstrTarget);

         if (m_pathTarget != pathNew)
         {

            bool bIsDir = pparticle->acmedirectory()->is(pathNew);

            bool bIsFile = pparticle->acmefile()->exists(pathNew);

            bool bIsFileSystemObject = bIsDir || bIsFile;

            if (bIsFileSystemObject)
            {

               m_pathTarget = pathNew;

               elinkChanged |= ::file::e_link_target;

            }

         }

      }

      if (m_elink & ::file::e_link_folder)
      {

         auto pathNew = path_find_replace(m_pathFolder, scopedstrSource, scopedstrTarget);

         if (m_pathFolder != pathNew)
         {

            bool bIsDir = pparticle->acmedirectory()->is(pathNew);

            if (bIsDir)
            {

               m_pathFolder = pathNew;

               elinkChanged |= ::file::e_link_folder;

            }

         }

      }

      if (m_elink & ::file::e_link_icon)
      {

         auto pathNew = path_find_replace(m_pathIcon, scopedstrSource, scopedstrTarget);

         if (m_pathIcon != pathNew)
         {

            m_pathIcon = pathNew;

            elinkChanged |= ::file::e_link_icon;

         }

      }

      return elinkChanged;

   }


   ::file::path link::path_find_replace(const ::file::path & path, const ::scoped_string & scopedstrSource, const ::scoped_string & scopedstrTarget) const
   {

      ::file::path pathNew;

      pathNew = path;

      pathNew.find_replace(scopedstrSource, scopedstrTarget);

      return pathNew;


   }


} // namespace file



