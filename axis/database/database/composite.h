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


      __pointer(::database::database)  m_pdatabase;


      composite();
      ~composite() override;

      
      void start_transaction() override;
      void commit_transaction() override;
      void rollback_transaction() override;


   public:
      
      
      //virtual __pointer(class dataset) dataset() = 0;


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
         u64 uConnectionFlags = 0) override;


      void     _connect() override;


      void disconnect() override;
      void     reset() override;
      void     create() override;
      void     drop() override;


      //virtual string escape(const ::string & psz);


      //inline __pointer(class transaction) transaction();


      ::count get_affected_rows_count() override;


      bool in_transaction() override { return m_pdatabase->in_transaction(); };


      bool exec(const ::string & pszQuery) override;


      __pointer(result_set) query_result(const ::string & pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;
      __pointer(result_set) query(const ::string & pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;


      virtual ::payload get_agent(const ::string & pszTable, const ::string & psz, const ::string & pszUser) override;
     

      using database::query_table_item;
      using database::query_item;
      using database::query_items;
      using database::query_row;
      using database::query_rows;

      //virtual ::payload query(const ::string & pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      bool query_table_item(::payload& payload, const ::string & table, const ::string & item, const ::string & where) override;
      bool query_rows(__pointer(row_array) & prowarray, const ::string & pszQuery) override;
      bool query_row(__pointer(row) & prow, const ::string & pszQuery) override;
      bool query_items(__pointer(payload_array) & pvara, const ::string & pszQuery) override;
      bool query_item(::payload & payload, const ::string & pszQuery) override;
       bool query_blob(get_memory getmemory, const ::string & pszQuery) override;


      string escape(const ::string & psz) override;

      string query_error(const ::string & pszPrefix = nullptr) override;
      void trace_error1(const ::string & pszPrefix = nullptr) override;

      ::payload get_insert_id() override;


   };


} // namespace database



