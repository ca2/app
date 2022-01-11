#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


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


   void folder_list_data::on_initialize_object()
   {

      auto estatus = ::user::list_data::on_initialize_object();

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::database::client::on_initialize_object();

      if (!estatus)
      {

         return estatus;

      }

      auto papplication = get_application();

      initialize_data_client(papplication->dataserver());

      return estatus;

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

         pitem->m_bOk = true;

      }
      else if(pitem->m_iSubItem == 1)
      {

         pitem->m_bOk = false; 

      }

   }


   void folder_list_data::GetSel(::user::list * plist, string_array & stra)
   {

      synchronous_lock synchronouslock(mutex());

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

      synchronous_lock synchronouslock(mutex());

      string_array straTotal;

      if (!data_get(::id(), straTotal))
      {

         return 0;

      }

      return straTotal.get_size();

   }


   bool folder_list_data::add_unique(const string_array& stra)
   {

      synchronous_lock synchronouslock(mutex());

      string_array straFolderPath;

      data_get(::id(), straFolderPath);

      for (i32 i = 0; i < stra.get_count(); i++)
      {

         if (!straFolderPath.contains(stra[i]))
         {

            straFolderPath.add(stra[i]);

         }

      }

      if (!data_set(::id(), straFolderPath))
      {

         return false;

      }

      return true;

   }


   bool folder_list_data::add_unique(const string_array & stra, i32_array & baRecursive)
   {

      synchronous_lock synchronouslock(mutex());

      string_array straFolderPath;

      data_get(::id(), straFolderPath);

      i32_array iaRecursive;

      data_get("recursive", iaRecursive);

      for(i32 i = 0; i < stra.get_count(); i++)
      {

         if(!straFolderPath.contains(stra[i]))
         {

            auto iNew = straFolderPath.add(stra[i]);

            bool bRecursive = false;

            if(i <= baRecursive.get_upper_bound())
            {

               bRecursive = baRecursive[i];

            }

            iaRecursive.set_at_grow(iNew, bRecursive);

         }

      }

      if (!data_set(::id(), straFolderPath))
      {

         return false;

      }

      try
      {

         data_set("recursive", iaRecursive);

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   bool folder_list_data::erase(const string_array & stra)
   {

      synchronous_lock synchronouslock(mutex());

      string_array straFolderPath;

      if (!data_get(::id(), straFolderPath))
      {

         return true;

      }

      i32_array iaRecursive;

      data_get("recursive", iaRecursive);

      index iFind;

      for(i32 i = 0; i < stra.get_count(); i++)
      {

         while((iFind = straFolderPath.find_first(stra[i])) >= 0)
         {

            straFolderPath.erase_at(iFind);

            if(iFind < iaRecursive.get_size())
            {

               iaRecursive.erase_at(iFind);

            }

         }

      }

      while(iaRecursive.get_size() < straFolderPath.get_size())
      {

         iaRecursive.add(true); // default bred, broad, expansive

      }

      while(iaRecursive.get_size() > straFolderPath.get_size())
      {

         iaRecursive.erase_last();

      }

      if (!data_set(::id(), straFolderPath))
      {

         return false;

      }

      try
      {

         data_set("recursive", iaRecursive);

      }
      catch(...)
      {
         return false;
      }

      return true;

   }


   bool folder_list_data::set_recursive(::index iItem, bool bRecursive)
   {

      synchronous_lock synchronouslock(mutex());

      i32_array iaRecursive;

      try
      {

         data_get("recursive", iaRecursive);

      }
      catch (...)
      {

      }

      iaRecursive.set_at_grow(iItem, bRecursive ? 1 : 0);

      try
      {

         data_set("recursive", iaRecursive);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool folder_list_data::get_recursive(::index iItem)
   {

      synchronous_lock synchronouslock(mutex());

      i32_array iaRecursive;

      try
      {

         data_get("recursive", iaRecursive);

      }
      catch (...)
      {

         return false;

      }

      if(iItem < 0 || iItem >= iaRecursive.get_size())
      {
      
         return false;
      
      }

      auto iData = iaRecursive[iItem];

      return iData != 0 ? true : false;

   }


} // namespace filemanager



