#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_userfs.h"
#endif
#include "list_item_array.h"
#include "list_item.h"


namespace userfs
{

   //void list_item_array::SoftSwap(index i1, index i2)
   //{
   //   index iArrange = this->element_at(i1)->m_iArrange;
   //   this->element_at(i1)->m_iArrange = this->element_at(i2)->m_iArrange;
   //   this->element_at(i2)->m_iArrange = iArrange;
   //}


   //__pointer(list_item) list_item_array::get_item(index i, const ::atom & atom)
   //{

   //   return this->element_at(i, atom);

   //}


   list_item_array::list_item_array()
   {

  /*    add_sort((::i64) ::fs::arrange_by_name, [](auto & pitem1, auto & pitem2)
         {

            int iCompareType = pitem1->get_type_weight() - pitem2->get_type_weight();

            if (iCompareType != 0) return iCompareType;

            return pitem1->m_strName.compare_ci(pitem2->m_strName);

         });*/

   }


   list_item_array::~list_item_array()
   {

   }


   void list_item_array::add_fs_item(list_item & item)
   {

      add(__new(list_item(item)));

   }


   index list_item_array::find_item_by_path(const ::file::path & path)
   {

      for(i32 i = 0; i < this->get_count(); i++)
      {

         if(operator[](i)->final_path() == path)
         {

            return i;

         }

         if (operator[](i)->user_path() == path)
         {

            return i;

         }

      }

      return -1;

   }


   void list_item_array::arrange(::fs::e_arrange earrange)
   {

      //sort((::i64) earrange);

   }


} // namespace userfs




