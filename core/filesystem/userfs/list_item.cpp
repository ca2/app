#include "framework.h"
#include "_userfs.h"


namespace userfs
{


   list_item::list_item()
   {

   }


   list_item::list_item(const list_item & listitem) :
      ::file::item(listitem)
   {

   }


   list_item & list_item::operator = (const list_item & item)
   {

      if(&item == this)
      {

         return *this;

      }

      set_context_object(item.get_context_object());

      m_filepathUser    = item.m_filepathUser;
      m_filepathFinal   = item.m_filepathFinal;
      m_strName         = item.m_strName;
      m_flags           = item.m_flags;

      return *this;

   }


} // namespace userfs


template <>
::file::item cast < ::file::item > (::userfs::list_item & item)
{

   ::file::item itemT;

   itemT.m_filepathUser = item.m_filepathUser;

   itemT.m_filepathFinal = item.m_filepathFinal;

   itemT.m_flags = item.m_flags;

   return itemT;

}
