#include "framework.h"
#include "database.h"
#include "transaction.h"


namespace database
{


   database::database()
   {

      defer_create_synchronization();

   }

   database::~database()
   {
      disconnect();

   }


   void database::start_transaction()
   {


   }


   void database::commit_transaction()
   {


   }


   void database::rollback_transaction()
   {


   }

   //void     database::connect(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrHost, const ::scoped_string & scopedstrPort, const ::scoped_string & scopedstrUser, const ::scoped_string & scopedstrPass, const ::scoped_string & scopedstrSocket, unsigned long long uConnectionFlags)
   //{



   //   return _connect();

   //}


   //bool database::exec(const ::scoped_string & scopedstrQuery)
   //{

   //   return false;

   //}


   //::payload database::query(const ::scoped_string & scopedstrQuery, ::collection::count iMaxRowCount, ::collection::count iMaxColumnCount)
   //{

   //   return query_rows(scopedstrQuery);

   //}


   //string database::escape(const ::scoped_string & scopedstr)
   //{

   //   return psz;

   //}


  /* ::collection::count database::get_affected_rows_count()
   {

      return -1;

   }*/


   //string database::error1(const ::scoped_string & scopedstrPrefix)
   //{

   //   return string(scopedstrPrefix) + " (error)";

   //}

   //void database::trace_error1(const ::scoped_string & scopedstrPrefix)
   //{
   //   //m_pdatabase->add_error_message(error1(scopedstrPrefix));
   //   //informationf("%s", m_strLastError.c_str());
   //}


   //void     database::init()
   //{

   //   return ::success;

   //}


   //void     database::set_error_code(int iErrorCode)
   //{

   //   m_iLastError = iErrorCode;

   //   return ::success;

   //}

