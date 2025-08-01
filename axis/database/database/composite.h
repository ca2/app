#pragma once


#include "axis/database/database/database.h"


namespace database
{


   class dataset;
   class transaction;

   class CLASS_DECL_AXIS composite :
      virtual public ::database::database
   {
   public:


      ::pointer<::database::database> m_pdatabase;


      composite();
      ~composite() override;

      
      void start_transaction() override;
      void commit_transaction() override;
      void rollback_transaction() override;


   public:
      
      
      //virtual ::pointer<class dataset> dataset() = 0;


      bool isActive() override;


      void init() override;
      enum_connection connection_status() override;
      void set_error_code(int iErrorCode) override;
      string get_error_message() override;
      void* get_handle() override;


      void     connect(
         const ::string & name,
         const ::string & host = nullptr,
         const ::string & port = nullptr,
         const ::string & user = nullptr,
         const ::string & pass = nullptr,
         const ::string & sckt = nullptr,
         unsigned long long uConnectionFlags = 0) override;


      void     _connect() override;


      void disconnect() override;
      void     reset() override;
      void     create() override;
      void     drop() override;


      //virtual string escape(const ::scoped_string & scopedstr);


      //inline ::pointer<class transaction> transaction();


      ::collection::count get_affected_rows_count() override;


      bool in_transaction() override { return m_pdatabase->in_transaction(); };


      bool exec(const ::scoped_string & scopedstrQuery) override;


      ::pointer<result_set>query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1) override;
      ::pointer<result_set>query(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1) override;


      virtual ::payload get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrUser) override;
     

      using database::query_table_item;
      using database::query_item;
      using database::query_items;
      using database::query_row;
      using database::query_rows;

      //virtual ::payload query(const ::scoped_string & scopedstrQuery, ::collection::count iMaxRowCount = -1, ::collection::count iMaxColumnCount = -1);
      bool query_table_item(::payload& payload, const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where) override;
      bool query_rows(::pointer<row_array>& prowarray, const ::scoped_string & scopedstrQuery) override;
      bool query_row(::pointer<row>& prow, const ::scoped_string & scopedstrQuery) override;
      bool query_items(::pointer<payload_array>& pvara, const ::scoped_string & scopedstrQuery) override;
      bool query_item(::payload & payload, const ::scoped_string & scopedstrQuery) override;
       bool query_blob(get_memory getmemory, const ::scoped_string & scopedstrQuery) override;


      string escape(const ::scoped_string & scopedstr) override;

      string query_error(const ::scoped_string & scopedstrPrefix = nullptr) override;
      void trace_error1(const ::scoped_string & scopedstrPrefix = nullptr) override;

      ::payload get_insert_id() override;


   };


} // namespace database



