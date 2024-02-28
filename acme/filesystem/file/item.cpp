#include "framework.h"
#include "item.h"


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



