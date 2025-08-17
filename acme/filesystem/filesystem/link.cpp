// Created by camilo on 2023-03-13 23:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "link.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"


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

      return ((link *)this)->øcreate_new < ::file::link >();

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

            bool bIsDir = pparticle->directory_system()->is(pathNew);

            bool bIsFile = pparticle->file_system()->exists(pathNew);

            bool bIsFileSystemObject = bIsDir || bIsFile;

            m_pathTarget = pathNew;

            elinkChanged |= ::file::e_link_target;

         }

      }

      if (m_elink & ::file::e_link_folder)
      {

         auto pathNew = path_find_replace(m_pathFolder, scopedstrSource, scopedstrTarget);

         if (m_pathFolder != pathNew)
         {

            bool bIsDir = pparticle->directory_system()->is(pathNew);

            m_pathFolder = pathNew;

            elinkChanged |= ::file::e_link_folder;

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


   ::file::e_link link::check_link()
   {

      ::file::e_link elinkWithError = ::file::e_link_none;

      auto pparticle = (::particle *)this;

      if (m_pathTarget.has_character())
      {

         bool bIsDir = pparticle->directory_system()->is(m_pathTarget);

         bool bIsFile = pparticle->file_system()->exists(m_pathTarget);

         bool bIsFileSystemObject = bIsDir || bIsFile;

         if (!bIsFileSystemObject)
         {

            elinkWithError |= ::file::e_link_target;

         }

      }

      if (m_pathFolder.has_character())
      {

         bool bIsDir = pparticle->directory_system()->is(m_pathFolder);

         if (!bIsDir)
         {

            elinkWithError |= ::file::e_link_folder;

         }

      }

      if (m_pathIcon.has_character())
      {

         bool bIsFile = pparticle->file_system()->exists(m_pathTarget);

         if (!bIsFile)
         {

            elinkWithError |= ::file::e_link_icon;

         }

      }

      return elinkWithError;

   }


} // namespace file



