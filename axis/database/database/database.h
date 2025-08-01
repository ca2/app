#pragma once


#include "acme/prototype/prototype/get_memory.h"
////#include "acme/prototype/prototype/object.h"


namespace database
{


   class dataset;
   class transaction;


   class CLASS_DECL_AXIS database :
      virtual public ::object
   {
   public:

      friend class transaction;


      database();
      ~database() override;


   protected:

      virtual void start_transaction();
      virtual void commit_transaction();
      virtual void rollback_transaction();
   

   public:
      //virtual ::pointer<class dataset> dataset() = 0;

      virtual bool isActive() = 0;


      virtual void     init() = 0;
      virtual enum_connection connection_status() = 0;
      virtual void     set_error_code(int iErrorCode) = 0;
      virtual string get_error_message() = 0;
      virtual void * get_handle() = 0;


      virtual void     connect(
      const ::string & name,
      const ::string & host = nullptr,
      const ::string & port = nullptr,
      const ::string & user = nullptr,
      const ::string & pass = nullptr,
      const ::string & sckt = nullptr,
      unsigned long long uConnectionFlags = 0) = 0;

      virtual void     _connect() = 0;

      virtual void disconnect();
      virtual void     reset() = 0;
      virtual void     create() = 0;
      virtual void     drop() = 0;

      //virtual string escape(const ::scoped_string & scopedstr);

      virtual  ::pointer<class transaction> transaction();

      virtual ::collection::count get_affected_rows_count() = 0;

      virtual bool in_transaction() = 0;


      virtual bool exec(const ::scoped_string & scopedstrQuery) = 0;


      virtual ::pointer<result_set>query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1) = 0;
      virtual ::pointer<result_set> query(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1);


      //virtual ::payload query(const ::scoped_string & scopedstrQuery, ::collection::count iMaxRowCount = -1, ::collection::count iMaxColumnCount = -1);
      virtual ::payload query_table_item(const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where, const ::payload & payload = ::payload());
      virtual ::pointer<row_array>query_rows(const ::scoped_string & scopedstrQuery);
      virtual ::pointer<row>query_row(const ::scoped_string & scopedstrQuery);
      virtual ::pointer<payload_array>query_items(const ::scoped_string & scopedstrQuery);
      virtual ::payload query_item(const ::scoped_string & scopedstrQuery, const ::payload & payloadDefault = ::payload());
      //virtual bool query_blob(get_memory getmemory, const ::scoped_string & scopedstrQuery);


      virtual bool query_table_item(::payload& payload, const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where);


      virtual bool query_rows(::pointer<row_array> & rows, const ::scoped_string & scopedstrQuery);
      virtual bool query_row(::pointer<row> & rows, const ::scoped_string & scopedstrQuery);
      virtual bool query_items(::pointer<payload_array> & items, const ::scoped_string & scopedstrQuery);
      virtual bool query_item(::payload& item, const ::scoped_string & scopedstrQuery);
      virtual bool query_blob(get_memory getmemory, const ::scoped_string & scopedstrQuery);



      virtual ::payload get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrUser) = 0;


      virtual string escape(const ::scoped_string & scopedstr) = 0;

      virtual string add_error_message(const ::scoped_string & scopedstrErrorMessage);


      //virtual string query_error(const ::scoped_string & scopedstrPrefix = nullptr) = 0;
      virtual void trace_error1(const ::scoped_string & scopedstrPrefix = nullptr) = 0;

      virtual string query_error(const ::scoped_string & scopedstrPrefix = nullptr) = 0;

      virtual ::payload get_insert_id() = 0;

      virtual void set_id_blob(string strKey, ::block block);
      virtual bool get_id_blob(string strKey, ::get_memory getmemory);


   };


} // namespace database



