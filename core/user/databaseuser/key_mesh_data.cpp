#include "framework.h"
#include "key_mesh_data.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "acme/primitive/data/listener.h"
#include "apex/database/_binary_stream.h"
#include "core/user/user/list.h"


namespace databaseuser
{


   data_key_mesh_data::data_key_mesh_data()
   {
   }

   data_key_mesh_data::~data_key_mesh_data()
   {
   }


//   void data_key_mesh_data::assert_ok() const
//   {
//
//   }
//
//
//   void data_key_mesh_data::dump(dump_context& dumpcontext) const
//   {
//
//   }


   void data_key_mesh_data::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      string_array stra;

      if (!datastream()->get(::atom(), stra))
      {

         return_(psubitem->m_bOk, false)

      }

      psubitem->m_strText = stra[psubitem->m_pitem->m_iItem];

      psubitem->m_bOk = true;

   }


   void data_key_mesh_data::GetSel(::user::list * plist, string_array & stra)
   {
      
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
            stra.add(wstraTotal[iItem]);
         }
      }
   }

   ::count data_key_mesh_data::_001GetItemCount()
   {
      string_array straTotal;
      if(!datastream()->get(::atom(), straTotal))
         return -1;
      return straTotal.get_size();
   }


   bool data_key_mesh_data::add_unique(const string_array & stra)
   {
      string_array straData;
      datastream()->get(::atom(), straData);
      straData.append_unique(stra);
      datastream()->set(::atom(), straData);
      //if(!datastream()->set(::atom(), straData))
         //return false;
      return true;
   }

   bool data_key_mesh_data::erase(const string_array & stra)
   {
      string_array straData;
      if(!datastream()->get(::atom(), straData))
         return true;
      straData.erase(stra);
      datastream()->set(::atom(), straData);
         //return false;
      return true;
   }


} // namespace databaseuser



