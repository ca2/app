#include "framework.h"


namespace file
{


   item::item()
   {

   }


   item::item(const item & item) :
      matter(item),
      m_filepathUser(item.m_filepathUser),
      m_filepathFinal(item.m_filepathFinal),
      m_flags(item.m_flags),
      m_strName(item.m_strName)
   {

   }


   item::item(const ::file::path & filepathUser, const ::file::path & filepathFinal)
   {

      m_filepathUser = filepathUser;
      m_filepathFinal = filepathFinal;

   }


   item::item(const ::file::path & filepathUser, const ::file::path & filepathFinal, const enumeration < enum_flag > & flags)
   {

      m_filepathUser = filepathUser;
      m_filepathFinal = filepathFinal;
      m_flags = flags;

   }


   item::~item()
   {

   }


   ::file::path item::get_user_path() const
   {

      if (m_filepathUser.is_empty())
      {

         return m_filepathFinal;

      }

      return m_filepathUser;

   }


   ::file::path item::get_final_path() const
   {

      if (m_filepathFinal.is_empty())
      {

         return m_filepathUser;

      }

      return m_filepathFinal;

   }


   bool item::IsFolder() const
   {

      if (m_flags & ::file::e_flag_folder_ex001_calc)
      {

         return m_flags & ::file::e_flag_folder_ex001;

      }
      else
      {

         bool bFolderEx001 = (m_flags & ::file::e_flag_folder) || (m_flags & ::file::e_flag_in_zip);

         const_cast <item *> (this)->m_flags |= ::file::e_flag_folder_ex001_calc;

         if (bFolderEx001)
         {

            const_cast <item *> (this)->m_flags |= ::file::e_flag_folder_ex001;

         }

         return m_flags & ::file::e_flag_folder_ex001;

      }

   }


} // namespace file



