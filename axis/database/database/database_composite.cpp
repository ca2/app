#include "framework.h"


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


   e_connection composite::connection_status()
   {
      
      return m_pdatabase->connection_status(); 
   
   }


   ::e_status composite::connect(const ::string & name, const ::string & host, const ::string & port, const ::string & user, const ::string & pass, const ::string & sckt, u64 uConnectionFlags)
   {

      return m_pdatabase->connect(name, host, port, user, pass, sckt, uConnectionFlags);

   }



   ::e_status   composite::_connect()
   {

      return m_pdatabase->_connect();

   }

   void composite::disconnect()
   {

      m_pdatabase->disconnect();

   }


   ::e_status   composite::reset()
   {

      return m_pdatabase->reset();

   }


   ::e_status   composite::create()
   {

      return m_pdatabase->create();

   }


   ::e_status   composite::drop()
   {

      return m_pdatabase->drop();

   }



   bool composite::exec(const ::string & pszQuery)
   {

      return false;

   }


   //::payload composite::query(const ::string & pszQuery, ::count iMaxRowCount, ::count iMaxColumnCount)
   //{

   //   return query_rows(pszQuery);

   //}


   string composite::escape(const ::string & psz)
   {

      return psz;

   }


   ::count composite::get_affected_rows_count()
   {

      return -1;

   }


   string composite::error1(const ::string & pszPrefix)
   {

      return m_pdatabase->error1(pszPrefix);

   }


   void composite::trace_error1(const ::string & pszPrefix)
   {

      m_pdatabase->trace_error1(pszPrefix);

   }


   ::e_status     composite::init()
   {

      return m_pdatabase->init();

   }


   void* composite::get_handle()
   {

      return nullptr;

   }


   ::e_status     composite::set_error_code(int iErrorCode)
   {

      return m_pdatabase->set_error_code(iErrorCode);

   }


   string composite::get_error_message()
   {

      return m_pdatabase->get_error_message();

   }


   ::payload composite::get_agent(const ::string & pszTable, const ::string & psz, const ::string & pszUser)
   {

      return ::payload(::e_type_null);

   }


   
   bool composite::query_table_item(::payload& payload, const ::string & table, const ::string & item, const ::string & where)
   {

      return m_pdatabase->query_table_item(payload, table, item, where);

   }

   



   bool composite::query_rows(__pointer(row_array) & prowaray, const ::string & pszQuery)
   {

      return m_pdatabase->query_rows(prowaray, pszQuery);

   }


   bool composite::query_row(__pointer(row) & prow, const ::string & pszQuery)
   {

      return m_pdatabase->query_row(prow, pszQuery);

   }


   bool composite::query_items(__pointer(payload_array) & pvara, const ::string & pszQuery)
   {

      return m_pdatabase->query_items(pvara, pszQuery);

   }


   bool composite::query_item(::payload & payload, const ::string & pszQuery)
   {

      return m_pdatabase->query_item(payload, pszQuery);

   }


   bool composite::query_blob(get_memory getmemory, const ::string & pszQuery)
   {

      return m_pdatabase->query_blob(getmemory, pszQuery);

   }


   __pointer(::database::result_set) composite::query_result(const ::string & pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return m_pdatabase->query_result(pszQuery, iRowCount, iColumnCount);

   }


   __pointer(result_set) composite::query(const ::string & pszQuery, ::count iRowCount, ::count iColumnCount)
   {
      
      return query_result(pszQuery, iRowCount, iColumnCount);
   
   }

   
   ::payload composite::get_insert_id()
   {

      return ::payload();

   }


} // namespace database



