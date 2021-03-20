#include "framework.h"


namespace database
{


   database_impl::database_impl()
   {

      m_bActive = false;

      defer_create_mutex();

   }

   database_impl::~database_impl()
   {
      disconnect();

   }


   ::e_status     database_impl::connect(const char* name, const char* host, const char* port, const char* user, const char* pass, const char* sckt, u64 uConnectionFlags)
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

   void database_impl::disconnect()
   {


   }


   ::e_status    database_impl::reset()
   {

      return ::success;

   }


   ::e_status    database_impl::create()
   {

      return ::success;

   }


   ::e_status   database_impl::drop()
   {

      return ::success;

   }


   bool database_impl::exec(const char* pszQuery)
   {

      return false;

   }


   //::payload database_impl::query(const char * pszQuery, ::count iMaxRowCount, ::count iMaxColumnCount)
   //{

   //   return query_rows(pszQuery);

   //}


   string database_impl::escape(const char* psz)
   {

      return psz;

   }


   ::count database_impl::get_affected_rows_count()
   {

      return -1;

   }


   bool database_impl::in_transaction() 
   {
      
      return m_bTransactionActive; 
   
   }

   
   string database_impl::error1(const char* pszPrefix)
   {

      return string(pszPrefix) + " (error)";

   }

   void database_impl::trace_error1(const char* pszPrefix)
   {
      m_strLastError += error1(pszPrefix);
   TRACE("%s", m_strLastError.c_str());

   }


   ::e_status     database_impl::init()
   {

      return ::success;

   }


   ::e_status     database_impl::set_error_code(int iErrorCode)
   {

      m_iLastError = iErrorCode;

      return ::success;

   }


   string database_impl::get_error_message()
   {

      return m_strError;

   }


   __pointer(row_array) database_impl::query_rows(const char* pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa;

   }


   __pointer(row) database_impl::query_row(const char* pszQuery)
   {

      auto pset = query_result(pszQuery, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa->element_at(0);

   }


   __pointer(var_array) database_impl::query_items(const char* pszQuery)
   {

      auto pset = query_result(pszQuery, -1, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      auto pvara = __new(var_array);

      for (index i = 0; i < pset->m_prowa->get_count(); i++)
      {

         pvara->add((const ::payload&)pset->m_prowa->element_at(i));

      }

      return pvara;

   }


   ::payload database_impl::query_item(const char* pszQuery, const ::payload & payloadDefault)
   {

      auto pset = query_result(pszQuery, 1, 1);

      if (pset.is_null())
      {

         return payloadDefault;

      }

      return pset->m_prowa->element_at(0)->element_at(0);

   }


   bool database_impl::memory_query_item(get_memory getmemory, const char* pszQuery)
   {

      ::payload item = query_item(pszQuery);

      if (!item)
      {

         return false;

      }

      return getmemory.get_base64(item.get_string());

   }

   /*
      bool database_impl::query_rows(__pointer(row_array) & rows, const char * pszQuery)
      {

         auto pset = query_result(pszQuery);

         if (pset.is_null())
         {

            return false;

         }

         rows = pset->m_prowa;

         return true;

      }


      bool database_impl::query_row(__pointer(row) & row, const char * pszQuery)
      {

         auto pset = query_result(pszQuery);

         if (pset.is_null())
         {

            return false;

         }

         row = pset->m_prowa->element_at(0);

         return true;

      }*/




   ::payload database_impl::get_agent(const char* pszTable, const char* psz, const char* pszUser)
   {

      return ::payload(::e_type_null);

   }


   __pointer(::database::result_set) database_impl::query_result(const char* pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return nullptr;

   }


   //bool database_impl::query_items(__pointer(var_array) & pitems, const char * pszQuery)
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


   //bool database_impl::query_item(::payload & item, const char * pszQuery)
   //{

   //   auto pset = query_result(pszQuery, 1);

   //   if (pset.is_null())
   //   {

   //      return false;

   //   }

   //   item = pset->m_prowa->element_at(0)->element_at(0);

   //   return true;

   //}
   ::payload database_impl::get_insert_id()
   {

      return false;
      
   }


} // namespace database



