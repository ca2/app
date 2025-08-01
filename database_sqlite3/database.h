#pragma once


#include "axis/database/database/database_impl.h"


namespace sqlite
{


   class CLASS_DECL_DATABASE_SQLITE3 database :
      public ::database::database_impl
   {
   public:


      void *                                             m_psqlite;

      sqlite3_stmt *                                     m_pstmtSelect;
      int                                                m_iSelectId;

      sqlite3_stmt *                                     m_pstmtReplace;
      int                                                m_iReplaceId;
      int                                                m_iReplaceValue;


      database();
      ~database() override;


   protected:

      void start_transaction() override;
      void commit_transaction() override;
      void rollback_transaction() override;

   public:


      //virtual ::pointer<::database::dataset>dataset() override;
      ::database::enum_connection connection_status() override;

      void set_error_code(int iErrorCode) override;

      void * get_handle() override;
      string get_error_message() override;

      void _connect() override;
      void disconnect() override;
      void create() override;
      void drop() override;


      string escape(const ::scoped_string & scopedstr) override;

      //virtual ::pointer<class dataset> dataset() = 0;

      bool isActive() override;


      void init() override;

      string add_error_message(const ::scoped_string & scopedstrErrorMessage) override;

      void connect(
         const ::string & name,
         const ::string & host = nullptr,
         const ::string & port = nullptr,
         const ::string & user = nullptr,
         const ::string & pass = nullptr,
         const ::string & sckt = nullptr,
         unsigned long long uConnectionFlags = 0) override;


      void reset() override;

      //virtual string escape(const ::scoped_string & scopedstr);

      ::collection::count get_affected_rows_count() override;

      bool in_transaction() override;

      bool exec(const ::scoped_string & scopedstrQuery) override;

      ::pointer<::database::result_set>query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount) override;

      ::pointer<::database::result_set>query(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1) override;


      //virtual ::payload query(const ::scoped_string & scopedstrQuery, ::collection::count iMaxRowCount = -1, ::collection::count iMaxColumnCount = -1);
      ::pointer<::database::row_array>query_rows(const ::scoped_string & scopedstrQuery) override;
      
      ::pointer<::database::row>query_row(const ::scoped_string & scopedstrQuery) override;
      
      ::pointer<::payload_array>query_items(const ::scoped_string & scopedstrQuery) override;
      
      virtual ::payload query_item(const ::scoped_string & scopedstrQuery);
      virtual bool memory_query_item(get_memory getmemory, const ::scoped_string & scopedstrQuery);

      //virtual bool query_rows(::pointer<row_array>& rows, const ::scoped_string & scopedstrQuery);
      //virtual bool query_row(::pointer<row>& rows, const ::scoped_string & scopedstrQuery);
      //virtual bool query_items(::pointer<payload_array>& items, const ::scoped_string & scopedstrQuery);
      //virtual bool query_item(::payload & item, const ::scoped_string & scopedstrQuery);


      //virtual string escape(const ::scoped_string & scopedstr);

      //string query_error(const ::scoped_string & scopedstrPrefix = nullptr) override;
      void trace_error1(const ::scoped_string & scopedstrPrefix = nullptr) override;
      string query_error(const ::scoped_string & scopedstrPrefix = nullptr) override;


      virtual void set_id_blob(string strKey, ::block block) override;
      virtual bool get_id_blob(string strKey, ::get_memory getmemory) override;



   };


} // namespace sqlite



