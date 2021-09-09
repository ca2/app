#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_userfs.h"
#endif



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
