#include "framework.h"

namespace database
{


   database::database()
   {

      defer_create_mutex();

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

   //void     database::connect(const ::string & name, const ::string & host, const ::string & port, const ::string & user, const ::string & pass, const ::string & sckt, u64 uConnectionFlags)
   //{



   //   return _connect();

   //}


   //bool database::exec(const ::string & pszQuery)
   //{

   //   return false;

   //}


   //::payload database::query(const ::string & pszQuery, ::count iMaxRowCount, ::count iMaxColumnCount)
   //{

   //   return query_rows(pszQuery);

   //}


   //string database::escape(const ::string & psz)
   //{

   //   return psz;

   //}


  /* ::count database::get_affected_rows_count()
   {

      return -1;

   }*/


   //string database::error1(const ::string & pszPrefix)
   //{

   //   return string(pszPrefix) + " (error)";

   //}

   //void database::trace_error1(const ::string & pszPrefix)
   //{
   //   //m_pdatabase->add_error_message(error1(pszPrefix));
   //   //FORMATTED_TRACE("%s", m_strLastError.c_str());
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

   __pointer(result_set) database::query(const ::string & pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return query_result(pszQuery, iRowCount, iColumnCount);

   }

   void database::disconnect()
   {


   }

   //string database::get_error_message()

   //{

   //   return m_strError;

   //}


   //__pointer(row_array) database::query_rows(const ::string & pszQuery)
   //{

   //   auto pset = query_result(pszQuery);

   //   if (pset.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return pset->m_prowa;

   //}


   //__pointer(row) database::query_row(const ::string & pszQuery)
   //{

   //   auto pset = query_result(pszQuery, 1);

   //   if (pset.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return pset->m_prowa->element_at(0);

   //}


   //__pointer(payload_array) database::query_items(const ::string & pszQuery)
   //{

   //   auto pset = query_result(pszQuery, -1, 1);

   //   if (pset.is_null())
   //   {

   //      return nullptr;

   //   }

   //   auto pvara = __new(payload_array);

   //   for (index i = 0; i < pset->m_prowa->get_count(); i++)
   //   {

   //      pvara->add((const ::payload &) pset->m_prowa->element_at(i));

   //   }

   //   return pvara;

   //}


   //::payload database::query_item(const ::string & pszQuery)
   //{

   //   auto pset = query_result(pszQuery, 1, 1);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   return pset->m_prowa->element_at(0)->element_at(0);

   //}


   //bool database::memory_query_item(get_memory getmemory, const ::string & pszQuery)
   //{

   //   ::payload item = query_item(pszQuery);

   //   if (!item)
   //   {

   //      return false;

   //   }

   //   return getmemory.get_base64(item.get_string());

   //}

/*
   bool database::query_rows(__pointer(row_array) & rows, const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return false;

      }

      rows = pset->m_prowa;

      return true;

   }


   bool database::query_row(__pointer(row) & row, const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return false;

      }

      row = pset->m_prowa->element_at(0);

      return true;

   }*/

   __pointer(::database::result_set) database::query_result(const ::string & pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return nullptr;

   }


   //bool database::query_items(__pointer(payload_array) & pitems, const ::string & pszQuery)
   //{

   //   auto pset = query_result(pszQuery);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   pitems.create(this);

   //   pitems->set_size(pset->m_prowa->get_size());

   //   for (index iRow = 0; iRow < pitems->get_size(); iRow++)
   //   {

   //      pitems->element_at(iRow) = pset->m_prowa->element_at(iRow)->element_at(0);

   //   }

   //   return true;

   //}


   //bool database::query_item(::payload & item, const ::string & pszQuery)
   //{

   //   auto pset = query_result(pszQuery, 1);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   item = pset->m_prowa->element_at(0)->element_at(0);

   //   return true;

   //}


   ::payload database::query_table_item(const ::string & table, const ::string & item, const ::string & where, const ::payload& payloadDefault)
   {

      ::payload payload;

      if (!query_table_item(payload, table, item, where))
      {

         return payloadDefault;

      }

      return payload;

   }



   __pointer(row_array) database::query_rows(const ::string & pszQuery)
   {

      __pointer(row_array) prowarray;

      if (!query_rows(prowarray, pszQuery))
      {

         return nullptr;

      }

      return prowarray;
   }


   __pointer(row) database::query_row(const ::string & pszQuery)
   {

      __pointer(row) prow;

      if (!query_row(prow, pszQuery))
      {

         return nullptr;

      }

      return prow;
   }


   __pointer(payload_array) database::query_items(const ::string & pszQuery)
   {

      __pointer(payload_array) pvara;


      if (!query_items(pvara, pszQuery))
      {

         return nullptr;

      }

      return pvara;

   }   
   
   
   ::payload database::query_item(const ::string & pszQuery, const ::payload &  payloadDefault)
   {

      ::payload payload;

      if (!query_item(payload, pszQuery))
      {

         return payloadDefault;

      }

      return payload;

   }


   bool database::query_table_item(::payload& payload, const ::string & table, const ::string & item, const ::string & where)
   {

      string strSql;

      strSql.format("SELECT `%s` FROM `%s` WHERE %s", item.c_str(), table.c_str(), where.c_str());

      return database::query_item(payload, strSql);

   }





   bool database::query_blob(get_memory getmemory, const ::string & pszQuery)
   {

      return false;

   }


   bool database::query_rows(__pointer(row_array)& rows, const ::string & pszQuery)
   {


      return false;
   }


   bool database::query_row(__pointer(row)& rows, const ::string & pszQuery)
   {

      return false;

   }


   bool database::query_items(__pointer(payload_array)& items, const ::string & pszQuery)
   {

      return false;

   }


   bool database::query_item(::payload& item, const ::string & pszQuery)
   {

      return false;

   }





   //bool database::database(__pointer(row_array)& rows, const ::string & pszQuery);
   //bool database::query_row(__pointer(row)& rows, const ::string & pszQuery);
   //bool database::query_items(__pointer(payload_array)& items, const ::string & pszQuery);
   //bool database::uery_item(::payload& item, const ::string & pszQuery);



   string database::add_error_message(const ::string& strErrorMessage)
   {


      return "";

   }


   string database::query_error(const ::string & strPrefix)
   {

      return strPrefix + " (error)";

   }


   void database::trace_error1(const ::string & pszPrefix)
   {

     //m_strLastError += error1(pszPrefix);
     //FORMATTED_TRACE("%s", m_strLastError.c_str());

   }

   __pointer(transaction) database::transaction()
   {

      return __new(class transaction(this));

   }


   //::payload database::query_table_item(const ::string & table, const ::string & item, const ::string & where, ::payload notfound)
   //{

   //   return ::payload();

   //}


   void database::set_id_blob(string strKey, ::block block)
   {

   }


   void database::get_id_blob(string strKey, ::get_memory getmemory)
   {

   }


} // namespace database



