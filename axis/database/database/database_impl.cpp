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


   void     database_impl::connect(const ::string & name, const ::string & host, const ::string & port, const ::string & user, const ::string & pass, const ::string & sckt, u64 uConnectionFlags)
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


   void    database_impl::reset()
   {

      return ::success;

   }


   void    database_impl::create()
   {

      return ::success;

   }


   void   database_impl::drop()
   {

      return ::success;

   }


   bool database_impl::exec(const ::string & pszQuery)
   {

      return false;

   }


   //::payload database_impl::query(const ::string & pszQuery, ::count iMaxRowCount, ::count iMaxColumnCount)
   //{

   //   return query_rows(pszQuery);

   //}


   string database_impl::escape(const ::string & psz)
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

   
   string database_impl::query_error(const ::string & pszPrefix)
   {

      return string(pszPrefix) + " (error)";

   }

   void database_impl::trace_error1(const ::string & pszPrefix)
   {
      m_strLastError += query_error(pszPrefix);
   
      FORMATTED_TRACE("%s", m_strLastError.c_str());

   }


   void     database_impl::init()
   {

      return ::success;

   }


   void     database_impl::set_error_code(int iErrorCode)
   {

      m_iLastError = iErrorCode;

      return ::success;

   }


   string database_impl::get_error_message()
   {

      return m_strError;

   }


   __pointer(row_array) database_impl::query_rows(const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa;

   }


   __pointer(row) database_impl::query_row(const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa->element_at(0);

   }


   __pointer(payload_array) database_impl::query_items(const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery, -1, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      auto pvara = __new(payload_array);

      for (index i = 0; i < pset->m_prowa->get_count(); i++)
      {

         pvara->add((const ::payload&)pset->m_prowa->element_at(i));

      }

      return pvara;

   }


   bool database_impl::query_blob(get_memory getmemory, const ::string & pszQuery)
   {

      return false;

   }


   ::payload database_impl::query_item(const ::string & pszQuery, const ::payload & payloadDefault)
   {

      auto pset = query_result(pszQuery, 1, 1);

      if (pset.is_null())
      {

         return payloadDefault;

      }

      return pset->m_prowa->element_at(0)->element_at(0);

   }


   /*
      bool database_impl::query_rows(__pointer(row_array) & rows, const ::string & pszQuery)
      {

         auto pset = query_result(pszQuery);

         if (pset.is_null())
         {

            return false;

         }

         rows = pset->m_prowa;

         return true;

      }


      bool database_impl::query_row(__pointer(row) & row, const ::string & pszQuery)
      {

         auto pset = query_result(pszQuery);

         if (pset.is_null())
         {

            return false;

         }

         row = pset->m_prowa->element_at(0);

         return true;

      }*/




   ::payload database_impl::get_agent(const ::string & pszTable, const ::string & psz, const ::string & pszUser)
   {

      return ::payload(::e_type_null);

   }


   __pointer(::database::result_set) database_impl::query_result(const ::string & pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return nullptr;

   }


   //bool database_impl::query_items(__pointer(payload_array) & pitems, const ::string & pszQuery)
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


   //bool database_impl::query_item(::payload & item, const ::string & pszQuery)
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