   ::pointer<result_set>database::query(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {

      return query_result(scopedstrQuery, iRowCount, iColumnCount);

   }

   void database::disconnect()
   {


   }

   //string database::get_error_message()

   //{

   //   return m_strError;

   //}


   //::pointer<row_array>database::query_rows(const ::scoped_string & scopedstrQuery)
   //{

   //   auto pset = query_result(scopedstrQuery);

   //   if (pset.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return pset->m_prowa;

   //}


   //::pointer<row>database::query_row(const ::scoped_string & scopedstrQuery)
   //{

   //   auto pset = query_result(scopedstrQuery, 1);

   //   if (pset.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return pset->m_prowa->element_at(0);

   //}


   //::pointer<payload_array>database::query_items(const ::scoped_string & scopedstrQuery)
   //{

   //   auto pset = query_result(scopedstrQuery, -1, 1);

   //   if (pset.is_null())
   //   {

   //      return nullptr;

   //   }

   //   auto pvara = __allocate payload_array();

   //   for (::collection::index i = 0; i < pset->m_prowa->get_count(); i++)
   //   {

   //      pvara->add((const ::payload &) pset->m_prowa->element_at(i));

   //   }

   //   return pvara;

   //}


   //::payload database::query_item(const ::scoped_string & scopedstrQuery)
   //{

   //   auto pset = query_result(scopedstrQuery, 1, 1);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   return pset->m_prowa->element_at(0)->element_at(0);

   //}


   //bool database::memory_query_item(get_memory getmemory, const ::scoped_string & scopedstrQuery)
   //{

   //   ::payload item = query_item(scopedstrQuery);

   //   if (!item)
   //   {

   //      return false;

   //   }

   //   return getmemory.get_base64(item.get_string());

   //}

/*
   bool database::query_rows(::pointer<row_array>& rows, const ::scoped_string & scopedstrQuery)
   {

      auto pset = query_result(scopedstrQuery);

      if (pset.is_null())
      {

         return false;

      }

      rows = pset->m_prowa;

      return true;

   }


   bool database::query_row(::pointer<row>& row, const ::scoped_string & scopedstrQuery)
   {

      auto pset = query_result(scopedstrQuery);

      if (pset.is_null())
      {

         return false;

      }

      row = pset->m_prowa->element_at(0);

      return true;

   }*/

   ::pointer<::database::result_set>database::query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {

      return nullptr;

   }


   //bool database::query_items(::pointer<payload_array>& pitems, const ::scoped_string & scopedstrQuery)
   //{

   //   auto pset = query_result(scopedstrQuery);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   pitems.create(this);

   //   pitems->set_size(pset->m_prowa->get_size());

   //   for (::collection::index iRow = 0; iRow < pitems->get_size(); iRow++)
   //   {

   //      pitems->element_at(iRow) = pset->m_prowa->element_at(iRow)->element_at(0);

   //   }

   //   return true;

   //}


   //bool database::query_item(::payload & item, const ::scoped_string & scopedstrQuery)
   //{

   //   auto pset = query_result(scopedstrQuery, 1);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   item = pset->m_prowa->element_at(0)->element_at(0);

   //   return true;

   //}


   ::payload database::query_table_item(const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where, const ::payload& payloadDefault)
   {

      ::payload payload;

      if (!query_table_item(payload, table, scopedstrItem, where))
      {

         return payloadDefault;

      }

      return payload;

   }



   ::pointer<row_array>database::query_rows(const ::scoped_string & scopedstrQuery)
   {

      ::pointer<row_array>prowarray;

      if (!query_rows(prowarray, scopedstrQuery))
      {

         return nullptr;

      }

      return prowarray;
   }


   ::pointer<row>database::query_row(const ::scoped_string & scopedstrQuery)
   {

      ::pointer<row>prow;

      if (!query_row(prow, scopedstrQuery))
      {

         return nullptr;

      }

      return prow;
   }


   ::pointer<payload_array>database::query_items(const ::scoped_string & scopedstrQuery)
   {

      ::pointer<payload_array>pvara;


      if (!query_items(pvara, scopedstrQuery))
      {

         return nullptr;

      }

      return pvara;

   }   
   
   
   ::payload database::query_item(const ::scoped_string & scopedstrQuery, const ::payload &  payloadDefault)
   {

      ::payload payload;

      if (!query_item(payload,scopedstrQuery))
      {

         return payloadDefault;

      }

      return payload;

   }


   bool database::query_table_item(::payload& payload, const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where)
   {

      string strSql;

      strSql.formatf("SELECT `%s` FROM `%s` WHERE %s",scopedstrItem.c_str(), table.c_str(), where.c_str());

      return database::query_item(payload, strSql);

   }





   bool database::query_blob(get_memory getmemory, const ::scoped_string & scopedstrQuery)
   {

      return false;

   }


   bool database::query_rows(::pointer<row_array> & rows, const ::scoped_string & scopedstrQuery)
   {


      return false;
   }


   bool database::query_row(::pointer<row> & rows, const ::scoped_string & scopedstrQuery)
   {

      return false;

   }


   bool database::query_items(::pointer<payload_array> & items, const ::scoped_string & scopedstrQuery)
   {

      return false;

   }


   bool database::query_item(::payload& item, const ::scoped_string & scopedstrQuery)
   {

      return false;

   }





   //bool database::database(::pointer<row_array> rows, const ::scoped_string & scopedstrQuery);
   //bool database::query_row(::pointer<row> rows, const ::scoped_string & scopedstrQuery);
   //bool database::query_items(::pointer<payload_array> items, const ::scoped_string & scopedstrQuery);
   //bool database::uery_item(::payload& item, const ::scoped_string & scopedstrQuery);



   string database::add_error_message(const ::scoped_string & scopedstrErrorMessage)
   {


      return "";

   }


   string database::query_error(const ::scoped_string & scopedstrPrefix)
   {

      return scopedstrPrefix + " (error)";

   }


   void database::trace_error1(const ::scoped_string & scopedstrPrefix)
   {

     //m_strLastError += error1(scopedstrPrefix);
     //informationf("%s", m_strLastError.c_str());

   }

   ::pointer<transaction>database::transaction()
   {

      return __allocate class transaction (this);

   }


   //::payload database::query_table_item(const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where, ::payload notfound)
   //{

   //   return ::payload();

   //}


   void database::set_id_blob(string strKey, ::block block)
   {

   }


   bool database::get_id_blob(string strKey, ::get_memory getmemory)
   {

      return false;

   }


} // namespace database



