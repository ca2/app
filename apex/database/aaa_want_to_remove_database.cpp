#include "framework.h"

namespace database
{

   database::database()
   {

      m_bActive = false;

      defer_create_mutex();

   }

   database::~database()
   {
      disconnect();

   }


   ::e_status     database::connect(const char * name, const char * host, const char * port,const char * user, const char * pass, const char * sckt, u64 uConnectionFlags)
   {

      m_strHost = host;
      m_strPort = port;
      m_strName = name;
      m_strUser = user;
      m_strPass = pass;
      m_strSckt = sckt;
      m_uConnectionFlags = uConnectionFlags;

      return _connect();

   }


   bool database::exec(const char * pszQuery)
   {

      return false;

   }


   //payload database::query(const char * pszQuery, ::count iMaxRowCount, ::count iMaxColumnCount)
   //{

   //   return query_rows(pszQuery);

   //}


   string database::escape(const char * psz)
   {

      return psz;

   }


   ::count database::get_affected_rows_count()
   {

      return -1;

   }


   string database::error1(const char * pszPrefix)
   {

      return string(pszPrefix) + " (error)";

   }

   void database::trace_error1(const char * pszPrefix)
   {
      m_strLastError += error1(pszPrefix);
      TRACE("%s", m_strLastError.c_str());
   }


   ::e_status     database::init()
   {

      return ::success;

   }


   ::e_status     database::set_error_code(int iErrorCode)
   {

      m_iLastError = iErrorCode;

      return ::success;

   }


   string database::get_error_message()
   {

      return m_strError;

   }


   __pointer(row_array) database::query_rows(const char * pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa;

   }


   __pointer(row) database::query_row(const char * pszQuery)
   {

      auto pset = query_result(pszQuery, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa->element_at(0);

   }


   __pointer(var_array) database::query_items(const char * pszQuery)
   {

      auto pset = query_result(pszQuery, -1, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      auto pvara = __new(var_array);

      for (index i = 0; i < pset->m_prowa->get_count(); i++)
      {

         pvara->add((const payload &) pset->m_prowa->element_at(i));

      }

      return pvara;

   }


   payload database::query_item(const char * pszQuery)
   {

      auto pset = query_result(pszQuery, 1, 1);

      if (pset.is_null())
      {

         return false;

      }

      return pset->m_prowa->element_at(0)->element_at(0);

   }


   bool database::memory_query_item(get_memory getmemory, const char * pszQuery)
   {

      payload item = query_item(pszQuery);

      if (!item)
      {

         return false;

      }

      return getmemory.get_base64(item.get_string());

   }

/*
   bool database::query_rows(__pointer(row_array) & rows, const char * pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return false;

      }

      rows = pset->m_prowa;

      return true;

   }


   bool database::query_row(__pointer(row) & row, const char * pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return false;

      }

      row = pset->m_prowa->element_at(0);

      return true;

   }*/

   __pointer(::database::result_set) database::query_result(const char * pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return nullptr;

   }


   //bool database::query_items(__pointer(var_array) & pitems, const char * pszQuery)
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


   //bool database::query_item(payload & item, const char * pszQuery)
   //{

   //   auto pset = query_result(pszQuery, 1);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   item = pset->m_prowa->element_at(0)->element_at(0);

   //   return true;

   //}


   transaction::transaction(database * pdatabase) :
      m_pdatabase(pdatabase),
      m_bProcessed (false)
   {
      pdatabase->start_transaction();
   }
   transaction::~transaction()
   {

      rollback();

   }

   void transaction::commit()
   {
      if (!m_bProcessed)
      {
         m_bProcessed = true;
         m_pdatabase->commit_transaction();

      }
   }
   void transaction::rollback()
   {
      if (!m_bProcessed)
      {
         m_bProcessed = true;
         m_pdatabase->rollback_transaction();

      }
   }


} // namespace database



