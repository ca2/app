#include "framework.h"
#include "item.h"
#include "acme/operating_system/time.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "acme/filesystem/filesystem/listing.h"


namespace file
{


   //item::item()
   //{

   //}


   //item::item(const item & item) :
   //   element(item),
   //   m_pathUser(item.m_pathUser),
   //   m_pathFinal(item.m_pathFinal),
   //   m_flags(item.m_flags),
   //   m_strName(item.m_strName)
   //{

   //}


   //item::item(const ::file::path & pathUser, const ::file::path & pathFinal)
   //{

   //   ASSERT()

   //   m_pathUser = pathUser;
   //   m_pathFinal = pathFinal;
   //   m_flags += e_flag_final_path;

   //}


   //item::item(const ::file::path & filepathUser, const ::file::path & filepathFinal, const enumeration < enum_flag > & flags)
   //{

   //   m_pathUser = filepathUser;
   //   m_pathFinal = filepathFinal;
   //   m_flags = flags;

   //}


   //item::~item()
   //{

   //}



   //void item::set_final_path_dir(int iDir)
   //{

   //   m_pathFinal.m_iDir = iDir;

   //}

   void item::truncate()
   {

      if (is_folder())
      {

         throw ::exception(error_wrong_state);

      }

      return this->file()->truncate(m_pathFinal);

   }


   void item::erase()
   {

      if (is_folder())
      {

         this->directory()->erase(m_pathFinal);

      }
      else
      {
         this->file()->erase(m_pathFinal);
      }

   }


   void item::create_folder()
   {

      this->directory()->create(m_pathFinal);

   }

   ::file::listing_base item::list()
   {

      if (!is_folder())
      {

         throw ::exception(error_wrong_state);

      }

      return directory()->folders_and_files(final_path());

   }


   ::filesize item::size() const
   {

      if (is_folder())
      {

         throw ::exception(error_wrong_state);

      }

      return this->file()->length(m_pathFinal);

   }


   class ::time item::last_modified_time() const
   {

      if (is_folder())
      {

         throw ::exception(error_wrong_state);

      }


      ::file_time_set filetimeset;

      ::get_file_time_set(m_pathFinal, filetimeset);

//      class ::time timeLastModified;

      class ::time timeLastModified(filetimeset.m_filetimeModified);

      return timeLastModified;

   }


   void item::set_last_modified_time(const class ::time & time)
   {


      if (is_folder())
      {

         throw ::exception(error_wrong_state);

      }


      // ::file_time_set filetimeset;
      //
      // ::get_file_time_set(m_pathFinal, filetimeset);
      //
      // //      class ::time timeLastModified;
      //
      // filetimeset.m_filetimeModified = time;
      //

      ::set_modified_file_time(final_path(), time);

      //return timeLastModified;


   }


   bool item::is_folder() const
   {

      if (m_flags & ::file::e_flag_folder_ex001_calc)
      {

         return m_flags & ::file::e_flag_folder_ex001;

      }
      else
      {

         if (m_pathFinal.is_empty())
         {

            ((item*)this)->m_pathFinal = m_papplication->defer_process_path(m_pathUser);

         }

         if (directory()->is(m_pathFinal))
         {

            ((item*)this)->m_flags |= ::file::e_flag_folder;

         }

         bool bFolderEx001 = (m_flags & ::file::e_flag_folder) || (m_flags & ::file::e_flag_in_zip);

         const_cast <item *> (this)->m_flags |= ::file::e_flag_folder_ex001_calc;

         if (bFolderEx001)
         {

            const_cast <item *> (this)->m_flags |= ::file::e_flag_folder_ex001;

         }

         return m_flags & ::file::e_flag_folder_ex001;

      }

   }


   bool item::is_file() const
   {

      if (m_flags & ::file::e_flag_folder_ex001_calc)
      {

         return m_flags & ::file::e_flag_folder_ex001;

      }
      else
      {

         if (m_pathFinal.is_empty())
         {

            ((item*)this)->m_pathFinal = m_papplication->defer_process_path(m_pathUser);

         }

         if (directory()->is(m_pathFinal))
         {

            ((item*)this)->m_flags |= ::file::e_flag_folder;

         }

         bool bFolderEx001 = (m_flags & ::file::e_flag_folder) || (m_flags & ::file::e_flag_in_zip);

         const_cast <item *> (this)->m_flags |= ::file::e_flag_folder_ex001_calc;

         if (bFolderEx001)
         {

            const_cast <item *> (this)->m_flags |= ::file::e_flag_folder_ex001;

         }

         return m_flags & ::file::e_flag_folder_ex001;

      }

   }


   bool item::exists() const
   {

      return is_folder() || is_file();

   }

} // namespace file



