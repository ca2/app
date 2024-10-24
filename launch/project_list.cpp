// Created by camilo on 2023-03-10 20:50 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "project_list.h"
#include "application.h"
#include "acme/platform/scoped_restore.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"


namespace application_build_helper
{


   project_list::project_list()
   {

   }


   project_list::~project_list()
   {


   }


   void project_list::create(application* papplication)
   {

      initialize(papplication);

      m_papplication = papplication;

      do_base("operating_system");

      do_base("source");

      file_system()->put_lines("project_list.txt", m_straLines);

   }


   bool project_list::do_base(const ::scoped_string& scopedstrBase)
   {

      auto range = scopedstrBase();

      range.trim();

      if (range.is_empty())
      {

         return false;

      }

      ::file::path pathFolder = m_papplication->m_pathFolder / range;

      ::file::listing listing;

      listing.set_folder_listing(pathFolder);

      directory_system()->enumerate(listing);

      for (auto& path : listing)
      {

         do_root(path);

      }

      return true;

   }


   bool project_list::do_root(const ::file::path& pathFolder)
   {

      if (pathFolder.is_empty())
      {

         return false;

      }

      ::file::listing listing;

      listing.set_folder_listing(pathFolder);

      directory_system()->enumerate(listing);

      for (auto& path : listing)
      {

         string strLine;
         
         strLine = path;

         strLine.case_insensitive_begins_eat(m_papplication->m_pathFolder);

         strLine.trim("\\/");

         m_straLines.add(strLine);
         
         printf("%s\n", strLine.c_str());

      }

      return true;

   }


} // namespace application_build_helper



