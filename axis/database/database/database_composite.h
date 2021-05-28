#pragma once


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
      virtual ~composite();

      
      void start_transaction() override;
      void commit_transaction() override;
      void rollback_transaction() override;


   public:
      
      
      //virtual __pointer(class dataset) dataset() = 0;


      bool isActive() override;


      ::e_status init() override;
      e_connection connection_status() override;
      ::e_status set_error_code(int iErrorCode) override;
      string get_error_message() override;
      void* get_handle() override;


      ::e_status     connect(
         const char* name,
         const char* host = nullptr,
         const char* port = nullptr,
         const char* user = nullptr,
         const char* pass = nullptr,
         const char* sckt = nullptr,
         u64 uConnectionFlags = 0) override;


      ::e_status     _connect() override;


      void disconnect() override;
      ::e_status     reset() override;
      ::e_status     create() override;
      ::e_status     drop() override;


      //virtual string escape(const char * psz);


      //inline __pointer(class transaction) transaction();


      ::count get_affected_rows_count() override;


      bool in_transaction() override { return m_pdatabase->in_transaction(); };


      bool exec(const char* pszQuery) override;


      __pointer(result_set) query_result(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;
      __pointer(result_set) query(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;


      virtual ::payload get_agent(const char* pszTable, const char* psz, const char* pszUser) override;
     

      using database::query_table_item;
      using database::query_item;
      using database::query_items;
      using database::query_row;
      using database::query_rows;

      //virtual ::payload query(const char * pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      bool query_table_item(::payload& payload, const char* table, const char* item, const char* where) override;
      bool query_rows(__pointer(row_array) & prowarray, const char* pszQuery) override;
      bool query_row(__pointer(row) & prow, const char* pszQuery) override;
      bool query_items(__pointer(var_array) & pvara, const char* pszQuery) override;
      bool query_item(::payload & payload, const char* pszQuery) override;
       bool query_blob(get_memory getmemory, const char* pszQuery) override;


      string escape(const char* psz) override;

      string error1(const char* pszPrefix = nullptr) override;
      void trace_error1(const char* pszPrefix = nullptr) override;

      ::payload get_insert_id() override;


   };


} // namespace database



