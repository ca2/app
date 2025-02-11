#include "framework.h"
#include "database_impl.h"
#include "result_set.h"


namespace database
{


   database_impl::database_impl()
   {

      m_bActive = false;

      defer_create_synchronization();

   }

   database_impl::~database_impl()
   {
      disconnect();

   }


   void database_impl::connect(const ::string & name, const ::string & host, const ::string & port, const ::string & user, const ::string & pass, const ::string & sckt, unsigned long long uConnectionFlags)
   {

      m_strHost = host;
      m_strPort = port;
      m_strName = name;
      m_strUser = user;
      m_strPass = pass;
      m_strSckt = sckt;
      m_uConnectionFlags = uConnectionFlags;

      _connect();

   }

   void database_impl::disconnect()
   {


   }


   void database_impl::reset()
   {

      //return ::success;

   }


   void database_impl::create()
   {

      //return ::success;

   }


   void database_impl::drop()
   {

      //return ::success;

   }


   bool database_impl::exec(const ::string & pszQuery)
   {

      return false;

   }


   //::payload database_impl::query(const ::string & pszQuery, ::collection::count iMaxRowCount, ::collection::count iMaxColumnCount)
   //{

   //   return query_rows(pszQuery);

   //}


   string database_impl::escape(const ::string & psz)
   {

      return psz;

   }


   ::collection::count database_impl::get_affected_rows_count()
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
   
      informationf("%s", m_strLastError.c_str());

   }


   void database_impl::init()
   {

      //return ::success;

   }


   void database_impl::set_error_code(int iErrorCode)
   {

      m_iLastError = iErrorCode;

   }


   string database_impl::get_error_message()
   {

      return m_strError;

   }


   ::pointer<row_array>database_impl::query_rows(const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa;

   }


   ::pointer<row>database_impl::query_row(const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa->element_at(0);

   }


   ::pointer<payload_array>database_impl::query_items(const ::string & pszQuery)
   {

      auto pset = query_result(pszQuery, -1, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      auto pvara = __allocate payload_array();

      for (::collection::index i = 0; i < pset->m_prowa->get_count(); i++)
      {

         pvara->add((const ::payload&)pset->m_prowa->element_at(i)->element_at(0));

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
      bool database_impl::query_rows(::pointer<row_array>& rows, const ::string & pszQuery)
      {

         auto pset = query_result(pszQuery);

         if (pset.is_null())
         {

            return false;

         }

         rows = pset->m_prowa;

         return true;

      }


      bool database_impl::query_row(::pointer<row>& row, const ::string & pszQuery)
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


   ::pointer<::database::result_set>database_impl::query_result(const ::string & pszQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {

      return nullptr;

   }


   //bool database_impl::query_items(::pointer<payload_array>& pitems, const ::string & pszQuery)
   //{

   //   auto pset = query_result(pszQuery);

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



