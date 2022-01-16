#include "framework.h"
#include "core/user/databaseuser/_databaseuser.h"


namespace databaseuser
{


   data_key_mesh_data::data_key_mesh_data()
   {
   }

   data_key_mesh_data::~data_key_mesh_data()
   {
   }


   void data_key_mesh_data::assert_valid() const
   {

   }


   void data_key_mesh_data::dump(dump_context& dumpcontext) const
   {

   }


   void data_key_mesh_data::_001GetItemText(::user::mesh_item * pitem)
   {
      string_array stra;
      if(!data_get(::id(), stra))
         return_(pitem->m_bOk, false)
         pitem->m_strText = stra[pitem->m_iItem];
      pitem->m_bOk = true;
   }

   void data_key_mesh_data::GetSel(::user::list * plist, string_array & stra)
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
            stra.add(wstraTotal[iItem]);
         }
      }
   }

   ::count data_key_mesh_data::_001GetItemCount()
   {
      string_array straTotal;
      if(!data_get(::id(), straTotal))
         return -1;
      return straTotal.get_size();
   }


   bool data_key_mesh_data::add_unique(const string_array & stra)
   {
      string_array straData;
      data_get(::id(), straData);
      straData.add_unique(stra);
      data_set(::id(), straData);
      //if(!data_set(::id(), straData))
         //return false;
      return true;
   }

   bool data_key_mesh_data::erase(const string_array & stra)
   {
      string_array straData;
      if(!data_get(::id(), straData))
         return true;
      straData.erase(stra);
      data_set(::id(), straData);
         //return false;
      return true;
   }


} // namespace databaseuser



