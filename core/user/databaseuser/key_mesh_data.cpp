#include "framework.h"
//#include "core/user/databaseuser/_databaseuser.h"
#include "core/user/user/list.h"
#include "key_mesh_data.h"


namespace databaseuser
{


   data_key_mesh_data::data_key_mesh_data()
   {
   }

   data_key_mesh_data::~data_key_mesh_data()
   {
   }


   void data_key_mesh_data::assert_ok() const
   {

   }


   void data_key_mesh_data::dump(dump_context& dumpcontext) const
   {

   }


   void data_key_mesh_data::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      string_array stra;

      if (!data_get(::atom(), stra))
      {

         return_(psubitem->m_bOk, false)

      }

      psubitem->m_strText = stra[psubitem->m_pitem->m_iItem];

      psubitem->m_bOk = true;

   }


   void data_key_mesh_data::GetSel(::user::list * plist, string_array & stra)
   {
      
      string_array wstraTotal;

      if (!data_get(::atom(), wstraTotal))
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
      if(!data_get(::atom(), straTotal))
         return -1;
      return straTotal.get_size();
   }


   bool data_key_mesh_data::add_unique(const string_array & stra)
   {
      string_array straData;
      data_get(::atom(), straData);
      straData.add_unique(stra);
      data_set(::atom(), straData);
      //if(!data_set(::atom(), straData))
         //return false;
      return true;
   }

   bool data_key_mesh_data::erase(const string_array & stra)
   {
      string_array straData;
      if(!data_get(::atom(), straData))
         return true;
      straData.erase(stra);
      data_set(::atom(), straData);
         //return false;
      return true;
   }


} // namespace databaseuser



