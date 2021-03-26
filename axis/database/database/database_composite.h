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

      
      virtual void start_transaction();
      virtual void commit_transaction();
      virtual void rollback_transaction();


   public:
      
      
      //virtual __pointer(class dataset) dataset() = 0;


      virtual bool isActive();


      virtual ::e_status init();
      virtual e_connection connection_status(); 
      virtual ::e_status set_error_code(int iErrorCode);
      virtual string get_error_message();
      virtual void* get_handle();


      virtual ::e_status     connect(
         const char* name,
         const char* host = nullptr,
         const char* port = nullptr,
         const char* user = nullptr,
         const char* pass = nullptr,
         const char* sckt = nullptr,
         u64 uConnectionFlags = 0);


      virtual ::e_status     _connect();


      virtual void disconnect();
      virtual ::e_status     reset();
      virtual ::e_status     create();
      virtual ::e_status     drop();


      //virtual string escape(const char * psz);


      //inline __pointer(class transaction) transaction();


      virtual ::count get_affected_rows_count();


      virtual bool in_transaction() { return m_pdatabase->in_transaction(); };


      virtual bool exec(const char* pszQuery);


      virtual __pointer(result_set) query_result(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);
      virtual __pointer(result_set) query(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);


      virtual ::payload get_agent(const char* pszTable, const char* psz, const char* pszUser) override;
     

      using database::query_table_item;
      using database::query_item;
      using database::query_items;
      using database::query_row;
      using database::query_rows;

      //virtual ::payload query(const char * pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      virtual bool query_table_item(::payload& payload, const char* table, const char* item, const char* where);
      virtual bool query_rows(__pointer(row_array) & prowarray, const char* pszQuery) override;
      virtual bool query_row(__pointer(row) & prow, const char* pszQuery) override;
      virtual bool query_items(__pointer(var_array) & pvara, const char* pszQuery) override;
      virtual bool query_item(::payload & payload, const char* pszQuery) override;
      virtual bool memory_query_item(get_memory getmemory, const char* pszQuery) override;


      virtual string escape(const char* psz);

      virtual string error1(const char* pszPrefix = nullptr);
      virtual void trace_error1(const char* pszPrefix = nullptr);

      virtual ::payload get_insert_id();


   };


} // namespace database



