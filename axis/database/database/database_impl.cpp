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


   void database_impl::connect(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrHost, const ::scoped_string & scopedstrPort, const ::scoped_string & scopedstrUser, const ::scoped_string & scopedstrPass, const ::scoped_string & scopedstrSocket, unsigned long long uConnectionFlags)
   {

      m_strHost = scopedstrHost;
      m_strPort = scopedstrPort;
      m_strName = scopedstrName;
      m_strUser = scopedstrUser;
      m_strPass = scopedstrPass;
      m_strSckt = scopedstrSocket;
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


   bool database_impl::exec(const ::scoped_string & scopedstrQuery)
   {

      return false;

   }


   //::payload database_impl::query(const ::scoped_string & scopedstrQuery, ::collection::count iMaxRowCount, ::collection::count iMaxColumnCount)
   //{

   //   return query_rows(scopedstrQuery);

   //}


   string database_impl::escape(const ::scoped_string & scopedstr)
   {

      return scopedstr;

   }


   ::collection::count database_impl::get_affected_rows_count()
   {

      return -1;

   }


   bool database_impl::in_transaction() 
   {
      
      return m_bTransactionActive; 
   
   }

   
   string database_impl::query_error(const ::scoped_string & scopedstrPrefix)
   {

      return string(scopedstrPrefix) + " (error)";

   }


   void database_impl::trace_error1(const ::scoped_string & scopedstrPrefix)
   {

      m_strLastError += query_error(scopedstrPrefix);
   
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


   ::pointer<row_array>database_impl::query_rows(const ::scoped_string & scopedstrQuery)
   {

      auto pset = query_result(scopedstrQuery);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa;

   }


   ::pointer<row>database_impl::query_row(const ::scoped_string & scopedstrQuery)
   {

      auto pset = query_result(scopedstrQuery, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa->element_at(0);

   }


   ::pointer<payload_array>database_impl::query_items(const ::scoped_string & scopedstrQuery)
   {

      auto pset = query_result(scopedstrQuery, -1, 1);

      if (pset.is_null())
      {

         return nullptr;

      }

      auto pvara = øallocate payload_array();

      for (::collection::index i = 0; i < pset->m_prowa->get_count(); i++)
      {

         pvara->add((const ::payload&)pset->m_prowa->element_at(i)->element_at(0));

      }

      return pvara;

   }


   bool database_impl::query_blob(get_memory getmemory, const ::scoped_string & scopedstrQuery)
   {

      return false;

   }


   ::payload database_impl::query_item(const ::scoped_string & scopedstrQuery, const ::payload & payloadDefault)
   {

      auto pset = query_result(scopedstrQuery, 1, 1);

      if (pset.is_null())
      {

         return payloadDefault;

      }

      return pset->m_prowa->element_at(0)->element_at(0);

   }


   /*
      bool database_impl::query_rows(::pointer<row_array>& rows, const ::scoped_string & scopedstrQuery)
      {

         auto pset = query_result(scopedstrQuery);

         if (pset.is_null())
         {

            return false;

         }

         rows = pset->m_prowa;

         return true;

      }


      bool database_impl::query_row(::pointer<row>& row, const ::scoped_string & scopedstrQuery)
      {

         auto pset = query_result(scopedstrQuery);

         if (pset.is_null())
         {

            return false;

         }

         row = pset->m_prowa->element_at(0);

         return true;

      }*/




   ::payload database_impl::get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrUser)
   {

      return ::payload(::e_type_null);

   }


   ::pointer<::database::result_set>database_impl::query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {

      return nullptr;

   }


   //bool database_impl::query_items(::pointer<payload_array>& pitems, const ::scoped_string & scopedstrQuery)
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


   //bool database_impl::query_item(::payload & item, const ::scoped_string & scopedstrQuery)
   //{

   //   auto pset = query_result(scopedstrQuery, 1);

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



