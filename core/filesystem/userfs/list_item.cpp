#include "framework.h"
#include "list_item.h"


namespace userfs
{


   list_item::list_item()
   {

      m_iImage = -1;
      m_iImageSelected = -1;

   }


   list_item::list_item(const list_item & listitem) :
      ::file::item(listitem),
      m_iImage(listitem.m_iImage),
      m_iImageSelected(listitem.m_iImageSelected)
   {

   }


   list_item & list_item::operator = (const list_item & item)
   {

      if(&item == this)
      {

         return *this;

      }

      m_pathUser        = item.m_pathUser;
      m_pathFinal       = item.m_pathFinal;
      m_strName         = item.m_strName;
      m_flags           = item.m_flags;
      m_iImage          = item.m_iImage;
      m_iImageSelected  = item.m_iImageSelected;

      return *this;

   }


} // namespace userfs


template <>
::file::item cast < ::file::item > (::userfs::list_item & item)
{

   ::file::item itemT;

   itemT.set_user_path(item.user_path());

   itemT.set_final_path(item.final_path());

   itemT.m_flags        = item.m_flags;

   return itemT;

}
