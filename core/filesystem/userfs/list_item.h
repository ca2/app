#pragma once


#include "acme/filesystem/file/item.h"


namespace userfs
{


   class CLASS_DECL_CORE list_item :
      virtual public ::file::item
   {
   public:


      int      m_iImage;
      int      m_iImageSelected;


      list_item();
      list_item(const list_item & item);

      //static index CompareArrangeByName(const ::pointer<list_item>& pitema, const ::pointer<list_item> pitemb);
      //index CompareArrangeByName(const list_item & item) const;
      //index GetIndex() const;

      inline int get_type_weight() { return IsFolder() ? 0 : 1; }

      list_item & operator = (const list_item & item);


   };


} // namespace userfs


template < class T >
T cast (::userfs::list_item & item)
{
   return T(item);
}


template <>
CLASS_DECL_CORE ::file::item cast < ::file::item > (::userfs::list_item & item);
