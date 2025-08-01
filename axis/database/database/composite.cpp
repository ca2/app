#include "framework.h"
#include "composite.h"


namespace database
{


   composite::composite()
   {


   }

   composite::~composite()
   {

   }


   void composite::start_transaction()
   {


   }


   void composite::commit_transaction()
   {

   }


   void composite::rollback_transaction()
   {


   }


   bool composite::isActive()
   {
      
      return m_pdatabase->isActive(); 
   
   }


   enum_connection composite::connection_status()
   {
      
      return m_pdatabase->connection_status(); 
   
   }


   void composite::connect(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrHost, const ::scoped_string & scopedstrPort, const ::scoped_string & scopedstrUser, const ::scoped_string & scopedstrPass, const ::scoped_string & scopedstrSocket, unsigned long long uConnectionFlags)
   {


      return m_pdatabase->connect(scopedstrName, scopedstrHost, scopedstrPort, scopedstrUser, scopedstrPass, scopedstrSocket, uConnectionFlags);

   }



   void   composite::_connect()
   {

      return m_pdatabase->_connect();

   }

   void composite::disconnect()
   {

      m_pdatabase->disconnect();

   }


   void   composite::reset()
   {

      return m_pdatabase->reset();

   }


   void   composite::create()
   {

      return m_pdatabase->create();

   }


   void   composite::drop()
   {

      return m_pdatabase->drop();

   }



   bool composite::exec(const ::scoped_string & scopedstrQuery)
   {

      return m_pdatabase->exec(scopedstrQuery);

   }


   //::payload composite::query(const ::scoped_string & scopedstrQuery, ::collection::count iMaxRowCount, ::collection::count iMaxColumnCount)
   //{

   //   return query_rows(scopedstrQuery);

   //}


   string composite::escape(const ::scoped_string & scopedstr)
   {

      return scopedstr;

   }


   ::collection::count composite::get_affected_rows_count()
   {

      return -1;

   }


   string composite::query_error(const ::scoped_string & scopedstrPrefix)
   {

      return m_pdatabase->query_error(scopedstrPrefix);

   }


   void composite::trace_error1(const ::scoped_string & scopedstrPrefix)
   {

      m_pdatabase->trace_error1(scopedstrPrefix);

   }


   void     composite::init()
   {

      return m_pdatabase->init();

   }


   void* composite::get_handle()
   {

      return nullptr;

   }


   void     composite::set_error_code(int iErrorCode)
   {

      return m_pdatabase->set_error_code(iErrorCode);

   }


   string composite::get_error_message()
   {

      return m_pdatabase->get_error_message();

   }


   ::payload composite::get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrUser)
   {

      return ::payload(::e_type_null);

   }


   
   bool composite::query_table_item(::payload& payload, const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where)
   {

      return m_pdatabase->query_table_item(payload, table, scopedstrItem, where);

   }

   
   bool composite::query_rows(::pointer<row_array>& prowaray, const ::scoped_string & scopedstrQuery)
   {

      return m_pdatabase->query_rows(prowaray, scopedstrQuery);

   }


   bool composite::query_row(::pointer<row>& prow, const ::scoped_string & scopedstrQuery)
   {

      return m_pdatabase->query_row(prow, scopedstrQuery);

   }


   bool composite::query_items(::pointer<payload_array>& pvara, const ::scoped_string & scopedstrQuery)
   {

      return m_pdatabase->query_items(pvara, scopedstrQuery);

   }


   bool composite::query_item(::payload & payload, const ::scoped_string & scopedstrQuery)
   {

      return m_pdatabase->query_item(payload, scopedstrQuery);

   }


   bool composite::query_blob(get_memory getmemory, const ::scoped_string & scopedstrQuery)
   {

      return m_pdatabase->query_blob(getmemory, scopedstrQuery);

   }


   ::pointer<::database::result_set>composite::query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {

      return m_pdatabase->query_result(scopedstrQuery, iRowCount, iColumnCount);

   }


   ::pointer<result_set>composite::query(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {
      
      return query_result(scopedstrQuery, iRowCount, iColumnCount);
   
   }

   
   ::payload composite::get_insert_id()
   {

      return ::payload();

   }


} // namespace database



