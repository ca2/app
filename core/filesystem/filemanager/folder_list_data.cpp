#include "framework.h"
#include "folder_list_data.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "acme/primitive/data/listener.h"
#include "apex/database/_binary_stream.h"
#include "apex/platform/application.h"
#include "core/user/user/list.h"


namespace filemanager
{


   folder_list_data::folder_list_data()
   {

      defer_create_synchronization();

   }


   folder_list_data::~folder_list_data()
   {

   }


   void folder_list_data::on_initialize_particle()
   {

      //auto estatus = 
      
      ::user::list_data::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      ::database::client::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto papp = get_app();

      initialize_data_client(papp->m_papexapplication->dataserver());

      //return estatus;

   }


   void folder_list_data::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if(psubitem->m_iSubItem == 0)
      {

         string_array stra;

         if(!datastream()->get(::atom(), stra))
         {

            psubitem->m_bOk = false;

            return;

         }

         psubitem->m_strText = stra[psubitem->m_pitem->m_iItem];

         psubitem->m_bOk = true;

      }
      else if(psubitem->m_iSubItem == 1)
      {

         psubitem->m_bOk = false;

      }

   }


   void folder_list_data::GetSel(::user::list * plist, string_array & stra)
   {

      synchronous_lock synchronouslock(this->synchronization());

      string_array wstraTotal;

      if (!datastream()->get(::atom(), wstraTotal))
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

      synchronous_lock synchronouslock(this->synchronization());

      string_array straTotal;

      if (!datastream()->get(::atom(), straTotal))
      {

         return 0;

      }

      return straTotal.get_size();

   }


   bool folder_list_data::add_unique(const string_array& stra)
   {

      synchronous_lock synchronouslock(this->synchronization());

      string_array straFolderPath;

      datastream()->get(::atom(), straFolderPath);

      for (i32 i = 0; i < stra.get_count(); i++)
      {

         if (!straFolderPath.contains(stra[i]))
         {

            straFolderPath.add(stra[i]);

         }

      }

      datastream()->set(::atom(), straFolderPath);

      //if (!datastream()->set(::atom(), straFolderPath))
      //{

      //   return false;

      //}

      return true;

   }


   bool folder_list_data::add_unique(const string_array & stra, i32_array & baRecursive)
   {

      synchronous_lock synchronouslock(this->synchronization());

      string_array straFolderPath;

      datastream()->get(::atom(), straFolderPath);

      i32_array iaRecursive;

      datastream()->get("recursive", iaRecursive);

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

      datastream()->set(::atom(), straFolderPath);

      //if (!datastream()->set(::atom(), straFolderPath))
      //{

      //   return false;

      //}

      try
      {

         datastream()->set("recursive", iaRecursive);

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   bool folder_list_data::erase(const string_array & stra)
   {

      synchronous_lock synchronouslock(this->synchronization());

      string_array straFolderPath;

      if (!datastream()->get(::atom(), straFolderPath))
      {

         return true;

      }

      i32_array iaRecursive;

      datastream()->get("recursive", iaRecursive);

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

      datastream()->set(::atom(), straFolderPath);

      //if (!datastream()->set(::atom(), straFolderPath))
      //{

      //   return false;

      //}

      try
      {

         datastream()->set("recursive", iaRecursive);

      }
      catch(...)
      {
         return false;
      }

      return true;

   }


   bool folder_list_data::set_recursive(::index iItem, bool bRecursive)
   {

      synchronous_lock synchronouslock(this->synchronization());

      i32_array iaRecursive;

      try
      {

         datastream()->get("recursive", iaRecursive);

      }
      catch (...)
      {

      }

      iaRecursive.set_at_grow(iItem, bRecursive ? 1 : 0);

      try
      {

         datastream()->set("recursive", iaRecursive);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool folder_list_data::get_recursive(::index iItem)
   {

      synchronous_lock synchronouslock(this->synchronization());

      i32_array iaRecursive;

      try
      {

         datastream()->get("recursive", iaRecursive);

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



