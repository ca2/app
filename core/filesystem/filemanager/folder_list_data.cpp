#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"


namespace filemanager
{


   folder_list_data::folder_list_data()
   {

      defer_create_mutex();

   }


   folder_list_data::~folder_list_data()
   {

   }


   void folder_list_data::assert_valid() const
   {


   }


   void folder_list_data::dump(dump_context& dumpcontext) const
   {


   }


   void folder_list_data::_001GetItemText(::user::mesh_item * pitem)
   {

      synchronous_lock synchronouslock(mutex());

      if(pitem->m_iSubItem == 0)
      {

         string_array stra;

         if(!data_get(::id(), stra))
         {

            pitem->m_bOk = false;

            return;

         }

         pitem->m_strText = stra[pitem->m_iItem];

      }
      else if(pitem->m_iSubItem == 1)
      {

         i32_array ia;

         if (!data_get("recursive", ia))
         {

            pitem->m_bOk = false;

            return;

         }

         bool bRecursive = ia[pitem->m_iItem] != false;

         if(bRecursive)
         {

            pitem->m_strText = "Recursive";

         }
         else
         {

            pitem->m_strText.Empty();

         }

      }

      pitem->m_bOk = true;
   }


   void folder_list_data::GetSel(::user::list * plist, string_array & stra)
   {

      string_array wstraTotal;

      if (!data_get(::id(), wstraTotal))
      {

         return;

      }

      ::user::range range;

      plist->_001GetSelection(range);

      for(index i = 0; i < range.get_item_count() ; i++)
      {

         auto & itemrange = range.ItemAt(i);

         for(index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            if(iItem >= 0 && iItem <= wstraTotal.get_upper_bound())
            {

               stra.add(wstraTotal[iItem]);

            }

         }

      }

   }


   ::count folder_list_data::_001GetItemCount()
   {

      string_array straTotal;

      if (!data_get(::id(), straTotal))
      {

         return 0;

      }

      return straTotal.get_size();

   }


   bool folder_list_data::add_unique(const string_array & stra, i32_array & baRecursive)
   {

      string_array straData;

      data_get(::id(), straData);

      i32_array iaData;
      data_get("recursive", iaData);

      for(i32 i = 0; i < stra.get_count(); i++)
      {

         if(!straData.contains(stra[i]))
         {

            straData.add(stra[i]);

            if(i <= baRecursive.get_upper_bound())
            {

               iaData.add(baRecursive[i]);

            }

         }

      }

      while(iaData.get_size() < straData.get_size())
      {

         iaData.add(true); // default bred, broad, expansive

      }

      while(iaData.get_size() > straData.get_size())
      {

         iaData.erase_last();

      }

      if (!data_set(::id(), straData))
      {

         return false;

      }

      try
      {

         data_get("recursive", iaData);

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   bool folder_list_data::erase(const string_array & stra)
   {

      string_array straData;

      if (!data_get(::id(), straData))
      {

         return true;

      }

      i32_array iaData;

      data_get("recursive", iaData);

      index iFind;

      for(i32 i = 0; i < stra.get_count(); i++)
      {

         while((iFind = straData.find_first(stra[i])) >= 0)
         {

            straData.erase_at(iFind);

            if(iFind < iaData.get_size())
            {

               iaData.erase_at(iFind);

            }

         }

      }

      while(iaData.get_size() < straData.get_size())
      {

         iaData.add(true); // default bred, broad, expansive

      }

      while(iaData.get_size() > straData.get_size())
      {

         iaData.erase_last();

      }

      if (!data_set(::id(), straData))
      {

         return false;

      }

      try
      {

         data_set("recursive", iaData);

      }
      catch(...)
      {
         return false;
      }

      return true;

   }


} // namespace filemanager



